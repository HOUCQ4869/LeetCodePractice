/**
 * @file    0079-word-search.cpp
 * @brief   79. 单词搜索
 * @link    https://leetcode.cn/problems/word-search/
 *
 * 解法：回溯（原地标记 + 词频剪枝）
 * 思路：先统计棋盘字符词频做一次整体剪枝（word 中某字符比棋盘还多则必无解）；
 *      再从每个格子出发回溯匹配，用 '#' 原地覆盖走过的格子充当 visited 标记，
 *      递归返回前恢复原字符，四个方向依次尝试。
 * 时间复杂度：O(M × N × 3^L)，L 为 word 长度（首格 4 个方向，其后每步至多 3 个新方向）
 * 空间复杂度：O(L)，递归栈深度（标记写在棋盘上，无额外 visited 数组）
 */

#include <string>
#include <vector>

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        // 剪枝：word 中某字符的出现次数超过棋盘中该字符总数，必然无解
        int cnt[128] = {0};
        for (const auto& row : board) {
            for (char c : row) ++cnt[static_cast<unsigned char>(c)];
        }
        for (char c : word) {
            if (--cnt[static_cast<unsigned char>(c)] < 0) return false;
        }

        int m = static_cast<int>(board.size());
        int n = static_cast<int>(board[0].size());
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dfs(board, word, i, j, 0)) return true;  // 任一起点成功即可
            }
        }
        return false;
    }

private:
    // 尝试从 (i, j) 出发匹配 word[k..]
    bool dfs(vector<vector<char>>& board, const string& word, int i, int j, int k) {
        if (board[i][j] != word[k]) return false;
        if (k + 1 == static_cast<int>(word.size())) return true;  // 最后一个字符匹配成功

        board[i][j] = '#';  // 原地标记：当前格已在路径上
        static const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        bool found = false;
        for (int t = 0; t < 4 && !found; ++t) {
            int ni = i + dirs[t][0];
            int nj = j + dirs[t][1];
            if (ni >= 0 && ni < static_cast<int>(board.size())
                && nj >= 0 && nj < static_cast<int>(board[0].size())) {
                found = dfs(board, word, ni, nj, k + 1);
            }
        }
        board[i][j] = word[k];  // 回溯：恢复原字符
        return found;
    }
};
