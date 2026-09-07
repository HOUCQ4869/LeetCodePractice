/**
 * @file    0032-longest-valid-parentheses.cpp
 * @brief   32. 最长有效括号
 * @link    https://leetcode.cn/problems/longest-valid-parentheses/
 *
 * 解法：双向扫描计数
 * 思路：正反各扫一遍，用 left/right 计数，相等时更新答案、失衡时清零，两个方向合起来覆盖所有有效段。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

#include <string>
#include <algorithm>

class Solution {
public:
    int longestValidParentheses(string s) {
        int n = (int)s.size();
        int best = 0;

        // 从左到右：right 超过 left 即失效
        int left = 0, right = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '(') ++left; else ++right;
            if (left == right) {
                best = max(best, 2 * right);
            } else if (right > left) {
                left = right = 0;
            }
        }

        // 从右到左：left 超过 right 即失效
        left = right = 0;
        for (int i = n - 1; i >= 0; --i) {
            if (s[i] == '(') ++left; else ++right;
            if (left == right) {
                best = max(best, 2 * left);
            } else if (left > right) {
                left = right = 0;
            }
        }
        return best;
    }
};
