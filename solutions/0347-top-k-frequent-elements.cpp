/**
 * @file    0347-top-k-frequent-elements.cpp
 * @brief   347. 前 K 个高频元素
 * @link    https://leetcode.cn/problems/top-k-frequent-elements/
 *
 * 解法：哈希计数 + 桶排序
 * 思路：统计频次后按下标 i 建"出现 i 次"的桶，从高频桶到低频桶收集前 k 个元素，避免比较排序。
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 */

#include <vector>
#include <unordered_map>

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int n = (int)nums.size();
        unordered_map<int, int> cnt;
        for (int x : nums) ++cnt[x];

        // buckets[i] 存放出现次数恰为 i 的所有元素
        vector<vector<int>> buckets(n + 1);
        for (auto& [x, c] : cnt) buckets[c].push_back(x);

        vector<int> res;
        for (int i = n; i >= 1 && (int)res.size() < k; --i) {
            for (int x : buckets[i]) {
                res.push_back(x);
                if ((int)res.size() == k) break;
            }
        }
        return res;
    }
};
