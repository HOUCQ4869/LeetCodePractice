/**
 * @file    1143-longest-common-subsequence.cpp
 * @brief   1143. 最长公共子序列
 * @link    https://leetcode.cn/problems/longest-common-subsequence/
 *
 * 解法：动态规划（一维滚动数组）
 * 思路：dp[j] 滚动保存当前行前 j 列的 LCS 长度，用 prev 保存左上角 dp[i-1][j-1]；短串做列以省空间。
 * 时间复杂度：O(mn)
 * 空间复杂度：O(min(m, n))
 */

#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        if (text1.size() < text2.size()) swap(text1, text2);  // 短串做列，空间更省
        int m = (int)text1.size(), n = (int)text2.size();
        vector<int> dp(n + 1, 0);
        for (int i = 1; i <= m; ++i) {
            int prev = 0;                        // dp[i-1][j-1]，j=1 时即 dp[i-1][0]
            for (int j = 1; j <= n; ++j) {
                int cur = dp[j];                 // 暂存 dp[i-1][j]
                if (text1[i - 1] == text2[j - 1]) {
                    dp[j] = prev + 1;            // 相等：左上角 + 1
                } else {
                    dp[j] = max(dp[j], dp[j - 1]);
                }
                prev = cur;
            }
        }
        return dp[n];
    }
};
