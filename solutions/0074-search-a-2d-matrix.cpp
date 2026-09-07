/**
 * @file    0074-search-a-2d-matrix.cpp
 * @brief   74. 搜索二维矩阵
 * @link    https://leetcode.cn/problems/search-a-2d-matrix/
 *
 * 解法：展平为一维的一次二分查找
 * 思路：每行首元素大于上一行末元素，逐行连接后是有序数组；
 *      对一维下标 [0, m*n) 二分，mid 映射回 matrix[mid/n][mid%n] 取值。
 * 时间复杂度：O(log(mn))
 * 空间复杂度：O(1)
 */

#include <vector>

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        int left = 0, right = m * n - 1;  // 闭区间 [left, right]
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int val = matrix[mid / n][mid % n];  // 一维下标映射回二维
            if (val == target) return true;
            if (val < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return false;
    }
};
