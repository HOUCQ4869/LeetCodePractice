/**
 * @file    0139-word-break.cpp
 * @brief   139. 单词拆分
 * @link    https://leetcode.cn/problems/word-break/
 *
 * 解法：动态规划
 * 思路：dp[i] 表示前 i 个字符可否由字典拼出，枚举最后单词起点 j，dp[i] = dp[j] && dict.count(s.substr(j, i - j))。
 * 时间复杂度：O(n^2 * m)
 * 空间复杂度：O(n + 字典总长)
 */

#include <string>
#include <vector>
#include <unordered_set>

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        int n = (int)s.size();
        vector<bool> dp(n + 1, false);
        dp[0] = true;  // 空串可拼出
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                // 前缀 s[0..j) 可拼，且 s[j..i) 是字典单词
                if (dp[j] && dict.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[n];
    }
};
