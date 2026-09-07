# 39. 组合总和

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/combination-sum/) ｜ [国际站](https://leetcode.com/problems/combination-sum/)
>
> 🟡 中等 ｜ 标签：`回溯`

## 📝 题目描述

给定一个**无重复元素**的整数数组 `candidates` 和一个目标数 `target`，找出 `candidates` 中可以使数字和为目标数 `target` 的所有**不同组合**。

- `candidates` 中的**同一个数字可以无限制重复被选取**；
- 如果至少一个数字的被选数量不同，两种组合就是不同的；
- 数组内的元素可以按任意顺序组成答案。

对于给定的输入，保证和为 `target` 的不同组合数少于 `150` 个。

**示例 1：**

```
输入：candidates = [2,3,6,7], target = 7
输出：[[2,2,3],[7]]
解释：2 + 2 + 3 = 7；7 = 7。注意 [2,3,2] 与 [2,2,3] 视为同一组合，只保留一个。
```

**示例 2：**

```
输入：candidates = [2,3,5], target = 8
输出：[[2,2,2,2],[2,3,3],[3,5]]
```

**示例 3：**

```
输入：candidates = [2], target = 1
输出：[]
```

**提示：**

- `1 <= candidates.length <= 30`
- `2 <= candidates[i] <= 40`
- `candidates` 的元素**互不相同**
- `1 <= target <= 40`

## 💡 题解

### 解法一：回溯（不排序）

**思路**：在"选数凑目标"的搜索树上做回溯，用两个手段控制正确性：

1. **`start` 起点约束**——每层只从下标 `start` 开始枚举候选。这保证组合内的元素下标单调不减，`[2,2,3]` 只会以一种顺序被生成，天然避免 `[2,3,2]`、`[3,2,2]` 等重复排列。
2. **递归传 `i` 而不是 `i + 1`**——本轮选了 `candidates[i]` 后，下一层仍允许从 `i` 开始，即同一元素可重复选取（这正是本题与第 40 题"组合总和 II"的关键差异）。

状态只需维护剩余目标 `remain`：减到 `0` 收集，减不动（候选大于 `remain`）就跳过。因元素互不相同且均 `>= 2`，`remain` 严格递减，递归必然终止。

```cpp
#include <vector>

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> path;
        backtrack(candidates, 0, target, path, ans);
        return ans;
    }

private:
    void backtrack(const vector<int>& candidates, int start, int remain,
                   vector<int>& path, vector<vector<int>>& ans) {
        if (remain == 0) {
            ans.push_back(path);  // 恰好凑出目标
            return;
        }
        for (int i = start; i < static_cast<int>(candidates.size()); ++i) {
            if (candidates[i] > remain) continue;  // 放不下的单个跳过（只能逐个跳）
            path.push_back(candidates[i]);
            backtrack(candidates, i, remain - candidates[i], path, ans);  // 传 i：可重复选
            path.pop_back();
        }
    }
};
```

- ⏱️ 时间复杂度：`O(n^(t/m))`，`n` 为候选数、`t` 为 `target`、`m` 为最小候选值（搜索树规模的宽松上界）
- 💾 空间复杂度：`O(t/m)`，递归栈与 `path` 的最大深度

### 解法二：回溯 + 排序剪枝（推荐）

**思路**：先对 `candidates` **排序**。此后若在某一层发现 `candidates[i] > remain`，由于后面的数只会更大，**从 `i` 到末尾的所有分支都不可能成功**，直接 `break` 剪掉整段子树；而未排序时只能对单个元素 `continue`，其余分支仍要逐一试探。当 `target` 较大、候选中有明显偏大的数时，剪枝收益显著；即便 `remain` 较小，剪枝同样让循环提前结束。其余逻辑（`start` 去重、传 `i` 允许复选）与解法一完全一致。这是"排序换剪枝"思想的经典示范。

```cpp
#include <algorithm>
#include <vector>

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());  // 排序是剪枝的前提
        vector<vector<int>> ans;
        vector<int> path;
        backtrack(candidates, 0, target, path, ans);
        return ans;
    }

private:
    void backtrack(const vector<int>& candidates, int start, int remain,
                   vector<int>& path, vector<vector<int>>& ans) {
        if (remain == 0) {  // 恰好凑出目标，收集并返回
            ans.push_back(path);
            return;
        }
        for (int i = start; i < static_cast<int>(candidates.size()); ++i) {
            if (candidates[i] > remain) break;  // 已排序，其后更大，整体剪枝
            path.push_back(candidates[i]);
            backtrack(candidates, i, remain - candidates[i], path, ans);  // 传 i：可重复选
            path.pop_back();
        }
    }
};
```

- ⏱️ 时间复杂度：`O(n^(t/m))`，上界同解法一，但剪枝后的实际搜索树显著更小
- 💾 空间复杂度：`O(t/m)`，递归栈与 `path`（排序另需 `O(n)`，可忽略）

## ⚠️ 易错点

- **可重复选取**要求递归传 `i`（当前元素还能再选）；顺手写成 `i + 1` 就变成了"每个数最多选一次"的第 40 题语义，会漏掉 `[2,2,3]` 这类组合。
- 每层若从 `0` 而不是 `start` 开始枚举，同一组合会以不同排列形式出现多次（`[2,3,2]` 与 `[2,2,3]`）。
- 剪枝用 `break` 的前提是**先排序**；不排序只能对单个元素 `continue`，两者不可混用。
- `remain == 0` 时收集后应立即 `return`；若不排序又缺少"候选大于 `remain` 跳过"的保护，`remain` 可能被减成负数后继续空转。

---

[← 返回目录](../../README.md)
