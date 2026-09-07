/**
 * @file    0020-valid-parentheses.cpp
 * @brief   20. 有效的括号
 * @link    https://leetcode.cn/problems/valid-parentheses/
 *
 * 解法：栈匹配
 * 思路：遇左括号入栈；遇右括号时栈顶必须是同类型左括号，匹配则弹栈，否则非法；
 *      扫描结束后栈必须为空（防遗漏未匹配的左括号）。
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 */

#include <string>
#include <stack>

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for (char c : s) {
            if (c == '(' || c == '[' || c == '{') {
                st.push(c);  // 左括号入栈
            } else {
                // 右括号出现时栈必须非空，且栈顶是同类型的左括号
                if (st.empty()) return false;
                char t = st.top();
                st.pop();
                if ((c == ')' && t != '(') || (c == ']' && t != '[') ||
                    (c == '}' && t != '{')) {
                    return false;
                }
            }
        }
        return st.empty();  // 栈空说明所有左括号都被匹配
    }
};
