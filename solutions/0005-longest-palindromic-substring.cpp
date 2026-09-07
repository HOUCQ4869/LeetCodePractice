/**
 * @file    0005-longest-palindromic-substring.cpp
 * @brief   5. 最长回文子串
 * @link    https://leetcode.cn/problems/longest-palindromic-substring/
 *
 * 解法：中心扩展
 * 思路：枚举 2n-1 个回文中心（字符与间隙），从中心向两侧扩张直到失配，记录最长回文的起点与长度。
 * 时间复杂度：O(n^2)
 * 空间复杂度：O(1)
 */

#include <string>

class Solution {
public:
    string longestPalindrome(string s) {
        int n = (int)s.size();
        if (n < 2) return s;
        int start = 0, bestLen = 1;
        // 下标 c 为偶数时中心是字符 c/2，为奇数时是 (c/2, c/2+1) 的间隙
        for (int c = 0; c < 2 * n - 1; ++c) {
            int l = c / 2, r = l + c % 2;
            while (l >= 0 && r < n && s[l] == s[r]) {  // 从中心向两侧扩张
                --l;
                ++r;
            }
            int len = r - l - 1;                       // 失配后回退一步
            if (len > bestLen) {
                bestLen = len;
                start = l + 1;
            }
        }
        return s.substr(start, bestLen);
    }
};
