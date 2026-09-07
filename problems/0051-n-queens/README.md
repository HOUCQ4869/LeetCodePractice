# 51. N 皇后

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/n-queens/) ｜ [国际站](https://leetcode.com/problems/n-queens/)
>
> 🔴 困难 ｜ 标签：`回溯`

## 📝 题目描述

按照国际象棋规则，皇后可以攻击与其处在**同一行、同一列或同一斜线**上的棋子。在 `n × n` 的棋盘上放置 `n` 个皇后，使它们**互不攻击**（即任意两个皇后不同行、不同列、不同对角线）。

返回所有不同的棋盘摆放方案。每个方案用字符矩阵表示：`'Q'` 代表一个皇后，`'.'` 代表空位。

**示例 1：**

```
输入：n = 4
输出：[[".Q..","...Q","Q...","..Q."],
      ["..Q.","Q...","...Q",".Q.."]]
解释：4 皇后问题恰有两个解。如上所示，两个解互为中心对称。
```

**示例 2：**

```
输入：n = 1
输出：[["Q"]]
```

**提示：**

- `1 <= n <= 9`

## 💡 题解

### 解法一：回溯 + 逐个检查冲突

**思路**：因为任意两个皇后不能同行，可以直接按**行**放置——第 `row` 行恰好放一个皇后，递归到第 `n` 行即为一个完整解。放置前用 `isValid` 线性扫描前 `row` 行，检查同列或同对角线（列差绝对值等于行差）冲突。这是最直观的版本，冲突检查 `O(n)`，用来建立问题模型。

```cpp
#include <string>
#include <vector>

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<int> queenCol(n, -1);           // queenCol[r]：第 r 行皇后所在列
        vector<string> board(n, string(n, '.'));
        backtrack(n, 0, queenCol, board, ans);
        return ans;
    }

private:
    void backtrack(int n, int row, vector<int>& queenCol, vector<string>& board,
                   vector<vector<string>>& ans) {
        if (row == n) {
            ans.push_back(board);
            return;
        }
        for (int col = 0; col < n; ++col) {
            if (!isValid(queenCol, row, col)) continue;
            queenCol[row] = col;
            board[row][col] = 'Q';
            backtrack(n, row + 1, queenCol, board, ans);
            board[row][col] = '.';  // 恢复现场
            queenCol[row] = -1;
        }
    }

    bool isValid(const vector<int>& queenCol, int row, int col) {
        for (int r = 0; r < row; ++r) {
            int dc = col - queenCol[r];
            if (dc == 0 || row - r == dc || row - r == -dc) {  // 同列或同对角线
                return false;
            }
        }
        return true;
    }
};
```

- ⏱️ 时间复杂度：`O(n!)` 量级（含 `O(n)` 的逐次冲突检查）
- 💾 空间复杂度：`O(n)`，递归栈与辅助数组（不计输出）

### 解法二：回溯 + 列 / 对角线标记数组

**思路**：冲突检查的瓶颈在于每次都重新扫描已放置的皇后。观察攻击方向的代数性质可以 `O(1)` 判定：

- **列** `col`：直接做下标；
- **主对角线（↘ 方向）**：同一对角线上 `row + col` 为定值，范围 `0 ~ 2n - 2`；
- **副对角线（↙ 方向）**：同一对角线上 `row - col` 为定值，范围 `-(n-1) ~ n-1`，加 `n - 1` 偏移到 `0 ~ 2n - 2`。

用三个布尔数组分别标记这三类线是否已被占用，放置 / 撤销各改三个下标，判定从 `O(n)` 降到 `O(1)`。

```cpp
#include <string>
#include <vector>

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<string> board(n, string(n, '.'));
        vector<bool> cols(n, false), mainDiag(2 * n - 1, false), antiDiag(2 * n - 1, false);
        backtrack(n, 0, board, cols, mainDiag, antiDiag, ans);
        return ans;
    }

private:
    void backtrack(int n, int row, vector<string>& board, vector<bool>& cols,
                   vector<bool>& mainDiag, vector<bool>& antiDiag,
                   vector<vector<string>>& ans) {
        if (row == n) {
            ans.push_back(board);
            return;
        }
        for (int col = 0; col < n; ++col) {
            int md = row + col;              // 副对角线编号（/ 方向）
            int ad = row - col + n - 1;      // 主对角线编号（\ 方向），偏移到非负
            if (cols[col] || mainDiag[md] || antiDiag[ad]) continue;
            cols[col] = mainDiag[md] = antiDiag[ad] = true;
            board[row][col] = 'Q';
            backtrack(n, row + 1, board, cols, mainDiag, antiDiag, ans);
            board[row][col] = '.';
            cols[col] = mainDiag[md] = antiDiag[ad] = false;  // 恢复现场
        }
    }
};
```

- ⏱️ 时间复杂度：`O(n!)` 量级，冲突判定 `O(1)`
- 💾 空间复杂度：`O(n)`，三个标记数组与递归栈（不计输出）

### 解法三：回溯 + 位运算（推荐）

**思路**：`n <= 9`，三个标记数组可以压缩成三个**整数位掩码**：`cols`、`d1`、`d2` 的第 `b` 位为 1 表示"当前行上第 `b` 列 / 第 `b` 条 ↘ 对角线 / 第 `b` 条 ↙ 对角线受攻击"。进入下一行时，对角线攻击会整体**平移一格**：↘ 方向每下一行列号 +1，掩码左移一位；↙ 方向列号 -1，掩码右移一位——递归参数直接传移位后的新掩码，无需任何数组与撤销操作。当前行的可用列 = `~(cols | d1 | d2) & full`（`full` 为低 `n` 位全 1）；用 `lowbit`（`x & -x`）逐个取出可用列，配合 `__builtin_ctz` 求列号。判定、枚举、撤销全部变成几次位运算，是 N 皇后的最快写法。

```cpp
#include <string>
#include <vector>

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        this->n = n;
        full = (1u << n) - 1;
        board.assign(n, string(n, '.'));
        ans.clear();
        backtrack(0, 0, 0, 0);
        return ans;
    }

private:
    int n = 0;
    unsigned full = 0;  // 低 n 位全 1：合法列掩码
    vector<string> board;
    vector<vector<string>> ans;

    // row：当前行；cols / d1 / d2：列、↘ 对角线、↙ 对角线在当前行上的攻击位
    void backtrack(int row, unsigned cols, unsigned d1, unsigned d2) {
        if (row == n) {
            ans.push_back(board);  // n 行全部放好，收集棋盘快照
            return;
        }
        unsigned avail = ~(cols | d1 | d2) & full;  // 当前行仍可放皇后的列
        while (avail) {
            unsigned p = avail & -avail;  // 取最低位的 1（lowbit）
            int col = __builtin_ctz(p);   // 该位对应的列号
            board[row][col] = 'Q';
            // 下一行：列不变；↘ 对角线左移一位、↙ 对角线右移一位
            backtrack(row + 1, cols | p, (d1 | p) << 1, (d2 | p) >> 1);
            board[row][col] = '.';
            avail &= avail - 1;  // 去掉该位，尝试下一个可用列
        }
    }
};
```

- ⏱️ 时间复杂度：`O(n!)` 量级，位运算使每步判定与枚举都是常数条指令
- 💾 空间复杂度：`O(n)`，递归栈与棋盘（`n <= 9` 时掩码用 32 位整数绰绰有余）

## ⚠️ 易错点

- 对角线编号：`row + col` 天然落在 `0 ~ 2n - 2`；`row - col` 含负数，**必须加 `n - 1` 偏移**再做数组下标，否则越界或漏判。
- 按行放置保证每行恰一个皇后，因此冲突检查**只需与之前的行比较**，不必维护"同行"检查；若允许任意位置放置则模型完全不同。
- 位运算版两条对角线的**移位方向**要与列掩码的约定一致：↘ 方向（下一行列号 +1）左移、↙ 方向（下一行列号 -1）右移，写反会静默漏解。
- 收集的是棋盘**快照**（`ans.push_back(board)` 拷贝），直接存引用会被后续回溯改掉；位运算版还注意 `n` 超过 32 时掩码会溢出（本题 `n <= 9` 无碍）。

---

[← 返回目录](../../README.md)
