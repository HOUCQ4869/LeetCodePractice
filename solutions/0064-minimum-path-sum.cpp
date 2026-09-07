/**
 * @file    0064-minimum-path-sum.cpp
 * @brief   64. 最小路径和
 * @link    https://leetcode.cn/problems/minimum-path-sum/
 *
 * 解法：动态规划（一维滚动数组）
 * 思路：dp[j] 滚动保存走到当前行第 j 列的最小路径和，逐行从左到右更新 dp[j] = grid[i][j] + min(dp[j], dp[j-1])。
 * 时间复杂度：O(mn)
 * 空间复杂度：O(n)
 */

#include <vector>
#include <algorithm>

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = (int)grid.size(), n = (int)grid[0].size();
        vector<int> dp(n);
        dp[0] = grid[0][0];
        for (int j = 1; j < n; ++j) dp[j] = dp[j - 1] + grid[0][j];  // 首行：只能从左来
        for (int i = 1; i < m; ++i) {
            dp[0] += grid[i][0];                                      // 首列：只能从上来
            for (int j = 1; j < n; ++j) {
                dp[j] = grid[i][j] + min(dp[j], dp[j - 1]);           // 上方旧值与左侧新值取小
            }
        }
        return dp[n - 1];
    }
};
