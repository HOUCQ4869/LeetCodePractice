/**
 * @file    0035-search-insert-position.cpp
 * @brief   35. 搜索插入位置
 * @link    https://leetcode.cn/problems/search-insert-position/
 *
 * 解法：二分查找（lower_bound 左边界模板）
 * 思路：等价于求第一个大于等于 target 的下标；左闭右开区间内二分，
 *      nums[mid] < target 则收缩左侧，否则保留 mid 为候选，收敛即插入位置。
 * 时间复杂度：O(log n)
 * 空间复杂度：O(1)
 */

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
