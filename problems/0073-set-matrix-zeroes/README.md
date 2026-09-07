# 73. 矩阵置零

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/set-matrix-zeroes/) ｜ [国际站](https://leetcode.com/problems/set-matrix-zeroes/)
>
> 🟡 中等 ｜ 标签：`矩阵` `哈希表`

## 📝 题目描述

给定一个 `m × n` 的矩阵 `matrix`，如果一个元素为 `0`，则将其所在行的**所有**元素和所在列的**所有**元素都设为 `0`。请使用**原地**算法。

**示例 1：**

```
输入：matrix = [[1,1,1],[1,0,1],[1,1,1]]
输出：[[1,0,1],[0,0,0],[1,0,1]]
```

**示例 2：**

```
输入：matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
输出：[[0,0,0,0],[0,4,5,0],[0,3,1,0]]
```

**提示：**

- `m == matrix.length`
- `n == matrix[0].length`
- `1 <= m, n <= 200`
- `-2^31 <= matrix[i][j] <= 2^31 - 1`

**进阶**：

- 一个直观的解决方案是使用 `O(mn)` 的额外空间，但这并不是一个好的解决方案。
- 一个简单的改进方案是使用 `O(m + n)` 的额外空间，但这仍然不是最好的解决方案。
- 你能想出一个仅使用**常数空间**的解决方案吗？

## 💡 题解

### 解法一：标记数组

**思路**：先扫一遍，用两个布尔数组记录哪些行、哪些列需要置零；再扫一遍，凡 `rowZero[i]` 或 `colZero[j]` 为真的格子直接置 `0`。必须先收集标记再统一置零——绝不能边发现 `0` 边置零，因为新写入的 `0` 会被当成原始的 `0`，波及无辜的行列。

```cpp
#include <vector>

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = (int)matrix.size(), n = (int)matrix[0].size();
        vector<bool> rowZero(m, false), colZero(n, false);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == 0) rowZero[i] = colZero[j] = true;
            }
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (rowZero[i] || colZero[j]) matrix[i][j] = 0;
            }
        }
    }
};
```

- ⏱️ 时间复杂度：`O(mn)`
- 💾 空间复杂度：`O(m + n)`

### 解法二：首行首列做标记（推荐）

**思路**：把第 `0` 行 / 第 `0` 列本身当作解法一中的标记数组：`matrix[i][0] == 0` 表示第 `i` 行要置零，`matrix[0][j] == 0` 表示第 `j` 列要置零。但首行首列**自己**是否置零无法在原地记录，需要两个额外变量 `firstRow` / `firstCol` 先行保存。流程：

1. 单独记录第 `0` 行、第 `0` 列原始是否含 `0`；
2. 扫描内部格子（`i >= 1, j >= 1`），遇到 `0` 就把对应的首行 / 首列位置写成 `0`（打标记）；
3. 依据首行 / 首列标记，把内部格子置零；
4. 最后依 `firstRow` / `firstCol` 处理第 `0` 行与第 `0` 列本身。

```cpp
#include <vector>

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = (int)matrix.size(), n = (int)matrix[0].size();
        bool firstRow = false, firstCol = false;
        for (int j = 0; j < n; ++j) firstRow |= (matrix[0][j] == 0);
        for (int i = 0; i < m; ++i) firstCol |= (matrix[i][0] == 0);

        // 用首行首列记录内部格子的置零需求
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == 0) matrix[i][0] = matrix[0][j] = 0;
            }
        }
        // 依据标记处理内部格子
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) matrix[i][j] = 0;
            }
        }
        // 最后处理首行首列自身
        if (firstRow) {
            for (int j = 0; j < n; ++j) matrix[0][j] = 0;
        }
        if (firstCol) {
            for (int i = 0; i < m; ++i) matrix[i][0] = 0;
        }
    }
};
```

- ⏱️ 时间复杂度：`O(mn)`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 一趟扫描边置零是错的：后写入的 `0` 会被当成原始 `0`，导致置零范围像涟漪一样扩散；必须"先标记、后置零"两阶段完成。
- 首行首列既是**标记区**又是**数据区**：必须先用 `firstRow` / `firstCol` 两个变量记录它们自身是否置零，并且放在最后处理，否则标记会被清零操作破坏。
- 解法二中步骤 2（打标记）与步骤 3（置零）不能合并成一趟——内部格子置零依赖的标记必须全部就位后再执行。
- 别漏了 `m == 1` 或 `n == 1` 的情况：此时"内部格子"为空，全靠 `firstRow` / `firstCol` 收尾，逻辑虽天然覆盖，但改动代码时要小心核对边界。

---

[← 返回目录](../../README.md)
