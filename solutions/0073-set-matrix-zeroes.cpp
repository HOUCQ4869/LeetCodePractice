/**
 * @file    0073-set-matrix-zeroes.cpp
 * @brief   73. 矩阵置零
 * @link    https://leetcode.cn/problems/set-matrix-zeroes/
 *
 * 解法：首行首列做标记
 * 思路：用第 0 行/第 0 列记录各行列是否置零，自身需求用两个布尔变量保存并最后处理。
 * 时间复杂度：O(mn)
 * 空间复杂度：O(1)
 */

#include <vector>

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = (int)matrix.size(), n = (int)matrix[0].size();
        bool firstRow = false, firstCol = false;
        for (int j = 0; j < n; ++j) firstRow |= (matrix[0][j] == 0);  // 第 0 行自身含 0？
        for (int i = 0; i < m; ++i) firstCol |= (matrix[i][0] == 0);  // 第 0 列自身含 0？

        // 用首行首列记录内部格子的置零需求
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == 0) matrix[i][0] = matrix[0][j] = 0;
            }
        }
        // 依据标记处理内部格子
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) matrix[i][j] = 0;
            }
        }
        // 最后处理首行首列自身
        if (firstRow) {
            for (int j = 0; j < n; ++j) matrix[0][j] = 0;
        }
        if (firstCol) {
            for (int i = 0; i < m; ++i) matrix[i][0] = 0;
        }
    }
};
