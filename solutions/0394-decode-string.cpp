/**
 * @file    0394-decode-string.cpp
 * @brief   394. 字符串解码
 * @link    https://leetcode.cn/problems/decode-string/
 *
 * 解法：双栈迭代
 * 思路：数字栈存每层括号的重复次数，字符串栈存进入该层前已拼好的串；
 *      遇 '[' 压栈并清空现场，遇 ']' 弹出并拼接 k 份；数字可能多位需累加。
 * 时间复杂度：O(输出串长度)
 * 空间复杂度：O(输出串长度)
 */

#include <string>
#include <stack>
#include <cctype>
#include <utility>

class Solution {
public:
    string decodeString(string s) {
        stack<int> numSt;     // 每层括号的重复次数
        stack<string> strSt;  // 进入该层括号前已拼好的字符串
        string cur;           // 当前层正在构建的字符串
        int num = 0;          // 当前读到的重复次数
        for (char c : s) {
            if (isdigit(c)) {
                num = num * 10 + (c - '0');  // 数字可能有多位
            } else if (c == '[') {
                numSt.push(num);   // 保存现场：重复次数
                strSt.push(cur);   // 保存现场：之前的字符串
                cur.clear();
                num = 0;
            } else if (c == ']') {
                int k = numSt.top();
                numSt.pop();
                string prev = strSt.top();
                strSt.pop();
                for (int t = 0; t < k; t++) {
                    prev += cur;   // 拼出 prev + k 份 cur
                }
                cur = move(prev);
            } else {
                cur += c;  // 普通字母直接追加
            }
        }
        return cur;
    }
};
