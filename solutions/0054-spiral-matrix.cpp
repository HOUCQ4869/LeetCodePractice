/**
 * @file    0054-spiral-matrix.cpp
 * @brief   54. 螺旋矩阵
 * @link    https://leetcode.cn/problems/spiral-matrix/
 *
 * 解法：四边界收缩
 * 思路：维护 top/bottom/left/right 四个边界，按上、右、下、左顺序遍历一圈后收缩，直至边界交叉。
 * 时间复杂度：O(mn)
 * 空间复杂度：O(1)（输出不计）
 */

#include <vector>

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = (int)matrix.size(), n = (int)matrix[0].size();
        int top = 0, bottom = m - 1, left = 0, right = n - 1;
        vector<int> ans;
        ans.reserve(m * n);
        while (top <= bottom && left <= right) {
            for (int j = left; j <= right; ++j) ans.push_back(matrix[top][j]);        // 上边
            for (int i = top + 1; i <= bottom; ++i) ans.push_back(matrix[i][right]);  // 右边
            if (top < bottom && left < right) {  // 剩多行多列才有下边、左边
                for (int j = right - 1; j >= left; --j) ans.push_back(matrix[bottom][j]);  // 下边
                for (int i = bottom - 1; i > top; --i) ans.push_back(matrix[i][left]);    // 左边
            }
            ++top; --bottom; ++left; --right;  // 边界收缩，进入内圈
        }
        return ans;
    }
};
