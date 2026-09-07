/**
 * @file    0994-rotting-oranges.cpp
 * @brief   994. 腐烂的橘子
 * @link    https://leetcode.cn/problems/rotting-oranges/
 *
 * 解法：多源 BFS
 * 思路：把初始所有腐烂橘子一起入队当作第 0 层，逐层向四邻扩散，扩散的层数即分钟数；
 *      用 fresh 计数剩余新鲜橘子，每传染一个减一，BFS 结束后 fresh > 0 说明无解，返回 -1。
 * 时间复杂度：O(MN)，每个格子至多入队一次
 * 空间复杂度：O(MN)，队列开销
 */

#include <queue>
#include <utility>
#include <vector>

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = static_cast<int>(grid.size());
        int n = static_cast<int>(grid[0].size());
        static const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        queue<pair<int, int>> q;
        int fresh = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 2) {
                    q.push({i, j});  // 所有初始腐烂橘子同时入队（多源）
                } else if (grid[i][j] == 1) {
                    ++fresh;
                }
            }
        }
        if (fresh == 0) return 0;  // 没有新鲜橘子，一分钟也不用等

        int minutes = 0;
        while (!q.empty()) {
            int sz = static_cast<int>(q.size());
            bool rotted = false;  // 本层是否真的传染了新橘子
            for (int k = 0; k < sz; ++k) {
                auto [x, y] = q.front();
                q.pop();
                for (const auto& d : dirs) {
                    int nx = x + d[0];
                    int ny = y + d[1];
                    if (nx < 0 || nx >= m || ny < 0 || ny >= n || grid[nx][ny] != 1) continue;
                    grid[nx][ny] = 2;  // 传染：新鲜 -> 腐烂
                    --fresh;
                    q.push({nx, ny});
                    rotted = true;
                }
            }
            if (rotted) ++minutes;  // 本层扩散花费一分钟
        }
        return fresh == 0 ? minutes : -1;
    }
};
