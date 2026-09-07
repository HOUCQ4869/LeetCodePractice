/**
 * @file    0051-n-queens.cpp
 * @brief   51. N 皇后
 * @link    https://leetcode.cn/problems/n-queens/
 *
 * 解法：回溯 + 位运算
 * 思路：逐行放置皇后（每行恰一个）。用三个整数的位掩码记录当前行上
 *      列、↘ 对角线、↙ 对角线的受攻击位置；进入下一行时对角线掩码整体
 *      左移 / 右移一位。可用列由取反与 full 求交，用 lowbit 逐个枚举。
 * 时间复杂度：O(n!)，每行候选随冲突剪枝迅速减少
 * 空间复杂度：O(n)，递归栈与棋盘（n ≤ 9，掩码用 32 位整数足够）
 */

#include <string>
#include <vector>

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        this->n = n;
        full = (1u << n) - 1;
        board.assign(n, string(n, '.'));
        ans.clear();
        backtrack(0, 0, 0, 0);
        return ans;
    }

private:
    int n = 0;
    unsigned full = 0;  // 低 n 位全 1：合法列掩码
    vector<string> board;
    vector<vector<string>> ans;

    // row：当前行；cols / d1 / d2：列、↘ 对角线、↙ 对角线在当前行上的攻击位
    void backtrack(int row, unsigned cols, unsigned d1, unsigned d2) {
        if (row == n) {
            ans.push_back(board);  // n 行全部放好，收集棋盘快照
            return;
        }
        unsigned avail = ~(cols | d1 | d2) & full;  // 当前行仍可放皇后的列
        while (avail) {
            unsigned p = avail & -avail;  // 取最低位的 1（lowbit）
            int col = __builtin_ctz(p);   // 该位对应的列号
            board[row][col] = 'Q';
            // 下一行：列不变；↘ 对角线左移一位、↙ 对角线右移一位
            backtrack(row + 1, cols | p, (d1 | p) << 1, (d2 | p) >> 1);
            board[row][col] = '.';
            avail &= avail - 1;  // 去掉该位，尝试下一个可用列
        }
    }
};
