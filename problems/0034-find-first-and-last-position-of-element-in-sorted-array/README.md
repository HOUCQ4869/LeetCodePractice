# 34. 在排序数组中查找元素的第一个和最后一个位置

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/) ｜ [国际站](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/)
>
> 🟡 中等 ｜ 标签：`二分查找`

## 📝 题目描述

给定一个非递减排序（可能包含重复元素）的整数数组 `nums` 和一个目标值 `target`，找出 `target` 在数组中的开始位置和结束位置，以数组 `[开始下标, 结束下标]` 的形式返回；如果 `target` 不在数组中，返回 `[-1, -1]`。题目要求设计并实现时间复杂度为 `O(log n)` 的算法。

**示例 1：**

```text
输入：nums = [5,7,7,8,8,10], target = 8
输出：[3,4]
解释：8 第一次出现在下标 3，最后一次出现在下标 4。
```

**示例 2：**

```text
输入：nums = [5,7,7,8,8,10], target = 6
输出：[-1,-1]
解释：6 不在数组中。
```

**示例 3：**

```text
输入：nums = [], target = 0
输出：[-1,-1]
```

**提示：**

- `0 <= nums.length <= 10^5`
- `-10^9 <= nums[i] <= 10^9`，`nums` 为非递减数组
- `-10^9 <= target <= 10^9`

## 💡 题解

### 解法一：线性扫描

**思路**：一次遍历，记录 `target` 第一次和最后一次出现的下标。写法最直接，但没有利用数组有序这一关键性质，不满足题目 `O(log n)` 的进阶要求，仅作对照。

```cpp
#include <vector>

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int n = nums.size();
        int start = -1, end = -1;
        for (int i = 0; i < n; i++) {
            if (nums[i] == target) {
                if (start == -1) start = i;  // 第一次出现
                end = i;                     // 持续更新为最后一次
            }
        }
        return {start, end};
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(1)`

### 解法二：两次二分查找（推荐）

**思路**：把问题拆成两个标准的"边界二分"：

1. **左边界**：用 `lowerBound` 求"第一个 `>= target`"的下标 `start`。若 `start` 越界或 `nums[start] != target`，说明 `target` 不存在，直接返回 `[-1, -1]`。
2. **右边界**：用 `upperBound` 求"第一个 `> target`"的下标，其前一位就是最后一个等于 `target` 的位置。

两个模板只差一个字符：`lowerBound` 中是 `nums[mid] < target`，`upperBound` 中是 `nums[mid] <= target`，正好对应 STL 中 `lower_bound` / `upper_bound` 的语义。

```cpp
#include <vector>

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int start = lowerBound(nums, target);
        if (start == (int)nums.size() || nums[start] != target) {
            return {-1, -1};
        }
        // 第一个大于 target 的位置减一，即最后一个等于 target 的位置
        int end = upperBound(nums, target) - 1;
        return {start, end};
    }

private:
    // 第一个 >= target 的下标（左闭右开模板）
    int lowerBound(vector<int>& nums, int target) {
        int left = 0, right = nums.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }

    // 第一个 > target 的下标（左闭右开模板）
    int upperBound(vector<int>& nums, int target) {
        int left = 0, right = nums.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] <= target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }
};
```

- ⏱️ 时间复杂度：`O(log n)`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 找到 `target` 后直接停止的普通二分无法定位边界；必须分别实现"找第一个"和"找最后一个"两套逻辑（或统一为 `lower_bound` / `upper_bound`）。
- 判断条件 `<` 与 `<=` 一字之差：`lowerBound` 用 `nums[mid] < target` 收缩左边界，`upperBound` 用 `nums[mid] <= target`，写反会导致边界错位。
- 必须先检查 `start == nums.size()` 再访问 `nums[start]`，否则 `target` 大于所有元素或数组为空时会越界。
- `upperBound` 的结果可能等于 `n`（`target` 不小于数组所有元素），此时"最后一个位置"是 `n - 1`，减一操作天然正确，无需特判。

---

[← 返回目录](../../README.md)
