/**
 * @file    0053-maximum-subarray.cpp
 * @brief   53. 最大子数组和
 * @link    https://leetcode.cn/problems/maximum-subarray/
 *
 * 解法：Kadane 算法（滚动变量动态规划）
 * 思路：cur 维护以当前元素结尾的最大子数组和，前缀贡献为负则舍弃重开；ans 取全局最大。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

#include <climits>
#include <vector>

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int cur = 0, ans = INT_MIN;
        for (int x : nums) {
            cur = max(cur, 0) + x;  // 前缀贡献为负则舍弃，重新开段
            ans = max(ans, cur);
        }
        return ans;
    }
};
