# 4. 寻找两个正序数组的中位数

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/median-of-two-sorted-arrays/) ｜ [国际站](https://leetcode.com/problems/median-of-two-sorted-arrays/)
>
> 🔴 困难 ｜ 标签：`二分查找`

## 📝 题目描述

给定两个大小分别为 `m` 和 `n` 的**升序**数组 `nums1` 和 `nums2`，请找出并返回这两个正序数组的**中位数**。算法的时间复杂度要求为 `O(log(m+n))`。中位数的定义：把两个数组合并排序后，若总长度为奇数则为正中间的数；若为偶数则为中间两个数的平均值。

**示例 1：**

```text
输入：nums1 = [1,3], nums2 = [2]
输出：2.00000
解释：合并数组 = [1,2,3]，中位数为 2。
```

**示例 2：**

```text
输入：nums1 = [1,2], nums2 = [3,4]
输出：2.50000
解释：合并数组 = [1,2,3,4]，中位数为 (2 + 3) / 2 = 2.5。
```

**示例 3：**

```text
输入：nums1 = [], nums2 = [1]
输出：1.00000
```

**提示：**

- `nums1.length == m`，`nums2.length == n`
- `0 <= m, n <= 1000`，`1 <= m + n <= 2000`
- `-10^6 <= nums1[i], nums2[i] <= 10^6`

## 💡 题解

### 解法一：归并后取中位数

**思路**：用归并排序的合并步骤把两个有序数组合成一个有序数组，再按总长度的奇偶直接取中位数。这是最直观的做法，但 `O(m+n)` 的时间和空间都不满足题目进阶要求，作为理解的起点。

```cpp
#include <vector>

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        vector<int> merged;
        merged.reserve(m + n);
        int i = 0, j = 0;
        while (i < m && j < n) {
            if (nums1[i] <= nums2[j]) merged.push_back(nums1[i++]);
            else merged.push_back(nums2[j++]);
        }
        while (i < m) merged.push_back(nums1[i++]);
        while (j < n) merged.push_back(nums2[j++]);
        int total = m + n;
        if (total % 2 == 1) {
            return merged[total / 2];
        }
        return (merged[total / 2 - 1] + merged[total / 2]) / 2.0;
    }
};
```

- ⏱️ 时间复杂度：`O(m + n)`
- 💾 空间复杂度：`O(m + n)`

### 解法二：逐步淘汰求第 k 小

**思路**：中位数本质是"合并后第 k 小的数"（奇数长度取第 `(m+n)/2 + 1` 小，偶数长度取第 `(m+n)/2` 与第 `(m+n)/2 + 1` 小的平均）。利用有序性做指数淘汰：设 `step = k/2`，比较两数组各自的第 `step` 个元素，较小一方的前 `step` 个元素必然全部排在第 k 小之前，可一次性淘汰；被淘汰方起点后移、`k` 减去淘汰个数，循环直到 `k == 1` 或一方耗尽。每轮淘汰约一半，总复杂度 `O(log(m+n))`。

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        if ((m + n) % 2 == 1) {
            return kth(nums1, nums2, (m + n) / 2 + 1);
        }
        int a = kth(nums1, nums2, (m + n) / 2);
        int b = kth(nums1, nums2, (m + n) / 2 + 1);
        return (a + b) / 2.0;
    }

private:
    // 求两有序数组合并后第 k 小的元素（k 从 1 开始）
    int kth(vector<int>& a, vector<int>& b, int k) {
        int i = 0, j = 0;  // 两数组尚未消费部分的起点
        while (true) {
            if (i == (int)a.size()) return b[j + k - 1];  // a 耗尽
            if (j == (int)b.size()) return a[i + k - 1];  // b 耗尽
            if (k == 1) return min(a[i], b[j]);
            // 各比较 k/2 个（不足则取到末尾），淘汰较小一方
            int step = k / 2;
            int ni = min((int)a.size(), i + step) - 1;
            int nj = min((int)b.size(), j + step) - 1;
            if (a[ni] <= b[nj]) {
                k -= ni - i + 1;
                i = ni + 1;
            } else {
                k -= nj - j + 1;
                j = nj + 1;
            }
        }
    }
};
```

- ⏱️ 时间复杂度：`O(log(m + n))`
- 💾 空间复杂度：`O(1)`

### 解法三：分割线二分（推荐）

**思路**：中位数的另一种刻画：在合并后的数组中画一条**分割线**，使左半元素个数恰为 `half = (m+n+1)/2`（总长为奇数时左边多一个），且"左边任一元素 ≤ 右边任一元素"。分割线可以用两数组各自的贡献个数 `i + j = half` 唯一刻画，于是只需**在较短的数组上**二分 `i`（`j = half - i` 随之确定）：

- 设 `l1, l2` 为两数组左侧最大值，`r1, r2` 为右侧最小值（取不到的边界用 `INT_MIN / INT_MAX` 哨兵代替）；
- 当 `l1 <= r2 && l2 <= r1` 时分割线合法，按奇偶直接算出中位数；
- 当 `l1 > r2` 说明 `nums1` 贡献太多，左移；反之右移。

由于在较短数组上二分，`j` 不会越界，复杂度为 `O(log(min(m, n)))`，是理论最优的做法。

```cpp
#include <vector>
#include <algorithm>
#include <climits>

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // 始终在较短的数组上二分，保证 j = half - i 不越界
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }
        int m = nums1.size(), n = nums2.size();
        int half = (m + n + 1) / 2;  // 左半部分的元素个数（奇数时左边多一个）
        int left = 0, right = m;
        while (left <= right) {
            int i = left + (right - left) / 2;  // nums1 贡献给左半的元素个数
            int j = half - i;                    // nums2 贡献给左半的元素个数
            // 边界用正负无穷哨兵代替，避免繁琐的分类讨论
            int l1 = (i == 0) ? INT_MIN : nums1[i - 1];
            int r1 = (i == m) ? INT_MAX : nums1[i];
            int l2 = (j == 0) ? INT_MIN : nums2[j - 1];
            int r2 = (j == n) ? INT_MAX : nums2[j];
            if (l1 <= r2 && l2 <= r1) {
                // 分割线合法：左半的最大值不超过右半的最小值
                if ((m + n) % 2 == 1) {
                    return max(l1, l2);
                }
                return (max(l1, l2) + min(r1, r2)) / 2.0;
            }
            if (l1 > r2) {
                right = i - 1;  // nums1 贡献太多，左移分割线
            } else {
                left = i + 1;   // nums1 贡献太少，右移分割线
            }
        }
        return 0.0;  // 输入保证合法，不会到达
    }
};
```

- ⏱️ 时间复杂度：`O(log(min(m, n)))`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 忘记在**较短**的数组上二分：若在较长数组上二分，`j = half - i` 可能为负或超出另一数组长度，直接越界。
- `i`、`j` 的含义是"贡献给左半的**元素个数**"，转成下标取值要减一：`nums1[i-1]` 才是左侧最大值、`nums1[i]` 是右侧最小值。
- 一侧贡献个数为 0 或取满时没有 `nums[i-1]` / `nums[i]` 可取，必须用 `INT_MIN` / `INT_MAX` 哨兵（或等价的分类讨论），否则越界。
- 偶数长度求平均时要用 `/ 2.0` 浮点除法，写成 `/ 2` 会把 2.5 变成 2。

---

[← 返回目录](../../README.md)
