/**
 * @file    0011-container-with-most-water.cpp
 * @brief   11. 盛最多水的容器
 * @link    https://leetcode.cn/problems/container-with-most-water/
 *
 * 解法：双指针 + 贪心收缩
 * 思路：左右指针从两端出发，每次移动较短的一侧——宽度不断减小，保留短板一侧不可能得到更优解。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

#include <vector>
#include <algorithm>

class Solution {
public:
    int maxArea(vector<int>& height) {
        int best = 0;
        int l = 0, r = static_cast<int>(height.size()) - 1;
        while (l < r) {
            // 面积 = 宽度 * 短板高度
            int area = (r - l) * min(height[l], height[r]);
            best = max(best, area);
            if (height[l] < height[r]) {
                ++l;  // 短板一侧不可能再参与更优解，安全舍弃
            } else {
                --r;
            }
        }
        return best;
    }
};
