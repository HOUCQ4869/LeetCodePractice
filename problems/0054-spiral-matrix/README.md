# 54. 螺旋矩阵

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/spiral-matrix/) ｜ [国际站](https://leetcode.com/problems/spiral-matrix/)
>
> 🟡 中等 ｜ 标签：`矩阵` `模拟`

## 📝 题目描述

给定一个 `m` 行 `n` 列的矩阵 `matrix`，请按照**顺时针螺旋顺序**返回矩阵中的所有元素。

**示例 1：**

```
输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[1,2,3,6,9,8,7,4,5]
```

**示例 2：**

```
输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
输出：[1,2,3,4,8,12,11,10,9,5,6,7]
```

**提示：**

- `m == matrix.length`
- `n == matrix[i].length`
- `1 <= m, n <= 10`
- `-100 <= matrix[i][j] <= 100`

## 💡 题解

### 解法一：方向模拟 + 访问标记

**思路**：从 `(0, 0)` 出发，按"右 → 下 → 左 → 上"的固定方向循环前进。用 `visited` 矩阵记录走过的格子，当下一步越界或已访问时，方向下标顺时针转一格（`d = (d + 1) % 4`）。每个格子恰好访问一次，走满 `m * n` 步结束。逻辑直白不易错，代价是 `O(mn)` 的标记数组。

```cpp
#include <vector>

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = (int)matrix.size(), n = (int)matrix[0].size();
        vector<vector<bool>> vis(m, vector<bool>(n, false));
        int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};  // 右、下、左、上
        vector<int> ans;
        ans.reserve(m * n);
        int x = 0, y = 0, d = 0;
        for (int k = 0; k < m * n; ++k) {
            ans.push_back(matrix[x][y]);
            vis[x][y] = true;
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || nx >= m || ny < 0 || ny >= n || vis[nx][ny]) {
                d = (d + 1) % 4;  // 撞墙或已访问：右转
                nx = x + dx[d];
                ny = y + dy[d];
            }
            x = nx;
            y = ny;
        }
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(mn)`
- 💾 空间复杂度：`O(mn)`（visited 矩阵）

### 解法二：四边界收缩（推荐）

**思路**：维护尚未遍历区域的四个边界 `top / bottom / left / right`，每一圈按固定顺序走四条边：上边从左到右 → 右边从上到下 → 下边从右到左 → 左边从下到上，每走完一条边就把对应边界向内收缩一格。注意边界细节：右列已输出过 `matrix[bottom][right]`，所以下行从 `right - 1` 走到 `left`；下行已输出过 `matrix[bottom][left]`，所以左列从 `bottom - 1` 走到 `top + 1`。另外，当只剩单行（`top == bottom`）时不能再走下行，只剩单列（`left == right`）时不能再走左列，否则会重复输出。

```cpp
#include <vector>

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = (int)matrix.size(), n = (int)matrix[0].size();
        int top = 0, bottom = m - 1, left = 0, right = n - 1;
        vector<int> ans;
        ans.reserve(m * n);
        while (top <= bottom && left <= right) {
            for (int j = left; j <= right; ++j) ans.push_back(matrix[top][j]);        // 上边
            for (int i = top + 1; i <= bottom; ++i) ans.push_back(matrix[i][right]);  // 右边
            if (top < bottom && left < right) {  // 剩多行多列才有下边、左边
                for (int j = right - 1; j >= left; --j) ans.push_back(matrix[bottom][j]);  // 下边
                for (int i = bottom - 1; i > top; --i) ans.push_back(matrix[i][left]);    // 左边
            }
            ++top; --bottom; ++left; --right;  // 边界收缩，进入内圈
        }
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(mn)`
- 💾 空间复杂度：`O(1)`（输出不计）

## ⚠️ 易错点

- 四条边的循环边界最易错：**右边**从 `top + 1` 开始（右上角已被上边输出）；**下边**从 `right - 1` 开始（右下角已被右边输出）；**左边**从 `bottom - 1` 到 `top + 1`（两个端点都已被前面两边输出）。
- 剩单行（`top == bottom`）时不能再走下边，剩单列（`left == right`）时不能再走左边，否则中间元素会输出两遍；`if (top < bottom && left < right)` 一并兜底。
- 收缩是四个边界同时 `++top; --bottom; ++left; --right;`，循环条件是 `top <= bottom && left <= right`，漏掉等号会丢掉最后一行/列。
- 方向模拟法转向的判定是"越界**或**已访问"，只判越界会在最后一圈打转。

---

[← 返回目录](../../README.md)
