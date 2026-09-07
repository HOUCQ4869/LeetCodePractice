# 994. 腐烂的橘子

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/rotting-oranges/) ｜ [国际站](https://leetcode.com/problems/rotting-oranges/)
>
> 🟡 中等 ｜ 标签：`图` `广度优先搜索`

## 📝 题目描述

给定一个 `m × n` 的网格，每个格子表示：

- `0`：空格子；
- `1`：新鲜橘子；
- `2`：腐烂的橘子。

每分钟，与腐烂橘子**上、下、左、右**四方向相邻的新鲜橘子都会腐烂。求直到网格中**不再有新鲜橘子**为止必须经过的最小分钟数；如果永远做不到（有新鲜橘子无法被传染），返回 `-1`。

**示例 1：**

```
输入：grid = [[2,1,1],[1,1,0],[0,1,1]]
输出：4
解释：左上角的腐烂橘子每分钟向四周扩散一层，右下角的新鲜橘子在第 4 分钟被传染。
```

**示例 2：**

```
输入：grid = [[2,1,1],[0,1,1],[1,0,1]]
输出：-1
解释：左下角 (2,0) 处的新鲜橘子与任何腐烂橘子都不连通，永远无法腐烂。
```

**示例 3：**

```
输入：grid = [[0,2]]
输出：0
解释：没有新鲜橘子，0 分钟后即满足条件。
```

**提示：**

- `1 <= m, n <= 10`
- `grid[i][j]` 的取值为 `0`、`1` 或 `2`

## 💡 题解

### 解法一：逐分钟暴力模拟

**思路**：直接按题意模拟：每一分钟扫描一遍整个网格，找出所有"四邻中存在腐烂橘子"的新鲜橘子，**先收集到列表里，扫描结束后统一置为腐烂**（若边扫边改，一次扫描内传染会连锁传播多步，一分钟就"变成"了好几分钟）。若某轮扫描发现已无新鲜橘子，返回当前分钟数；若仍有新鲜橘子但本轮没有任何新传染发生，说明剩下的橘子永远轮不到，返回 `-1`。思路零门槛，但每轮 `O(MN)`、最多 `O(MN)` 轮，最坏平方级。

```cpp
#include <utility>
#include <vector>

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = static_cast<int>(grid.size());
        int n = static_cast<int>(grid[0].size());
        static const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        int minutes = 0;
        while (true) {
            int fresh = 0;
            vector<pair<int, int>> willRot;  // 本分钟将被传染的新鲜橘子
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (grid[i][j] != 1) continue;
                    ++fresh;
                    for (const auto& d : dirs) {
                        int ni = i + d[0];
                        int nj = j + d[1];
                        if (ni >= 0 && ni < m && nj >= 0 && nj < n && grid[ni][nj] == 2) {
                            willRot.push_back({i, j});  // 邻居有腐烂橘子，下一分钟变质
                            break;
                        }
                    }
                }
            }
            if (fresh == 0) return minutes;   // 没有新鲜橘子了
            if (willRot.empty()) return -1;   // 有新鲜橘子但再也传染不到
            for (auto& [i, j] : willRot) grid[i][j] = 2;  // 统一生效，避免同分钟连锁
            ++minutes;
        }
    }
};
```

- ⏱️ 时间复杂度：`O((MN)^2)`，每轮扫描 `O(MN)`，最多传染 `MN` 轮
- 💾 空间复杂度：`O(MN)`，暂存本轮新腐烂的格子

### 解法二：多源广度优先搜索（推荐）

**思路**：「多个源头同时向外扩散，问每个角落被波及的时刻」正是**多源 BFS** 的标准应用场景。把初始所有腐烂橘子**一次性**全部入队，视为 BFS 的第 0 层；逐层向外扩散，每一层对应一分钟，扩散的层数就是答案。用 `fresh` 计数新鲜橘子，每传染一个就减一；BFS 结束后若 `fresh > 0`，说明存在孤立的新鲜橘子，返回 `-1`。相比模拟法，每个格子只被处理一次，一遍 BFS 出结果。注意两个边界：初始就没有新鲜橘子时答案为 `0`；层计数只在**这一层真的传染了新橘子**时才加一（最后一层往往只是空转，不计时）。

```cpp
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
```

- ⏱️ 时间复杂度：`O(MN)`，每个格子至多入队一次
- 💾 空间复杂度：`O(MN)`，队列开销

## ⚠️ 易错点

- 必须把**所有**初始腐烂橘子同时入队再做 BFS；逐个单独做单源 BFS 会把"同时扩散"错误地变成"先后扩散"，把分钟数算大。
- 分钟计数容易差一：第 0 层（初始腐烂橘子本身）不耗时，从它们传染出第一层才开始 +1；同时最后一层若没有传染任何新橘子，不应计入。
- 模拟法里边扫描边修改，会让一次扫描内的传染连锁生效，分钟数偏小；必须先收集、后统一置腐烂。
- 边界：网格里没有任何新鲜橘子时答案为 `0`（包括全是空格或只有腐烂橘子的情况），不要漏判而直接进入 BFS。

---

[← 返回目录](../../README.md)
