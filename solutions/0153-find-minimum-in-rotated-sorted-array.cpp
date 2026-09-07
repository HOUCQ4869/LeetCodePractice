/**
 * @file    0153-find-minimum-in-rotated-sorted-array.cpp
 * @brief   153. 寻找旋转排序数组中的最小值
 * @link    https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array/
 *
 * 解法：二分查找（与右端点比较）
 * 思路：元素互异。nums[mid] > nums[right] 说明最小值在 (mid, right]；
 *      否则 [left, mid] 有序，最小值在 [left, mid]（mid 本身可能就是），收缩到收敛。
 * 时间复杂度：O(log n)
 * 空间复杂度：O(1)
 */

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
