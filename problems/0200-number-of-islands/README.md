# 200. 岛屿数量

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/number-of-islands/) ｜ [国际站](https://leetcode.com/problems/number-of-islands/)
>
> 🟡 中等 ｜ 标签：`图` `深度优先搜索` `广度优先搜索` `并查集`

## 📝 题目描述

给定一个由字符 `'1'`（陆地）和 `'0'`（水）组成的二维网格，请计算网格中岛屿的数量。

- 岛屿由水平方向和/或竖直方向上相邻的陆地格子连接而成；
- 岛屿总是被水包围，并且可以假设网格的四条边均被水包围（边界之外都视为水）。

**示例 1：**

```
输入：grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
输出：3
解释：左上角 4 个 '1' 连成一座岛，中间的 1 个 '1' 是一座，右下角的 2 个 '1' 是一座，共 3 座。
```

**示例 2：**

```
输入：grid = [
  ["1","1"],
  ["0","0"]
]
输出：1
```

**提示：**

- `1 <= m, n <= 300`
- `grid[i][j]` 的取值为 `'1'` 或 `'0'`

## 💡 题解

### 解法一：深度优先搜索（洪水填充）

**思路**：把网格看作图，相邻的陆地格连成一整块。顺序扫描每个格子，一旦遇到 `'1'`，说明发现了一座**尚未统计过**的岛——计数加一，随即从该格出发 DFS，把这座岛上所有连通的 `'1'` 全部改写成 `'0'`（俗称"淹没"），保证同一座岛之后不会再被重复计数。扫描结束时计数即岛屿数。直接修改网格充当 visited 标记，省去额外数组；若不允许修改输入，可另开一个 `visited` 二维数组。

```cpp
#include <vector>

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = static_cast<int>(grid.size());
        int n = static_cast<int>(grid[0].size());
        int count = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1') {
                    ++count;          // 遇到新陆地，岛屿数 +1
                    sink(grid, i, j); // 淹没整座岛，防止重复计数
                }
            }
        }
        return count;
    }

private:
    void sink(vector<vector<char>>& grid, int i, int j) {
        if (i < 0 || i >= static_cast<int>(grid.size())
            || j < 0 || j >= static_cast<int>(grid[0].size())
            || grid[i][j] != '1') {
            return;
        }
        grid[i][j] = '0';  // 标记为已访问
        sink(grid, i + 1, j);
        sink(grid, i - 1, j);
        sink(grid, i, j + 1);
        sink(grid, i, j - 1);
    }
};
```

- ⏱️ 时间复杂度：`O(MN)`，每个格子至多被访问常数次
- 💾 空间复杂度：`O(MN)`，最坏情况（几乎全是陆地）递归栈的深度

### 解法二：广度优先搜索

**思路**：整体框架与解法一相同，只是把"淹没"的操作从递归改为队列式的 BFS：发现新岛屿时把起点入队，然后逐个出队并向四个方向扩散，把到达的陆地置 `'0'` 并入队，直到队列清空。相比 DFS 的优势是**没有递归深度风险**（网格极大时 DFS 可能爆栈）；注意必须在**入队的同时**标记 `'0'`，而不是出队时才标记，否则同一格会被重复入队，队列规模失控。

```cpp
#include <queue>
#include <utility>
#include <vector>

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = static_cast<int>(grid.size());
        int n = static_cast<int>(grid[0].size());
        static const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        int count = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] != '1') continue;
                ++count;
                queue<pair<int, int>> q;
                grid[i][j] = '0';  // 入队时立刻标记，防止重复入队
                q.push({i, j});
                while (!q.empty()) {
                    auto [x, y] = q.front();
                    q.pop();
                    for (const auto& d : dirs) {
                        int nx = x + d[0];
                        int ny = y + d[1];
                        if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
                        if (grid[nx][ny] != '1') continue;
                        grid[nx][ny] = '0';
                        q.push({nx, ny});
                    }
                }
            }
        }
        return count;
    }
};
```

- ⏱️ 时间复杂度：`O(MN)`
- 💾 空间复杂度：`O(min(M, N))`，队列中同时容纳的格子数不超过网格的"对角线宽度"

### 解法三：并查集（推荐）

**思路**：把每个陆地格看成一个节点，**岛屿就是陆地格构成的连通块**。初始时让岛屿计数等于陆地格总数（每块陆地自成一个集合）；再依次把每个陆地格与**右侧、下侧**的相邻陆地合并——每个相邻对都会被其中靠左/靠上的格子枚举到，所以只看两个方向就能覆盖全部四邻关系。每合并两个**不同的**连通块，计数减一。最终计数就是连通块个数，即岛屿数。`find` 配合路径压缩 + 按秩合并，单次合并近似 `O(1)`。

并查集代码量略大，但它是最通用的做法：当题目升级为"不断添加陆地并随时询问岛屿数量"（如第 305 题）时，DFS/BFS 每次都要整体重算，而并查集只需对新增的边做增量合并。

```cpp
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
```

- ⏱️ 时间复杂度：`O(MN × α(MN))`，`α` 为反阿克曼函数，可视为常数
- 💾 空间复杂度：`O(MN)`

## ⚠️ 易错点

- BFS 中若**出队时**才标记访问，同一格子会被重复入队，队列规模指数膨胀——必须在**入队前**就置 `'0'`。
- 并查集里把水格子也初始化成独立集合、或对水格子做 `find`，会统计出错误的连通块数量；计数只应从陆地格开始。
- 洪水填充只需向右、向下合并即可覆盖全部相邻关系，但**扫描每个格子作为起点**这一步不能省，否则会漏掉只被"上方/左方"相邻关系连接的岛。
- DFS 版本忘记把访问过的 `'1'` 置 `'0'`，会死循环或把一座岛重复计数多次。

---

[← 返回目录](../../README.md)
