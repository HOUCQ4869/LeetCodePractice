/**
 * @file    0152-maximum-product-subarray.cpp
 * @brief   152. 乘积最大子数组
 * @link    https://leetcode.cn/problems/maximum-product-subarray/
 *
 * 解法：动态规划——同时维护最大与最小乘积
 * 思路：负数会翻转最大/最小，故以 i 结尾同时维护 maxP 与 minP，转移取「延续乘积」与「重新开头」中的较大/较小者。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

#include <vector>
#include <algorithm>

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        long long maxP = nums[0], minP = nums[0];  // 以 i 结尾的最大/最小乘积
        long long best = nums[0];
        for (int i = 1; i < (int)nums.size(); ++i) {
            int x = nums[i];
            if (x < 0) swap(maxP, minP);               // 负数交换大小角色
            maxP = max((long long)x, maxP * x);        // 延续或重新开头
            minP = min((long long)x, minP * x);
            best = max(best, maxP);
        }
        return (int)best;
    }
};
