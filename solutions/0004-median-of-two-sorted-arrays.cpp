/**
 * @file    0004-median-of-two-sorted-arrays.cpp
 * @brief   4. 寻找两个正序数组的中位数
 * @link    https://leetcode.cn/problems/median-of-two-sorted-arrays/
 *
 * 解法：分割线二分（在较短数组上二分）
 * 思路：中位数将合并数组分成等长（奇数时左半多一个）的左右两部分；
 *      在较短数组上二分其贡献给左半的个数 i，另一数组的个数 j 随之确定，
 *      当左半最大值 <= 右半最小值时分割线合法，按总长度奇偶计算中位数。
 * 时间复杂度：O(log(min(m, n)))
 * 空间复杂度：O(1)
 */

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
