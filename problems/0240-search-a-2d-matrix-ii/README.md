# 240. 搜索二维矩阵 II

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/search-a-2d-matrix-ii/) ｜ [国际站](https://leetcode.com/problems/search-a-2d-matrix-ii/)
>
> 🟡 中等 ｜ 标签：`二分查找` `分治`

## 📝 题目描述

编写一个高效的算法来搜索 `m × n` 矩阵 `matrix` 中的一个目标值 `target`。该矩阵具有以下特性：

- 每行的元素从左到右升序排列；
- 每列的元素从上到下升序排列。

**示例 1：**

```
输入：matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
输出：true
```

**示例 2：**

```
输入：matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
输出：false
```

**提示：**

- `m == matrix.length`
- `n == matrix[i].length`
- `1 <= n, m <= 300`
- `-10^9 <= matrix[i][j] <= 10^9`
- 每行的所有元素从左到右升序排列
- 每列的所有元素从上到下升序排列
- `-10^9 <= target <= 10^9`

## 💡 题解

### 解法一：逐行二分

**思路**：每一行都是升序数组，对每行做一次二分查找 `target`。行与行之间虽然整体无序，但逐行查找不会遗漏。`m` 行各一次 `O(log n)` 的二分，简单直接。

```cpp
#include <vector>

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        for (auto& row : matrix) {
            auto it = lower_bound(row.begin(), row.end(), target);
            if (it != row.end() && *it == target) return true;
        }
        return false;
    }
};
```

- ⏱️ 时间复杂度：`O(m log n)`
- 💾 空间复杂度：`O(1)`

### 解法二：分治——中心元素划界排除

**思路**：对子矩阵（行区间 `[r1, r2]`、列区间 `[c1, c2]`）取中心 `pivot = matrix[rm][cm]`。若 `pivot == target` 直接命中；若 `pivot > target`，则右下开象限（行、列下标均超过中心的元素）全部 `>= pivot > target`，可整块剪掉；若 `pivot < target`，则左上象限（行、列下标均不超过中心的元素）全部 `<= pivot < target`，同样整块剪掉。每次把问题缩减为两块子矩阵递归。设矩阵元素数为 `C = mn`，递推式形如 `T(C) = 3T(C/4) + O(1)`，复杂度约 `O(C^{log₄ 3})`。

```cpp
#include <vector>

class Solution {
    // 在子矩阵 [r1,r2] x [c1,c2] 内搜索 t
    bool search(vector<vector<int>>& m, int r1, int c1, int r2, int c2, int t) {
        if (r1 > r2 || c1 > c2) return false;
        int rm = (r1 + r2) / 2, cm = (c1 + c2) / 2;
        int p = m[rm][cm];
        if (p == t) return true;
        if (p > t) {
            // 剪掉右下开象限：上方整块 + 中行以下的左块
            return search(m, r1, c1, rm - 1, c2, t) || search(m, rm, c1, r2, cm, t);
        }
        // 剪掉左上象限：下方整块 + 中行以上的右块
        return search(m, rm + 1, c1, r2, c2, t) || search(m, r1, cm + 1, rm, c2, t);
    }

public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = (int)matrix.size(), n = (int)matrix[0].size();
        return search(matrix, 0, 0, m - 1, n - 1, target);
    }
};
```

- ⏱️ 时间复杂度：`O((mn)^{log₄ 3})` ≈ `O((mn)^{0.79})`
- 💾 空间复杂度：`O(log(mn))`（递归栈）

### 解法三：Z 字形查找——右上角出发（推荐）

**思路**：从矩阵**右上角**出发：当前值 `matrix[x][y]` 是它所在行的**最大值**、所在列的**最小值**。于是每次比较有确定方向：

- `matrix[x][y] == target`：命中；
- `matrix[x][y] > target`：该列下方只会更大，排除第 `y` 列，左移；
- `matrix[x][y] < target`：该行左边只会更小，排除第 `x` 行，下移。

每步排除一整行或一整列，最多 `m + n` 步；出界则不存在。起点选**左下角**同理（大于上移、小于右移），但从左上角（全矩阵最小）或右下角（全矩阵最大）出发无法判断方向。

```cpp
#include <vector>

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = (int)matrix.size(), n = (int)matrix[0].size();
        int x = 0, y = n - 1;  // 从右上角出发
        while (x < m && y >= 0) {
            int v = matrix[x][y];
            if (v == target) return true;
            v > target ? --y : ++x;  // 大于排除当前列，小于排除当前行
        }
        return false;
    }
};
```

- ⏱️ 时间复杂度：`O(m + n)`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- Z 字形查找必须从**右上角**或**左下角**出发；从左上角（最小值）或右下角（最大值）出发时，一个比较无法同时淘汰行和列。
- "每行有序、每列有序"**不代表**"上一行末尾 <= 下一行开头"，矩阵整体不是一维有序数组，74 题那种"拉平后二分"在这里不适用。
- 逐行二分用 `lower_bound` 时记得检查 `it != row.end()` 且 `*it == target`，只判其一可能越界或误判。
- 分治剪枝要注意被排除象限的边界归属：`p > t` 剪掉的是**开**象限（不含中心所在的行与列交叉区），递归范围必须恰好覆盖剩余区域，否则会漏查边界。

---

[← 返回目录](../../README.md)
