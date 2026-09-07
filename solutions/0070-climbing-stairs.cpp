/**
 * @file    0070-climbing-stairs.cpp
 * @brief   70. 爬楼梯
 * @link    https://leetcode.cn/problems/climbing-stairs/
 *
 * 解法：滚动变量（斐波那契递推）
 * 思路：f(n) = f(n-1) + f(n-2)，仅依赖最近两个状态，用两个变量滚动计算。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

class Solution {
public:
    int climbStairs(int n) {
        int prev = 1, curr = 1;  // f(0) = 1, f(1) = 1
        for (int i = 2; i <= n; ++i) {
            int next = prev + curr;
            prev = curr;
            curr = next;
        }
        return curr;
    }
};
