# 46. 全排列

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/permutations/) ｜ [国际站](https://leetcode.com/problems/permutations/)
>
> 🟡 中等 ｜ 标签：`回溯`

## 📝 题目描述

给定一个**不含重复数字**的整数数组 `nums`，返回其所有可能的全排列。可以按任意顺序返回答案。

**示例 1：**

```
输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
```

**示例 2：**

```
输入：nums = [0,1]
输出：[[0,1],[1,0]]
```

**示例 3：**

```
输入：nums = [1]
输出：[[1]]
```

**提示：**

- `1 <= nums.length <= 6`
- `-10 <= nums[i] <= 10`
- `nums` 中的所有整数**互不相同**

## 💡 题解

### 解法一：回溯 + used 标记数组

**思路**：把"生成排列"想象成在 `n` 个空位上依次填数。维护两条状态：`path`（已填的前缀）和 `used`（哪些元素已被占用）。每一层从 `0` 到 `n - 1` 扫描候选，跳过已用的，选中一个就标记 `used`、追加到 `path`，递归填下一个空位；返回后撤销这两步（回溯的"恢复现场"）。当 `path` 长度等于 `n` 时得到一个完整排列，**拷贝**进答案。这是最贴近人工枚举直觉的回溯模板，扩展性强（含重复元素的第 47 题"全排列 II"只需在此基础上排序 + 同层去重）。

```cpp
#include <vector>

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> path;
        vector<bool> used(nums.size(), false);
        backtrack(nums, used, path, ans);
        return ans;
    }

private:
    void backtrack(const vector<int>& nums, vector<bool>& used,
                   vector<int>& path, vector<vector<int>>& ans) {
        if (path.size() == nums.size()) {
            ans.push_back(path);  // 必须拷贝，path 之后还会被回溯修改
            return;
        }
        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            if (used[i]) continue;  // 已在当前排列中，跳过
            used[i] = true;
            path.push_back(nums[i]);
            backtrack(nums, used, path, ans);
            path.pop_back();        // 恢复现场
            used[i] = false;
        }
    }
};
```

- ⏱️ 时间复杂度：`O(n × n!)`，共 `n!` 个排列，每个排列拷贝 `O(n)`
- 💾 空间复杂度：`O(n)`，递归栈、`path` 与 `used`（不计输出）

### 解法二：回溯 + 原地交换（推荐）

**思路**：换一种划分方式：确定第 `depth` 个空位时，让 `[depth, n)` 区间里的每个候选**轮流与位置 `depth` 交换**，然后递归确定 `depth + 1` 位，返回后再换回去。这样"未用元素"始终聚拢在 `[depth, n)` 一段里，**省掉了 `used` 数组和 `path` 数组**——到达叶子时 `nums` 本身就是一份完整排列，直接拷贝进答案即可。代码最短、辅助状态最少；代价是产生的排列**不保证字典序**（本题允许任意顺序，不受影响）。

```cpp
#include <utility>
#include <vector>

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        backtrack(nums, 0, ans);
        return ans;
    }

private:
    // [0, depth) 已确定，[depth, n) 为剩余候选
    void backtrack(vector<int>& nums, int depth, vector<vector<int>>& ans) {
        if (depth == static_cast<int>(nums.size())) {
            ans.push_back(nums);  // 此时 nums 本身就是一份完整排列
            return;
        }
        for (int i = depth; i < static_cast<int>(nums.size()); ++i) {
            swap(nums[depth], nums[i]);  // 把 nums[i] 换到当前位置
            backtrack(nums, depth + 1, ans);
            swap(nums[depth], nums[i]);  // 回溯：换回原位
        }
    }
};
```

- ⏱️ 时间复杂度：`O(n × n!)`，排列共 `n!` 个，每个拷贝 `O(n)`；交换本身 `O(1)`
- 💾 空间复杂度：`O(n)`，仅递归栈（不计输出）

## ⚠️ 易错点

- 交换法**必须把交换换回来**，否则同一层后续分支的候选集合已被打乱，会漏解或重解。
- 收集答案时必须是**拷贝**（`ans.push_back(path)` 传值 / `push_back(nums)` 传值），存引用或指针会在后续回溯中被改掉。
- 交换法生成的排列不按字典序；若题目要求字典序输出，应改用解法一按序枚举。
- `used` 版本中撤销操作的顺序要与选择操作**严格对称**（`pop_back` 与 `used[i] = false` 都不能漏），漏掉一个会导致后续分支永久少一个候选。

---

[← 返回目录](../../README.md)
