/**
 * @file    0279-perfect-squares.cpp
 * @brief   279. 完全平方数
 * @link    https://leetcode.cn/problems/perfect-squares/
 *
 * 解法：数学——拉格朗日四平方定理
 * 思路：答案只能是 1/2/3/4：形如 4^a(8b+7) 时为 4，本身平方数为 1，可拆两平方和为 2，否则为 3。
 * 时间复杂度：O(sqrt(n))
 * 空间复杂度：O(1)
 */

#include <cmath>

class Solution {
public:
    int numSquares(int n) {
        // 判断 x 是否为完全平方数
        auto isSquare = [](int x) {
            int r = (int)sqrt((double)x);
            return r * r == x;
        };

        // 规则 1：形如 4^a * (8b + 7) 时答案为 4
        int m = n;
        while (m % 4 == 0) m /= 4;
        if (m % 8 == 7) return 4;

        // 规则 2：n 本身是完全平方数，答案为 1
        if (isSquare(n)) return 1;

        // 规则 3：能拆成两个平方数之和，答案为 2
        for (int a = 1; (long long)a * a <= n; ++a) {
            if (isSquare(n - a * a)) return 2;
        }

        // 其余情况答案为 3
        return 3;
    }
};
