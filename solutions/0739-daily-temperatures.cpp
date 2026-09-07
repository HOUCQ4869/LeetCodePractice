/**
 * @file    0739-daily-temperatures.cpp
 * @brief   739. 每日温度
 * @link    https://leetcode.cn/problems/daily-temperatures/
 *
 * 解法：单调栈（存下标，栈内温度递减）
 * 思路：遍历温度，把尚无答案的下标压栈维持递减；遇到更高温度时
 *      不断弹栈，为每个弹出的下标结算"下一个更高温度"的距离。
 * 时间复杂度：O(n)（每个下标至多入栈、出栈一次）
 * 空间复杂度：O(n)
 */

#include <vector>
#include <stack>

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> ans(n, 0);
        stack<int> stk;  // 存下标，对应温度从栈底到栈顶单调递减
        for (int i = 0; i < n; i++) {
            // 当前温度比栈顶高：栈顶那一天找到了"下一个更高温度"
            while (!stk.empty() && temperatures[i] > temperatures[stk.top()]) {
                int j = stk.top();
                stk.pop();
                ans[j] = i - j;
            }
            stk.push(i);
        }
        // 循环结束后仍在栈中的下标没有更暖的一天，答案保持 0
        return ans;
    }
};
