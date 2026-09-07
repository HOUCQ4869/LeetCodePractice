/**
 * @file    0041-first-missing-positive.cpp
 * @brief   41. 缺失的第一个正数
 * @link    https://leetcode.cn/problems/first-missing-positive/
 *
 * 解法：原地置换
 * 思路：把值 v∈[1,n] 的元素换到下标 v-1 上，整理后第一个 nums[i] != i+1 处即答案，否则为 n+1。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

#include <utility>
#include <vector>

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = (int)nums.size();
        for (int i = 0; i < n; ++i) {
            // 把 nums[i] 换到下标 nums[i]-1，直到当前值越界或已在位
            while (nums[i] >= 1 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (nums[i] != i + 1) return i + 1;
        }
        return n + 1;
    }
};
