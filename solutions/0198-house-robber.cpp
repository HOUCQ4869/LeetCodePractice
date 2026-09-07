/**
 * @file    0198-house-robber.cpp
 * @brief   198. 打家劫舍
 * @link    https://leetcode.cn/problems/house-robber/
 *
 * 解法：动态规划 + 滚动变量
 * 思路：dp[i] = max(dp[i-1], dp[i-2] + nums[i])，偷或不偷第 i 间取较大者，仅用两个变量滚动。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

#include <vector>
#include <algorithm>

class Solution {
public:
    int rob(vector<int>& nums) {
        int prev = 0, curr = 0;  // dp[i-2], dp[i-1]
        for (int x : nums) {
            int next = max(curr, prev + x);  // 不偷 i 或 偷 i
            prev = curr;
            curr = next;
        }
        return curr;
    }
};
