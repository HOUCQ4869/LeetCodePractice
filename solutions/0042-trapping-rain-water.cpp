/**
 * @file    0042-trapping-rain-water.cpp
 * @brief   42. 接雨水
 * @link    https://leetcode.cn/problems/trapping-rain-water/
 *
 * 解法：双指针
 * 思路：维护两侧实时最大值 lMax/rMax，哪侧最大值更小就结算哪侧——该侧水位只取决于自身最大值。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

#include <vector>
#include <algorithm>

class Solution {
public:
    int trap(vector<int>& height) {
        int n = static_cast<int>(height.size());
        if (n < 3) return 0;  // 少于三根柱子无法积水
        int l = 0, r = n - 1;
        int lMax = 0, rMax = 0, ans = 0;
        while (l < r) {
            lMax = max(lMax, height[l]);
            rMax = max(rMax, height[r]);
            if (lMax < rMax) {
                ans += lMax - height[l];  // 右侧必有更高的柱，左侧水位由 lMax 决定
                ++l;
            } else {
                ans += rMax - height[r];  // 左侧必有不低于 lMax 的柱，右侧水位由 rMax 决定
                --r;
            }
        }
        return ans;
    }
};
