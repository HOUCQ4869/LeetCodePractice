/**
 * @file    0300-longest-increasing-subsequence.cpp
 * @brief   300. 最长递增子序列
 * @link    https://leetcode.cn/problems/longest-increasing-subsequence/
 *
 * 解法：贪心 + 二分查找
 * 思路：tails[k] 维护长度 k+1 的严格递增子序列的最小结尾，新元素能延长则尾插，否则二分替换第一个 >= x 的结尾。
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(n)
 */

#include <vector>
#include <algorithm>

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> tails;  // tails[k]：长度 k+1 的递增子序列的最小结尾
        for (int x : nums) {
            auto it = lower_bound(tails.begin(), tails.end(), x);
            if (it == tails.end()) {
                tails.push_back(x);  // 比所有结尾都大，LIS 变长
            } else {
                *it = x;  // 替换为更小的结尾，保持潜力
            }
        }
        return (int)tails.size();
    }
};
