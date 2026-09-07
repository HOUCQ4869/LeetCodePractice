/**
 * @file    0031-next-permutation.cpp
 * @brief   31. 下一个排列
 * @link    https://leetcode.cn/problems/next-permutation/
 *
 * 解法：两遍扫描 + 反转
 * 思路：从右找第一个升序位 i，再从右找第一个大于 nums[i] 的 j，交换后反转 i+1 之后的后缀；无 i 时整体反转。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

#include <algorithm>
#include <utility>
#include <vector>

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = (int)nums.size();
        // 1. 从右找第一个升序对 nums[i] < nums[i+1]
        int i = n - 2;
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            --i;
        }
        if (i >= 0) {
            // 2. 从右找第一个大于 nums[i] 的 nums[j]
            int j = n - 1;
            while (nums[j] <= nums[i]) {
                --j;
            }
            // 3. 交换，完成最小幅度提升
            swap(nums[i], nums[j]);
        }
        // 4. 反转后缀（i == -1 时即整体反转，回到最小排列）
        reverse(nums.begin() + i + 1, nums.end());
    }
};
