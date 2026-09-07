# 64. 最小路径和

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/minimum-path-sum/) ｜ [国际站](https://leetcode.com/problems/minimum-path-sum/)
>
> 🟡 中等 ｜ 标签：`动态规划` `矩阵`

## 📝 题目描述

给定一个包含非负整数的 `m × n` 网格 `grid`，请找出一条从**左上角**到**右下角**的路径，使得路径上的数字总和最小，返回这个最小的数字总和。

每次只能**向下**或者**向右**移动一步，不能向上、向左，也不能越界。

**示例 1：**

```
输入：grid = [[1,3,1],[1,5,1],[4,2,1]]
输出：7
解释：因为路径 1→3→1→1→1 的总和最小。
```

**示例 2：**

```
输入：grid = [[1,2,3],[4,5,6]]
输出：12
```

**提示：**

- `m == grid.length`
- `n == grid[i].length`
- `1 <= m, n <= 200`
- `0 <= grid[i][j] <= 200`

## 💡 题解

### 解法一：二维动态规划

**思路**：设 `dp[i][j]` 为从 `(0, 0)` 走到 `(i, j)` 的最小路径和。到达 `(i, j)` 只能来自上方 `(i-1, j)` 或左侧 `(i, j-1)`，取两者较小者再累加当前格子的值：

`dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1])`

边界：第一行只能从左侧来，`dp[0][j] = dp[0][j-1] + grid[0][j]`；第一列只能从上方来，同理逐格累加。答案为 `dp[m-1][n-1]`。

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = (int)grid.size(), n = (int)grid[0].size();
        // dp[i][j]：从 (0,0) 走到 (i,j) 的最小路径和
        vector<vector<int>> dp(m, vector<int>(n));
        dp[0][0] = grid[0][0];
        for (int j = 1; j < n; ++j) dp[0][j] = dp[0][j - 1] + grid[0][j];  // 首行
        for (int i = 1; i < m; ++i) dp[i][0] = dp[i - 1][0] + grid[i][0];  // 首列
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[m - 1][n - 1];
    }
};
```

- ⏱️ 时间复杂度：`O(mn)`
- 💾 空间复杂度：`O(mn)`

### 解法二：滚动数组（推荐）

**思路**：与 62 题相同的压缩手法——第 `i` 行只依赖第 `i-1` 行和本行左侧的值。用一维 `dp`：转移时 `dp[j]`（尚未覆盖的旧值）正是上一行的 `dp[i-1][j]`，而 `dp[j-1]` 已是本行的 `dp[i][j-1]`，故 `dp[j] = grid[i][j] + min(dp[j], dp[j-1])`。首行先单独初始化，每行开头的首列单独累加。

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = (int)grid.size(), n = (int)grid[0].size();
        vector<int> dp(n);
        dp[0] = grid[0][0];
        for (int j = 1; j < n; ++j) dp[j] = dp[j - 1] + grid[0][j];  // 首行
        for (int i = 1; i < m; ++i) {
            dp[0] += grid[i][0];                                      // 首列
            for (int j = 1; j < n; ++j) {
                dp[j] = grid[i][j] + min(dp[j], dp[j - 1]);
            }
        }
        return dp[n - 1];
    }
};
```

- ⏱️ 时间复杂度：`O(mn)`
- 💾 空间复杂度：`O(n)`

## ⚠️ 易错点

- 第一行、第一列不满足通用转移（会引用不存在的上/左格子），必须单独初始化；滚动写法里每行开头的 `dp[0] += grid[i][0]`（首列）最容易漏掉。
- 滚动数组内层必须**从左往右**扫，`dp[j-1]` 才是本行已更新的值；反向扫描会把上一行的左侧值用进来。
- 只能向右、向下移动，路线图是天然的 DAG，DP 一遍即可；不要套 Dijkstra/BFS 做四方向搜索，既慢又容易绕路。
- 返回的是右下角的 `dp[n-1]`，不是最后一行的最小值——中途拐进某一列的路径和可能更小，但并不通向终点。

---

[← 返回目录](../../README.md)
