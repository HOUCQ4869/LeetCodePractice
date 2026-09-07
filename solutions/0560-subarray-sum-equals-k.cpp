/**
 * @file    0560-subarray-sum-equals-k.cpp
 * @brief   560. 和为 K 的子数组
 * @link    https://leetcode.cn/problems/subarray-sum-equals-k/
 *
 * 解法：前缀和 + 哈希表
 * 思路：哈希表记录每个前缀和出现的次数；扫到位置 j 时查询 pre - k 的次数，即得以 j 结尾的合法子数组数。
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 */

#include <vector>
#include <unordered_map>

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> cnt;  // 前缀和 -> 出现次数
        cnt[0] = 1;                   // 空前缀，用于统计从下标 0 开始的子数组
        int pre = 0, ans = 0;
        for (int x : nums) {
            pre += x;
            auto it = cnt.find(pre - k);
            if (it != cnt.end()) {
                ans += it->second;  // 这些前缀结束位置的下一格，都能构成和为 k 的子数组
            }
            ++cnt[pre];  // 先查询、后插入，避免把空子数组统计进去
        }
        return ans;
    }
};
