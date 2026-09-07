# 48. 旋转图像

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/rotate-image/) ｜ [国际站](https://leetcode.com/problems/rotate-image/)
>
> 🟡 中等 ｜ 标签：`矩阵` `数学`

## 📝 题目描述

给定一个 `n × n` 的二维矩阵 `matrix` 表示一个图像，请将图像**顺时针旋转 90 度**。

必须在**原地**旋转图像，即直接修改输入的二维矩阵，**不要**使用另一个矩阵来旋转。

**示例 1：**

```
输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[[7,4,1],[8,5,2],[9,6,3]]
```

**示例 2：**

```
输入：matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
输出：[[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
```

**提示：**

- `n == matrix.length == matrix[i].length`
- `1 <= n <= 20`
- `-1000 <= matrix[i][j] <= 1000`

## 💡 题解

**坐标规律**：顺时针旋转 90° 后，原第 `i` 行第 `j` 列的元素来到第 `j` 行第 `n - 1 - i` 列，即 `new[j][n-1-i] = old[i][j]`。下面三种解法都是围绕这条规律的不同落地方式。

### 解法一：辅助矩阵

**思路**：按坐标规律直接构造新矩阵再拷回原矩阵。最直白、不会出错，但用了 `O(n^2)` 额外空间，不满足题目"原地"的精神，作为基准对照。

```cpp
#include <vector>

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = (int)matrix.size();
        vector<vector<int>> tmp(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                tmp[j][n - 1 - i] = matrix[i][j];
            }
        }
        matrix = move(tmp);
    }
};
```

- ⏱️ 时间复杂度：`O(n^2)`
- 💾 空间复杂度：`O(n^2)`

### 解法二：四元组循环旋转

**思路**：一次旋转会同时牵动 4 个格子，构成循环链：`(i,j) → (j,n-1-i) → (n-1-i,n-1-j) → (n-1-j,i) → (i,j)`。取一个临时变量保存起点值，即可把这 4 个位置一次性轮转就位。只需枚举"左上三角区"（`i ∈ [0, (n+1)/2)`，`j ∈ [i, n-1-i)`），保证每组 4 格恰好被处理一次；`n` 为奇数时中心格旋转后不变，天然落在枚举范围之外。

```cpp
#include <utility>
#include <vector>

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = (int)matrix.size();
        for (int i = 0; i < (n + 1) / 2; ++i) {
            for (int j = i; j < n - 1 - i; ++j) {
                int tmp = matrix[i][j];
                matrix[i][j] = matrix[n - 1 - j][i];                  // 左 → 上
                matrix[n - 1 - j][i] = matrix[n - 1 - i][n - 1 - j];  // 下 → 左
                matrix[n - 1 - i][n - 1 - j] = matrix[j][n - 1 - i];  // 右 → 下
                matrix[j][n - 1 - i] = tmp;                           // 上 → 右
            }
        }
    }
};
```

- ⏱️ 时间复杂度：`O(n^2)`
- 💾 空间复杂度：`O(1)`

### 解法三：转置 + 左右翻转（推荐）

**思路**：两步组合恰好得到顺时针 90°：先沿主对角线**转置**（`(i,j) → (j,i)`），再把每一行**左右翻转**（`(j,i) → (j, n-1-i)`），复合效果正是 `(i,j) → (j, n-1-i)`。两步都只做原地交换，代码极短且不易错。相应地，逆时针 90° 等价于"转置 + 上下翻转"，180° 等价于"左右翻转 + 上下翻转"。

```cpp
#include <algorithm>
#include <utility>
#include <vector>

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = (int)matrix.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                swap(matrix[i][j], matrix[j][i]);  // 主对角线转置
            }
        }
        for (auto& row : matrix) {
            reverse(row.begin(), row.end());  // 左右翻转
        }
    }
};
```

- ⏱️ 时间复杂度：`O(n^2)`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 方向别记反：顺时针 90° 是 `new[j][n-1-i] = old[i][j]`；`old[n-1-j][i] → new[i][j]` 那组坐标对应的是逆时针。
- 转置时内层循环从 `j = i + 1` 开始，只处理对角线一侧；若遍历全部 `(i, j)` 会把每对元素交换两次，等于没换。
- 四元组旋转的枚举范围要精确（`i < (n+1)/2`、`i <= j < n-1-i`），范围偏大会把同一组格子旋转多次。
- 解法一 `matrix = move(tmp)` 是整体搬回，若逐元素拷贝注意 `tmp` 是按新坐标写的，直接下标对下标会覆盖。

---

[← 返回目录](../../README.md)
