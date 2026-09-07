/**
 * @file    0076-minimum-window-substring.cpp
 * @brief   76. 最小覆盖子串
 * @link    https://leetcode.cn/problems/minimum-window-substring/
 *
 * 解法：滑动窗口 + 有效字符计数
 * 思路：右指针扩张、左指针收缩；用 formed / required 两个计数把「窗口是否覆盖 t」变成 O(1) 判断。
 * 时间复杂度：O(n + m)，n = |s|，m = |t|
 * 空间复杂度：O(|Σ|)，|Σ| = 128
 */

#include <string>
#include <array>
#include <climits>

class Solution {
public:
    string minWindow(string s, string t) {
        array<int, 128> need{};
        for (char c : t) {
            ++need[c];
        }
        int required = 0;  // t 中出现过的字符种数
        for (int x : need) {
            if (x > 0) ++required;
        }
        array<int, 128> win{};
        int formed = 0;  // 窗口内已凑够次数的字符种数
        int bestLen = INT_MAX, bestStart = 0;
        int l = 0;
        for (int r = 0; r < static_cast<int>(s.size()); ++r) {
            char c = s[r];
            ++win[c];
            if (need[c] > 0 && win[c] == need[c]) ++formed;  // 恰好凑够一种
            while (formed == required) {                      // 已覆盖，收缩左边界
                if (r - l + 1 < bestLen) {
                    bestLen = r - l + 1;
                    bestStart = l;
                }
                char d = s[l++];
                if (need[d] > 0 && win[d] == need[d]) --formed;  // 先判断再减计数
                --win[d];
            }
        }
        return bestLen == INT_MAX ? "" : s.substr(bestStart, bestLen);
    }
};
