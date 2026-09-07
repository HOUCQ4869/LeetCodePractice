/**
 * @file    0155-min-stack.cpp
 * @brief   155. 最小栈
 * @link    https://leetcode.cn/problems/min-stack/
 *
 * 解法：辅助栈
 * 思路：主栈正常存值，辅助栈与主栈同步维护"当前栈内最小值"：
 *      push 时新值 <= 辅助栈顶才入栈（保证重复最小值的个数对齐），
 *      pop 时两栈顶相等则同步弹辅助栈，getMin 直接读辅助栈顶。
 * 时间复杂度：O(1)（每个操作）
 * 空间复杂度：O(n)
 */

#include <stack>

class MinStack {
public:
    MinStack() {}

    void push(int val) {
        st.push(val);
        // 用 <= 保证重复出现的最小值都入辅助栈，弹出时数量才能对上
        if (minSt.empty() || val <= minSt.top()) {
            minSt.push(val);
        }
    }

    void pop() {
        if (st.top() == minSt.top()) {
            minSt.pop();  // 弹出的恰是当前最小值，辅助栈同步弹出
        }
        st.pop();
    }

    int top() {
        return st.top();
    }

    int getMin() {
        return minSt.top();  // 辅助栈顶即当前栈内最小值
    }

private:
    stack<int> st;     // 主栈
    stack<int> minSt;  // 辅助栈：与主栈同步维护最小值
};
