/**
 * @file    0048-rotate-image.cpp
 * @brief   48. 旋转图像
 * @link    https://leetcode.cn/problems/rotate-image/
 *
 * 解法：转置 + 左右翻转
 * 思路：先沿主对角线转置（(i,j)→(j,i)），再每行左右翻转（(j,i)→(j,n-1-i)），合成顺时针 90°。
 * 时间复杂度：O(n^2)
 * 空间复杂度：O(1)
 */

#include <algorithm>
#include <utility>
#include <vector>

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = (int)matrix.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                swap(matrix[i][j], matrix[j][i]);  // 主对角线转置
            }
        }
        for (auto& row : matrix) {
            reverse(row.begin(), row.end());  // 左右翻转
        }
    }
};
