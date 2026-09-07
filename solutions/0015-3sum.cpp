/**
 * @file    0015-3sum.cpp
 * @brief   15. 三数之和
 * @link    https://leetcode.cn/problems/3sum/
 *
 * 解法：排序 + 固定首数 + 双指针
 * 思路：排序后枚举首数 nums[i]，在 (i, n) 区间用双指针找两数之和为 -nums[i]，过程中三层去重。
 * 时间复杂度：O(n^2)
 * 空间复杂度：O(log n)，排序递归栈开销
 */

#include <vector>
#include <algorithm>

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());
        int n = static_cast<int>(nums.size());
        for (int i = 0; i < n - 2; ++i) {
            if (nums[i] > 0) break;                         // 最小数已为正，三数之和不可能为 0
            if (i > 0 && nums[i] == nums[i - 1]) continue;  // 首数去重
            int l = i + 1, r = n - 1;
            while (l < r) {
                int sum = nums[i] + nums[l] + nums[r];
                if (sum < 0) {
                    ++l;
                } else if (sum > 0) {
                    --r;
                } else {
                    ans.push_back({nums[i], nums[l], nums[r]});
                    while (l < r && nums[l] == nums[l + 1]) ++l;  // 第二数去重
                    while (l < r && nums[r] == nums[r - 1]) --r;  // 第三数去重
                    ++l;
                    --r;
                }
            }
        }
        return ans;
    }
};
