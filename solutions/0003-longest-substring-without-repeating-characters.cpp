/**
 * @file    0003-longest-substring-without-repeating-characters.cpp
 * @brief   3. 无重复字符的最长子串
 * @link    https://leetcode.cn/problems/longest-substring-without-repeating-characters/
 *
 * 解法：滑动窗口 + 记录最后出现位置
 * 思路：last[c] 记录字符 c 最近出现的下标；右指针遇到窗口内的重复字符时，左边界直接跳到其后一位。
 * 时间复杂度：O(n)
 * 空间复杂度：O(|Σ|)，|Σ| = 128
 */

#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> last(128, -1);  // 每个字符最后出现的下标
        int best = 0;
        for (int l = 0, r = 0; r < static_cast<int>(s.size()); ++r) {
            int c = static_cast<unsigned char>(s[r]);
            if (last[c] >= l) {
                l = last[c] + 1;  // 重复字符仍在窗口内，左边界直接跳过它
            }
            last[c] = r;
            best = max(best, r - l + 1);
        }
        return best;
    }
};
