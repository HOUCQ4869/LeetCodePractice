/**
 * @file    0240-search-a-2d-matrix-ii.cpp
 * @brief   240. 搜索二维矩阵 II
 * @link    https://leetcode.cn/problems/search-a-2d-matrix-ii/
 *
 * 解法：Z 字形查找（右上角出发）
 * 思路：右上角是其行的最大值、列的最小值，每次比较可排除一整列（大于）或一整行（小于）。
 * 时间复杂度：O(m + n)
 * 空间复杂度：O(1)
 */

#include <vector>

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = (int)matrix.size(), n = (int)matrix[0].size();
        int x = 0, y = n - 1;  // 从右上角出发
        while (x < m && y >= 0) {
            int v = matrix[x][y];
            if (v == target) return true;
            v > target ? --y : ++x;  // 大于排除当前列，小于排除当前行
        }
        return false;
    }
};
