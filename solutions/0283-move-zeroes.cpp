/**
 * @file    0283-move-zeroes.cpp
 * @brief   283. 移动零
 * @link    https://leetcode.cn/problems/move-zeroes/
 *
 * 解法：双指针交换
 * 思路：slow 指向下一个非零元素应放的位置，遍历中遇到非零就与 slow 位置交换，零自然被换到尾部。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

#include <vector>
#include <utility>

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        for (int slow = 0, fast = 0; fast < static_cast<int>(nums.size()); ++fast) {
            if (nums[fast] != 0) {
                swap(nums[slow], nums[fast]);  // slow 处必为 0（或即自身），交换不破坏相对顺序
                ++slow;
            }
        }
    }
};
