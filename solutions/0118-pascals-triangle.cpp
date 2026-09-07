/**
 * @file    0118-pascals-triangle.cpp
 * @brief   118. 杨辉三角
 * @link    https://leetcode.cn/problems/pascals-triangle/
 *
 * 解法：逐行递推
 * 思路：每行首尾为 1，中间元素等于上一行左右两数之和，逐行构造。
 * 时间复杂度：O(numRows^2)
 * 空间复杂度：O(1)（不计返回值）
 */

#include <vector>

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res;
        for (int i = 0; i < numRows; ++i) {
            vector<int> row(i + 1, 1);  // 首尾先置 1
            for (int j = 1; j < i; ++j) {
                row[j] = res[i - 1][j - 1] + res[i - 1][j];  // 左上 + 右上
            }
            res.push_back(move(row));
        }
        return res;
    }
};
