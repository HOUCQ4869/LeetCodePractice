/**
 * @file    0238-product-of-array-except-self.cpp
 * @brief   238. 除自身以外数组的乘积
 * @link    https://leetcode.cn/problems/product-of-array-except-self/
 *
 * 解法：前缀积写入输出数组 + 滚动后缀积
 * 思路：正向扫描把前缀积存进 ans，反向扫描用变量 suf 累积后缀积并乘回，无需除法。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)（输出数组不计入）
 */

#include <vector>

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = (int)nums.size();
        vector<int> ans(n);
        ans[0] = 1;
        for (int i = 1; i < n; ++i) {
            ans[i] = ans[i - 1] * nums[i - 1];  // 暂存前缀积
        }
        int suf = 1;  // 滚动后缀积
        for (int i = n - 1; i >= 0; --i) {
            ans[i] *= suf;   // 乘上右边所有数之积
            suf *= nums[i];  // 更新后缀，供更左边的位置使用
        }
        return ans;
    }
};
