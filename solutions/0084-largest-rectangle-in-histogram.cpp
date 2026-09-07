/**
 * @file    0084-largest-rectangle-in-histogram.cpp
 * @brief   84. 柱状图中最大的矩形
 * @link    https://leetcode.cn/problems/largest-rectangle-in-histogram/
 *
 * 解法：单调栈 + 哨兵
 * 思路：维护高度单调递增的栈（存下标）。新柱更矮时弹栈结算：
 *      弹出柱的高度为矩形高，左边界为弹出后的新栈顶，右边界为当前下标 i；
 *      末尾追加高度 0 的哨兵强制清空整栈，保证所有柱子都被结算。
 * 时间复杂度：O(n)（每个下标至多入栈、出栈一次）
 * 空间复杂度：O(n)
 */

#include <vector>
#include <stack>
#include <algorithm>

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        stack<int> stk;  // 存下标，对应高度从栈底到栈顶单调递增
        int ans = 0;
        // i == n 时用高度 0 作哨兵，强制清空栈内所有柱子
        for (int i = 0; i <= n; i++) {
            int cur = (i == n) ? 0 : heights[i];
            while (!stk.empty() && cur < heights[stk.top()]) {
                int h = heights[stk.top()];
                stk.pop();
                // 左边界为弹出后新栈顶（不含），栈空则延伸到最左端 -1
                int left = stk.empty() ? -1 : stk.top();
                ans = max(ans, h * (i - left - 1));
            }
            stk.push(i);
        }
        return ans;
    }
};
