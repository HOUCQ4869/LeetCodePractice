# 35. 搜索插入位置

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/search-insert-position/) ｜ [国际站](https://leetcode.com/problems/search-insert-position/)
>
> 🟢 简单 ｜ 标签：`二分查找`

## 📝 题目描述

给定一个元素互不相同且升序排列的整数数组 `nums` 和一个目标值 `target`，如果 `target` 在数组中，返回它的下标；如果不在，返回将它插入数组后仍保持有序的位置下标。题目要求使用时间复杂度为 `O(log n)` 的算法。

**示例 1：**

```text
输入：nums = [1,3,5,6], target = 5
输出：2
解释：5 存在于数组中，下标为 2。
```

**示例 2：**

```text
输入：nums = [1,3,5,6], target = 2
输出：1
解释：2 不在数组中，插入后应位于 1 和 3 之间，即下标 1。
```

**示例 3：**

```text
输入：nums = [1,3,5,6], target = 7
输出：4
解释：7 比所有元素都大，插入到数组末尾，下标 4。
```

**提示：**

- `1 <= nums.length <= 10^4`
- `-10^4 <= nums[i] <= 10^4`，`nums` 为无重复元素的升序数组
- `-10^4 <= target <= 10^4`

## 💡 题解

### 解法一：顺序扫描

**思路**：从左到右找到第一个大于等于 `target` 的位置，该位置即插入位置；若所有元素都小于 `target`，则插入到末尾 `n`。思路直观，但没有利用数组的有序性，不满足题目 `O(log n)` 的要求。

```cpp
#include <vector>

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (nums[i] >= target) return i;
        }
        return n;  // target 比所有元素都大，插到末尾
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(1)`

### 解法二：二分查找（推荐）

**思路**：问题等价于求"第一个大于等于 `target` 的下标"，即 STL 的 `lower_bound`。采用左闭右开区间 `[left, right)`：若 `nums[mid] < target`，插入位置一定在 `mid` 右侧，令 `left = mid + 1`；否则 `mid` 本身可能就是答案，令 `right = mid`。循环结束时 `left == right` 即为所求。`right` 初始取 `n`，天然覆盖"插入到末尾"的情况。

```cpp
#include <vector>

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        // 左闭右开区间 [left, right)，right 初始为 n 覆盖"插到末尾"的情况
        int left = 0, right = nums.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) {
                left = mid + 1;  // 答案在 mid 右侧
            } else {
                right = mid;     // nums[mid] >= target，mid 可能是答案
            }
        }
        // 循环结束时 left == right，即第一个 >= target 的位置
        return left;
    }
};
```

- ⏱️ 时间复杂度：`O(log n)`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 区间定义要自洽：`right` 初始化为 `n`（左闭右开）还是 `n - 1`（左闭右闭）决定了循环条件（`left < right` 还是 `left <= right`）和更新方式，两套模板不能混用，否则死循环或漏解。
- `(left + right)` 直接相加可能整型溢出，应写 `left + (right - left) / 2`。
- 忘记处理 `target` 大于所有元素的情况，此时答案是 `n`；左闭右开模板中 `right` 初始为 `n` 可自然覆盖。

---

[← 返回目录](../../README.md)
