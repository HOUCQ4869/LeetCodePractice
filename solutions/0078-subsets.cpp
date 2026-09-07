/**
 * @file    0078-subsets.cpp
 * @brief   78. 子集
 * @link    https://leetcode.cn/problems/subsets/
 *
 * 解法：二进制位运算枚举
 * 思路：n 个元素的每个子集唯一对应一个 n 位掩码（第 i 位为 1 表示选 nums[i]），
 *      枚举 0 ~ 2^n - 1 的全部掩码并按位提取元素，天然无重复、无需递归。
 * 时间复杂度：O(n × 2^n)，共 2^n 个子集，每个提取 O(n)
 * 空间复杂度：O(1)，除输出数组外仅常数空间
 */

#include <utility>
#include <vector>

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        vector<vector<int>> ans;
        ans.reserve(1u << n);
        for (int mask = 0; mask < (1 << n); ++mask) {  // 每个掩码对应一个子集
            vector<int> cur;
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) cur.push_back(nums[i]);  // 第 i 位为 1 则选入
            }
            ans.push_back(std::move(cur));
        }
        return ans;
    }
};
