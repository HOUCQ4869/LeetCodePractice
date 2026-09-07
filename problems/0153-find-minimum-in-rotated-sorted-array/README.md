# 153. 寻找旋转排序数组中的最小值

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array/) ｜ [国际站](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/)
>
> 🟡 中等 ｜ 标签：`二分查找`

## 📝 题目描述

一个长度为 `n` 的元素互不相同的升序数组，经过 `1` 到 `n` 次**旋转**后得到输入数组 `nums`（每次旋转把末尾元素移到开头）。例如 `[0,1,2,4,5,6,7]` 旋转 4 次后变为 `[4,5,6,7,0,1,2]`。请找出并返回数组中的**最小元素**。题目要求设计 `O(log n)` 的算法。

**示例 1：**

```text
输入：nums = [3,4,5,1,2]
输出：1
解释：原数组为 [1,2,3,4,5]，旋转 3 次得到输入数组。
```

**示例 2：**

```text
输入：nums = [4,5,6,7,0,1,2]
输出：0
```

**示例 3：**

```text
输入：nums = [11,13,15,17]
输出：11
解释：原数组旋转了 n 次回到原样，数组本身仍有序，首元素即最小值。
```

**提示：**

- `n == nums.length`
- `1 <= n <= 5000`
- `-5000 <= nums[i] <= 5000`，元素互异
- 数组由升序数组旋转 `1` 到 `n` 次得到

## 💡 题解

### 解法一：线性扫描

**思路**：遍历数组维护最小值；也可以利用"旋转数组前一段递增、遇到骤降点即为最小值"的观察提前结束。简单可靠，但 `O(n)` 不满足题目进阶要求。

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int findMin(vector<int>& nums) {
        int ans = nums[0];
        for (int x : nums) {
            ans = min(ans, x);
        }
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(1)`

### 解法二：二分查找（推荐）

**思路**：旋转数组的结构是"两段递增 + 一个骤降点（最小值）"，用 `left`、`right` 框住最小值所在区间。关键在于**与右端点 `nums[right]` 比较**：

- 若 `nums[mid] > nums[right]`，说明 `mid` 落在左段（较大段），最小值一定在 `(mid, right]`，令 `left = mid + 1`；
- 否则 `mid` 落在右段（较小段）或数组未旋转，`mid` 本身可能就是最小值，令 `right = mid`（不能 `-1`）。

区间每轮缩小且始终保持包含最小值，收敛到 `left == right` 时即为答案。与 `nums[left]` 比较不可行：数组未旋转时左半右半都"看似有序"，无法判断方向。

```cpp
#include <vector>

class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[right]) {
                left = mid + 1;  // 最小值在 mid 右侧（mid 一定不是最小值）
            } else {
                right = mid;     // mid 可能就是最小值，保留
            }
        }
        return nums[left];
    }
};
```

- ⏱️ 时间复杂度：`O(log n)`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 必须与 `nums[right]` 而非 `nums[left]` 比较：数组未旋转时（旋转 `n` 次）`nums[mid] > nums[left]` 恒成立，会错误地不断右移错过最小值。
- `nums[mid] <= nums[right]` 时只能写 `right = mid`，写 `mid - 1` 可能把最小值排除在区间外（`mid` 本身可能就是最小值）。
- 循环条件是 `left < right` 而非 `left <= right`，配合 `right = mid` 才能保证区间严格缩小、不死循环。
- 本题元素互异；若允许重复（154 题），当 `nums[mid] == nums[right]` 时无法判断方向，只能 `right--` 逐步收缩，最坏退化为 `O(n)`。

---

[← 返回目录](../../README.md)
