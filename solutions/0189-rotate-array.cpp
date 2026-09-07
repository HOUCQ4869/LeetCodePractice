/**
 * @file    0189-rotate-array.cpp
 * @brief   189. 轮转数组
 * @link    https://leetcode.cn/problems/rotate-array/
 *
 * 解法：三次翻转
 * 思路：先整体翻转，再分别翻转前 k 个与后 n-k 个元素，即得向右轮转 k 步的结果。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

#include <algorithm>
#include <vector>

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = (int)nums.size();
        k %= n;  // k 可能大于等于 n
        reverse(nums.begin(), nums.end());           // 1. 整体翻转
        reverse(nums.begin(), nums.begin() + k);     // 2. 翻转前 k 个
        reverse(nums.begin() + k, nums.end());       // 3. 翻转后 n-k 个
    }
};
