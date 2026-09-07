/**
 * @file    0438-find-all-anagrams-in-a-string.cpp
 * @brief   438. 找到字符串中所有字母异位词
 * @link    https://leetcode.cn/problems/find-all-anagrams-in-a-string/
 *
 * 解法：定长滑动窗口 + 差异计数
 * 思路：维护「p 的计数 - 窗口计数」差值数组与差值非零的字母数 differ，differ 为 0 即命中异位词。
 * 时间复杂度：O(n + m)，n = |s|，m = |p|
 * 空间复杂度：O(|Σ|)，|Σ| = 26
 */

#include <string>
#include <vector>
#include <array>

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int n = static_cast<int>(s.size());
        int m = static_cast<int>(p.size());
        vector<int> ans;
        if (n < m) return ans;
        array<int, 26> cnt{};  // need - win 的差值
        for (char c : p) {
            ++cnt[c - 'a'];
        }
        for (int i = 0; i < m; ++i) {
            --cnt[s[i] - 'a'];
        }
        int differ = 0;  // 差值非零的字母个数
        for (int x : cnt) {
            if (x != 0) ++differ;
        }
        if (differ == 0) ans.push_back(0);
        for (int i = m; i < n; ++i) {
            int in = s[i] - 'a', out = s[i - m] - 'a';
            if (cnt[in] == 0) ++differ;   // 进入字符：差值将从 0 变为 -1
            --cnt[in];
            if (cnt[in] == 0) --differ;
            if (cnt[out] == 0) ++differ;  // 离开字符：差值将从 0 变为 +1
            ++cnt[out];
            if (cnt[out] == 0) --differ;
            if (differ == 0) ans.push_back(i - m + 1);
        }
        return ans;
    }
};
