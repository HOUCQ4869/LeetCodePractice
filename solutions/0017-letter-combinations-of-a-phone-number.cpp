/**
 * @file    0017-letter-combinations-of-a-phone-number.cpp
 * @brief   17. 电话号码的字母组合
 * @link    https://leetcode.cn/problems/letter-combinations-of-a-phone-number/
 *
 * 解法：回溯
 * 思路：path 逐位追加字符，pos 扫到 digits 末尾时收集一份拷贝；
 *      每层枚举当前数字对应的全部字母，递归后撤销最后追加的字符。
 * 时间复杂度：O(4^n × n)，n 为数字位数（7、9 各对应 4 个字母）
 * 空间复杂度：O(n)，递归栈与 path（不计输出）
 */

#include <string>
#include <vector>

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};  // 空输入返回空数组，而不是 [""]

        // 下标即数字：0、1 没有对应字母，占位为空串
        const vector<string> mapping = {"", "", "abc", "def", "ghi",
                                        "jkl", "mno", "pqrs", "tuv", "wxyz"};
        vector<string> ans;
        string path;
        backtrack(digits, 0, mapping, path, ans);
        return ans;
    }

private:
    void backtrack(const string& digits, int pos, const vector<string>& mapping,
                   string& path, vector<string>& ans) {
        if (pos == static_cast<int>(digits.size())) {
            ans.push_back(path);  // 每个数字都选定了一个字母
            return;
        }
        for (char ch : mapping[digits[pos] - '0']) {  // 只枚举当前数字的字母
            path.push_back(ch);
            backtrack(digits, pos + 1, mapping, path, ans);
            path.pop_back();  // 回溯：撤销选择
        }
    }
};
