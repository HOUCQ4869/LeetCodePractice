/**
 * @file    0131-palindrome-partitioning.cpp
 * @brief   131. 分割回文串
 * @link    https://leetcode.cn/problems/palindrome-partitioning/
 *
 * 解法：回溯 + 区间 DP 预处理回文表
 * 思路：先 O(n^2) 预处理 isPal[i][j]（s[i]==s[j] 且去掉两端后仍是回文），
 *      回溯时从 start 枚举每一段的结尾 end，isPal[start][end] 成立才切段递归，
 *      回文判断降为 O(1)。start 走到串尾即收集一份切分方案。
 * 时间复杂度：O(n × 2^n)，切分方案总数上界 2^(n-1)，每份拷贝 O(n)
 * 空间复杂度：O(n^2)，回文表（递归栈 O(n)）
 */

#include <string>
#include <vector>

class Solution {
public:
    vector<vector<string>> partition(string s) {
        int n = static_cast<int>(s.size());
        // isPal[i][j]：s[i..j] 是否为回文串
        vector<vector<bool>> isPal(n, vector<bool>(n, false));
        for (int i = n - 1; i >= 0; --i) {  // i 从大到小，保证 i+1 行先算好
            for (int j = i; j < n; ++j) {
                isPal[i][j] = (s[i] == s[j]) && (j - i < 2 || isPal[i + 1][j - 1]);
            }
        }

        vector<vector<string>> ans;
        vector<string> path;
        backtrack(s, 0, isPal, path, ans);
        return ans;
    }

private:
    void backtrack(const string& s, int start, const vector<vector<bool>>& isPal,
                   vector<string>& path, vector<vector<string>>& ans) {
        if (start == static_cast<int>(s.size())) {  // 整串切分完毕
            ans.push_back(path);
            return;
        }
        for (int end = start; end < static_cast<int>(s.size()); ++end) {
            if (!isPal[start][end]) continue;  // 不是回文的段直接跳过
            path.push_back(s.substr(start, end - start + 1));
            backtrack(s, end + 1, isPal, path, ans);
            path.pop_back();
        }
    }
};
