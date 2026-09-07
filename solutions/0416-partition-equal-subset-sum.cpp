/**
 * @file    0416-partition-equal-subset-sum.cpp
 * @brief   416. 分割等和子集
 * @link    https://leetcode.cn/problems/partition-equal-subset-sum/
 *
 * 解法：一维 01 背包
 * 思路：问题转化为能否从数组中选出和恰为 sum/2 的子集，dp[j] 表示可否凑出 j，容量倒序遍历保证每数只选一次。
 * 时间复杂度：O(n * target)
 * 空间复杂度：O(target)
 */

#include <vector>
#include <numeric>

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 == 1) return false;
        int target = sum / 2;

        vector<char> dp(target + 1, 0);  // char 当布尔用
        dp[0] = true;
        for (int x : nums) {
            for (int j = target; j >= x; --j) {  // 倒序：保证每数只用一次
                if (dp[j - x]) dp[j] = 1;
            }
        }
        return dp[target];
    }
};
