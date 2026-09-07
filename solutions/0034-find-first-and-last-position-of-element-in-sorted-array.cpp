/**
 * @file    0034-find-first-and-last-position-of-element-in-sorted-array.cpp
 * @brief   34. 在排序数组中查找元素的第一个和最后一个位置
 * @link    https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/
 *
 * 解法：两次二分（lower_bound + upper_bound）
 * 思路：先用左边界二分找第一个 >= target 的位置 start，若越界或不等于 target 则不存在；
 *      再用右边界二分找第一个 > target 的位置，其前一位即最后一个等于 target 的位置。
 * 时间复杂度：O(log n)
 * 空间复杂度：O(1)
 */

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
