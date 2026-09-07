/**
 * @file    0136-single-number.cpp
 * @brief   136. 只出现一次的数字
 * @link    https://leetcode.cn/problems/single-number/
 *
 * 解法：异或
 * 思路：利用 x^x=0 与 x^0=x，全部元素异或后成对者抵消，只剩出现一次的那个数。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

#include <vector>

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ans = 0;
        for (int x : nums) {
            ans ^= x;  // 成对元素抵消为 0，只剩出现一次者
        }
        return ans;
    }
};
