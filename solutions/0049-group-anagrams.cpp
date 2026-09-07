/**
 * @file    0049-group-anagrams.cpp
 * @brief   49. 字母异位词分组
 * @link    https://leetcode.cn/problems/group-anagrams/
 *
 * 解法：计数编码作为哈希键
 * 思路：统计每个字符串 26 个字母的出现次数并拼成带分隔符的键，互为异位词的键必相同，哈希表分组后汇总。
 * 时间复杂度：O(n * k)，n 为字符串数量，k 为字符串最大长度
 * 空间复杂度：O(n * k)
 */

#include <vector>
#include <string>
#include <array>
#include <unordered_map>

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;
        for (const string& s : strs) {
            array<int, 26> cnt{};
            for (char c : s) {
                ++cnt[c - 'a'];
            }
            string key;
            for (int x : cnt) {  // 用 '#' 分隔，避免 "1|11" 与 "11|1" 之类的键冲突
                key += to_string(x);
                key += '#';
            }
            groups[key].push_back(s);
        }
        vector<vector<string>> ans;
        ans.reserve(groups.size());
        for (auto& kv : groups) {
            ans.push_back(move(kv.second));
        }
        return ans;
    }
};
