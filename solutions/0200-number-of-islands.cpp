/**
 * @file    0200-number-of-islands.cpp
 * @brief   200. 岛屿数量
 * @link    https://leetcode.cn/problems/number-of-islands/
 *
 * 解法：并查集
 * 思路：把每个 '1' 格子看成一个节点，岛屿即陆地格构成的连通块。
 *      初始把岛屿数记为陆地格总数，再依次将每个陆地格与右侧、下侧的相邻陆地合并，
 *      每合并两个不同的连通块计数减一，最终计数就是岛屿数量。
 *      find 用路径压缩 + 按秩合并，单次合并近似 O(1)。
 * 时间复杂度：O(MN × α(MN))，α 为反阿克曼函数，可视为常数
 * 空间复杂度：O(MN)
 */

#include <utility>
#include <vector>

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = static_cast<int>(grid.size());
        int n = static_cast<int>(grid[0].size());

        parent.resize(m * n);
        rank.assign(m * n, 0);
        int islands = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1') {
                    parent[i * n + j] = i * n + j;  // 每块陆地初始自成一个集合
                    ++islands;
                }
            }
        }

        // 只需向右、向下合并：每个相邻对都会被其中左/上的格子枚举到
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] != '1') continue;
                if (j + 1 < n && grid[i][j + 1] == '1') {
                    unite(i * n + j, i * n + j + 1, islands);  // 向右合并
                }
                if (i + 1 < m && grid[i + 1][j] == '1') {
                    unite(i * n + j, (i + 1) * n + j, islands);  // 向下合并
                }
            }
        }
        return islands;
    }

private:
    vector<int> parent;
    vector<int> rank;

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // 路径压缩：沿途节点直接挂到根
        }
        return parent[x];
    }

    void unite(int a, int b, int& islands) {
        int ra = find(a);
        int rb = find(b);
        if (ra == rb) return;  // 已属同一座岛
        if (rank[ra] < rank[rb]) swap(ra, rb);  // 按秩合并：矮树挂到高树下
        parent[rb] = ra;
        if (rank[ra] == rank[rb]) ++rank[ra];
        --islands;  // 两座不同的岛合并成一座
    }
};
