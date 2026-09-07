/**
 * @file    0001-two-sum.cpp
 * @brief   1. 两数之和
 * @link    https://leetcode.cn/problems/two-sum/
 *
 * 解法：哈希表
 * 思路：一遍遍历，哈希表记录「数值 -> 下标」；对当前数先查 target 与其之差是否已出现，再把自己入表。
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 */

#include <vector>
#include <unordered_map>

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> hash;
        for (int i = 0; i < (int)nums.size(); i++) {
            int now = nums[i];
            int anthor = target - now;
            if (hash.count(anthor)) {
                return {i, hash[anthor]};
            }
            hash[now] = i;
        }
        return {};
    }
};
