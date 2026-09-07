# 78. 子集

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/subsets/) ｜ [国际站](https://leetcode.com/problems/subsets/)
>
> 🟡 中等 ｜ 标签：`回溯` `位运算`

## 📝 题目描述

给定一个**不含重复元素**的整数数组 `nums`，返回该数组所有可能的子集（幂集）。解集不能包含重复的子集，可以按任意顺序返回。

**示例 1：**

```
输入：nums = [1,2,3]
输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
```

**示例 2：**

```
输入：nums = [0]
输出：[[],[0]]
```

**提示：**

- `1 <= nums.length <= 10`
- `-10 <= nums[i] <= 10`
- `nums` 中的所有元素**互不相同**

## 💡 题解

### 解法一：迭代逐个扩展

**思路**：从只含空集的答案集出发，逐个处理数组元素 `x`：每来一个新元素，**已有的每个子集各自拷贝一份并追加 `x`**，就得到所有包含 `x` 的新子集。答案规模按 `1 → 2 → 4 → … → 2^n` 翻倍。全程无递归、无撤销，是最不容易写错的做法。注意内层循环只遍历**加入 `x` 之前**已存在的子集（先记录当前规模），否则边遍历边追加会陷入死循环。

```cpp
#include <vector>

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans = {{}};  // 从空集出发
        for (int x : nums) {
            int sz = static_cast<int>(ans.size());
            for (int i = 0; i < sz; ++i) {  // 只遍历扩展前的旧子集
                ans.push_back(ans[i]);       // 拷贝旧子集
                ans.back().push_back(x);     // 追加新元素
            }
        }
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n × 2^n)`，共 `2^n` 个子集，拷贝构造总计付出 `O(n)` 均摊
- 💾 空间复杂度：`O(1)`，除输出外仅常数空间（不计输出）

### 解法二：回溯（start 控制去重）

**思路**：子集树的标准回溯：函数进入时先**把当前 `path` 收进答案**（子集树中每个节点都对应一个合法子集，而非只有叶子），然后让循环下标 `i` 从 `start` 开始，尝试"选入 `nums[i]`"后递归 `i + 1`，返回后撤销。`start` 保证每层只在当前位置**之后**挑选，天然避免了 `{1,2}` 与 `{2,1}` 这类顺序性重复，无需任何去重集合。这份模板可以直接推广到「子集 II」「组合总和」等一整类组合枚举题。

```cpp
#include <vector>

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> path;
        backtrack(nums, 0, path, ans);
        return ans;
    }

private:
    void backtrack(const vector<int>& nums, int start,
                   vector<int>& path, vector<vector<int>>& ans) {
        ans.push_back(path);  // 每个节点对应一个子集，进入即收集
        for (int i = start; i < static_cast<int>(nums.size()); ++i) {
            path.push_back(nums[i]);
            backtrack(nums, i + 1, path, ans);
            path.pop_back();
        }
    }
};
```

- ⏱️ 时间复杂度：`O(n × 2^n)`
- 💾 空间复杂度：`O(n)`，递归栈与 `path`（不计输出）

### 解法三：二进制位运算枚举（推荐）

**思路**：`n` 个互不相同的元素，每个子集等价于给每个元素做一次"选 / 不选"的决策——这正好编码为一个 `n` 位二进制数：**第 `i` 位为 `1` 表示选入 `nums[i]`**。于是子集与 `[0, 2^n - 1]` 内的整数**一一对应**，从 `0` 枚举到 `2^n - 1`，对每个掩码按位挑出为 `1` 的元素即可。无递归、无撤销、天然无重复，是本题最简洁的写法（前提是 `n` 较小且元素互异，本题 `n <= 10` 恰好完美契合）。

```cpp
#include <utility>
#include <vector>

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        vector<vector<int>> ans;
        ans.reserve(1u << n);
        for (int mask = 0; mask < (1 << n); ++mask) {  // 每个掩码对应一个子集
            vector<int> cur;
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) cur.push_back(nums[i]);  // 第 i 位为 1 则选入
            }
            ans.push_back(std::move(cur));
        }
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n × 2^n)`，共 `2^n` 个子集，每个提取 `O(n)`
- 💾 空间复杂度：`O(1)`，除输出数组外仅常数空间

## ⚠️ 易错点

- 回溯版收集时机是**进入每个节点时**（子集没有统一的"叶子深度"），只在深层收集会漏掉大量子集；空集也来自第一次进入时的空 `path`。
- 迭代扩展法必须先记下本轮起始规模再遍历（或用临时数组承接），边遍历 `ans` 边向其 `push_back` 会无限循环。
- 位运算版枚举上界是 `1 << n`（不是 `1 << (n - 1)`），且掩码含 `0`——它对应空集，不能跳过。
- 若改用「每位选/不选」的二叉分支写法，两个分支都要递归；漏掉"不选"分支会只剩全集与空集。

---

[← 返回目录](../../README.md)
