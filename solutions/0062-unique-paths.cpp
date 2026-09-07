/**
 * @file    0062-unique-paths.cpp
 * @brief   62. 不同路径
 * @link    https://leetcode.cn/problems/unique-paths/
 *
 * 解法：组合数学
 * 思路：全程共 m+n-2 步，其中 min(m,n)-1 步向下，路径数即组合数 C(m+n-2, min(m,n)-1)，边乘边除计算避免溢出。
 * 时间复杂度：O(min(m, n))
 * 空间复杂度：O(1)
 */

#include <algorithm>

class Solution {
public:
    int uniquePaths(int m, int n) {
        // 在 m+n-2 步中选出 min(m,n)-1 步向下：C(m+n-2, min(m,n)-1)
        int total = m + n - 2;
        int k = min(m, n) - 1;
        long long ans = 1;
        for (int i = 1; i <= k; ++i) {
            // 每轮结果仍是组合数 C(total-k+i, i)，保证整除且不超过最终答案
            ans = ans * (total - k + i) / i;
        }
        return (int)ans;
    }
};
