/**
 * @file    0072-edit-distance.cpp
 * @brief   72. 编辑距离
 * @link    https://leetcode.cn/problems/edit-distance/
 *
 * 解法：动态规划（一维滚动数组）
 * 思路：dp[j] 表示 word1 前 i 个字符变成 word2 前 j 个字符的最少操作数，用 prev 保存左上角，逐行从左到右转移。
 * 时间复杂度：O(mn)
 * 空间复杂度：O(n)
 */

#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = (int)word1.size(), n = (int)word2.size();
        vector<int> dp(n + 1);
        for (int j = 0; j <= n; ++j) dp[j] = j;   // 第 0 行：dp[0][j] = j
        for (int i = 1; i <= m; ++i) {
            int prev = dp[0];                      // dp[i-1][0]
            dp[0] = i;                             // dp[i][0] = i
            for (int j = 1; j <= n; ++j) {
                int cur = dp[j];                   // 暂存 dp[i-1][j]
                if (word1[i - 1] == word2[j - 1]) {
                    dp[j] = prev;                  // 末尾对齐，无需操作
                } else {
                    dp[j] = 1 + min({dp[j],        // 删除 word1[i-1]（旧 dp[j]）
                                     dp[j - 1],    // 插入 word2[j-1]
                                     prev});       // 替换
                }
                prev = cur;
            }
        }
        return dp[n];
    }
};
