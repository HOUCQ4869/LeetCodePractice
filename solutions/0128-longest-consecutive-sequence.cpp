/**
 * @file    0128-longest-consecutive-sequence.cpp
 * @brief   128. 最长连续序列
 * @link    https://leetcode.cn/problems/longest-consecutive-sequence/
 *
 * 解法：哈希集合 + 只从起点扩展
 * 思路：全部数放入 unordered_set；仅当 x-1 不在集合中时 x 才是某段起点，从起点沿 +1 方向探测段长。
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 */

#include <vector>
#include <algorithm>
#include <unordered_set>

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> S(nums.begin(), nums.end());
        int best = 0;
        for (int x : S) {
            if (S.count(x - 1)) continue;  // x 不是段的起点，跳过，避免 O(n^2) 重复扫描
            int len = 1;
            while (S.count(x + len)) {     // 沿连续段向右探测
                ++len;
            }
            best = max(best, len);
        }
        return best;
    }
};
