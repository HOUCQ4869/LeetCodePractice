/**
 * @file    0075-sort-colors.cpp
 * @brief   75. 颜色分类
 * @link    https://leetcode.cn/problems/sort-colors/
 *
 * 解法：三指针一趟扫描
 * 思路：p0/p2 维护 0 段右边界与 2 段左边界，i 扫描中段；遇 0 换左进 i，遇 2 换右不进 i，遇 1 直接过。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

#include <utility>
#include <vector>

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = (int)nums.size();
        int p0 = 0, p2 = n - 1;  // [0,p0) 全 0，(p2,n-1] 全 2
        for (int i = 0; i <= p2; ) {
            if (nums[i] == 0) {
                swap(nums[i], nums[p0]);
                ++p0;
                ++i;  // 换回来的一定是 1（或自身），可直接前进
            } else if (nums[i] == 2) {
                swap(nums[i], nums[p2]);
                --p2;
                // 换回来的值未知，i 不动，继续处理当前位置
            } else {
                ++i;  // nums[i] == 1，天然属于中段
            }
        }
    }
};
