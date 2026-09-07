/**
 * @file    0033-search-in-rotated-sorted-array.cpp
 * @brief   33. 搜索旋转排序数组
 * @link    https://leetcode.cn/problems/search-in-rotated-sorted-array/
 *
 * 解法：一次二分（判断哪半边有序）
 * 思路：从 mid 切开后必有一半有序：nums[left] <= nums[mid] 时左半有序，否则右半有序；
 *      target 落在有序半区的首尾范围内则收缩到该半，否则收缩到另一半，每轮排除一半。
 * 时间复杂度：O(log n)
 * 空间复杂度：O(1)
 */

#include <vector>

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;  // 闭区间
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) return mid;
            if (nums[left] <= nums[mid]) {
                // 左半 [left, mid] 有序
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;  // target 落在左半
                } else {
                    left = mid + 1;
                }
            } else {
                // 右半 [mid, right] 有序
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;  // target 落在右半
                } else {
                    right = mid - 1;
                }
            }
        }
        return -1;
    }
};
