/**
 * @file    0022-generate-parentheses.cpp
 * @brief   22. 括号生成
 * @link    https://leetcode.cn/problems/generate-parentheses/
 *
 * 解法：回溯（构造过程中剪枝）
 * 思路：边生成边保证前缀合法：已放左括号数 open < n 时才能放 '('，
 *      已放右括号数 close < open 时才能放 ')'；长度到达 2n 时收集。
 *      生成的每个串天然合法，无需事后检查。解的个数为第 n 个卡特兰数。
 * 时间复杂度：O(4^n / √n)，卡特兰数的渐近规模乘上每个串的 O(n) 输出
 * 空间复杂度：O(n)，递归栈与 path（不计输出）
 */

#include <string>
#include <vector>

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        string path;
        backtrack(n, 0, 0, path, ans);
        return ans;
    }

private:
    // open / close：已使用的左 / 右括号个数
    void backtrack(int n, int open, int close, string& path, vector<string>& ans) {
        if (static_cast<int>(path.size()) == 2 * n) {
            ans.push_back(path);  // 构造过程中已保证合法
            return;
        }
        if (open < n) {  // 左括号还没用完，可以放 '('
            path.push_back('(');
            backtrack(n, open + 1, close, path, ans);
            path.pop_back();
        }
        if (close < open) {  // 右括号数小于左括号数，前缀仍合法，可放 ')'
            path.push_back(')');
            backtrack(n, open, close + 1, path, ans);
            path.pop_back();
        }
    }
};
