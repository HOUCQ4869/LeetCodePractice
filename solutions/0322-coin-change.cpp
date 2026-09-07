/**
 * @file    0322-coin-change.cpp
 * @brief   322. 零钱兑换
 * @link    https://leetcode.cn/problems/coin-change/
 *
 * 解法：动态规划——完全背包
 * 思路：dp[i] 为凑出金额 i 的最少硬币数，dp[i] = min(dp[i-c] + 1)；不可达用 INT_MAX 表示并防溢出。
 * 时间复杂度：O(amount * n)
 * 空间复杂度：O(amount)
 */

#include <vector>
#include <algorithm>
#include <climits>

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, INT_MAX);  // INT_MAX 表示不可达
        dp[0] = 0;
        for (int i = 1; i <= amount; ++i) {
            for (int c : coins) {
                if (c <= i && dp[i - c] != INT_MAX) {
                    dp[i] = min(dp[i], dp[i - c] + 1);
                }
            }
        }
        return dp[amount] == INT_MAX ? -1 : dp[amount];
    }
};
