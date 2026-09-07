# 118. 杨辉三角

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/pascals-triangle/) ｜ [国际站](https://leetcode.com/problems/pascals-triangle/)
>
> 🟢 简单 ｜ 标签：`动态规划` `数组`

## 📝 题目描述

给定一个非负整数 `numRows`，生成「杨辉三角」的前 `numRows` 行。

在杨辉三角中，每个数是它**左上方**和**右上方**的数之和（边界上的数始终为 1）：

```
    1
   1 1
  1 2 1
 1 3 3 1
1 4 6 4 1
```

**示例 1：**

```
输入：numRows = 5
输出：[[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
```

**示例 2：**

```
输入：numRows = 1
输出：[[1]]
```

**提示：**

- `1 <= numRows <= 30`

## 💡 题解

### 解法一：组合数公式递推

**思路**：杨辉三角本质上是组合数表——第 `i` 行第 `j` 个数恰是 `C(i, j)`（从 `i` 个里选 `j` 个）。由恒等式 `C(i, j + 1) = C(i, j) * (i - j) / (j + 1)`，可以在一行内从左往右由前一个数推出后一个数，不依赖上一行的存储。注意必须**先乘后除**并保证整除，且中间量用 `long long` 防溢出（`numRows = 30` 时 `C(29, 14)` 约为 `7.8 * 10^7`，乘法过程中间值可能超出 `int`）。

```cpp
#include <vector>

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res;
        for (int i = 0; i < numRows; ++i) {
            vector<int> row;
            long long c = 1;  // C(i, 0)
            for (int j = 0; j <= i; ++j) {
                row.push_back((int)c);
                c = c * (i - j) / (j + 1);  // C(i, j+1) = C(i, j) * (i-j) / (j+1)
            }
            res.push_back(move(row));
        }
        return res;
    }
};
```

- ⏱️ 时间复杂度：`O(numRows^2)`
- 💾 空间复杂度：`O(1)`（不计返回值）

### 解法二：逐行递推（推荐）

**思路**：利用杨辉三角的构造规律做动态规划：第 `i` 行（从 0 计）有 `i + 1` 个数，首尾恒为 `1`，中间的第 `j` 个数等于上一行的 `j - 1` 与 `j` 两个数之和。从第 0 行 `[1]` 开始逐行依据该规律构造即可。相比公式法，这种写法没有除法、没有溢出风险，是最通用、最稳妥的实现，也是本题的标准解法。

```cpp
#include <vector>

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res;
        for (int i = 0; i < numRows; ++i) {
            vector<int> row(i + 1, 1);  // 首尾先置 1
            for (int j = 1; j < i; ++j) {
                row[j] = res[i - 1][j - 1] + res[i - 1][j];  // 左上 + 右上
            }
            res.push_back(move(row));
        }
        return res;
    }
};
```

- ⏱️ 时间复杂度：`O(numRows^2)`（生成的总元素数）
- 💾 空间复杂度：`O(1)`（不计返回值所需的 `O(numRows^2)`）

## ⚠️ 易错点

- 逐行递推中内层循环范围是 `[1, i - 1]`（只算中间元素），首尾位置已初始化为 1，别重复赋值或越界。
- 行下标从 0 计，第 `i` 行有 `i + 1` 个元素，`row(i + 1, 1)` 的大小别写错。
- 组合数递推必须**先乘后除**且用整型容量足够的中间变量，`c = c / (j + 1) * (i - j)` 会丢失整除性。
- `numRows = 1` 时只应输出 `[[1]]`，注意循环边界。

---

[← 返回目录](../../README.md)
