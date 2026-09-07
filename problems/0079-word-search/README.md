# 79. 单词搜索

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/word-search/) ｜ [国际站](https://leetcode.com/problems/word-search/)
>
> 🟡 中等 ｜ 标签：`回溯`

## 📝 题目描述

给定一个 `m × n` 二维字符网格 `board` 和一个字符串单词 `word`。如果 `word` 存在于网格中，返回 `true`；否则返回 `false`。

单词必须按照**字母顺序**，通过**上下左右相邻**的单元格内的字母构成一条路径；同一个单元格内的字母**在一条路径中不允许被重复使用**。

**示例 1：**

```
输入：board = [["A","B","C","E"],
              ["S","F","C","S"],
              ["A","D","E","E"]], word = "ABCCED"
输出：true
解释：A(0,0) -> B(0,1) -> C(0,2) -> C(1,2) -> E(2,2) -> D(2,1)。
```

**示例 2：**

```
输入：board = [["A","B","C","E"],
              ["S","F","C","S"],
              ["A","D","E","E"]], word = "SEE"
输出：true
解释：S(1,3) -> E(2,3) -> E(2,2)，路径不重复经过同一格。
```

**示例 3：**

```
输入：board = [["A","B","C","E"],
              ["S","F","C","S"],
              ["A","D","E","E"]], word = "ABCB"
输出：false
解释：匹配 A->B->C 后需要再找一个相邻的 B，但最近的 B 已在路径上用过。
```

**提示：**

- `1 <= m, n <= 6`
- `1 <= word.length <= 15`
- `board` 和 `word` 仅由大小写英文字母组成

## 💡 题解

### 解法一：回溯 + visited 数组

**思路**：单词可能从**任何格子**开始匹配，因此枚举每个起点做 DFS。递归函数 `dfs(i, j, k)` 表示"从 `(i, j)` 出发匹配 `word[k..]`"：当前格字符不等于 `word[k]` 立即失败；`k` 已是最后一个字符则成功；否则向四邻扩展。为满足"同一格子在一条路径内不能重复使用"，用 `visited` 数组标记本路径走过的格子，**进入时置位、递归返回后复位**——复位这一步就是回溯的"恢复现场"，它保证不同路径之间互不干扰。任一起点成功即整体返回 `true`。

```cpp
#include <string>
#include <vector>

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = static_cast<int>(board.size());
        int n = static_cast<int>(board[0].size());
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dfs(board, visited, word, i, j, 0)) return true;  // 任一起点成功即可
            }
        }
        return false;
    }

private:
    bool dfs(vector<vector<char>>& board, vector<vector<bool>>& visited,
             const string& word, int i, int j, int k) {
        if (board[i][j] != word[k] || visited[i][j]) return false;
        if (k + 1 == static_cast<int>(word.size())) return true;  // 最后一个字符匹配成功

        visited[i][j] = true;  // 占用当前格
        static const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        bool found = false;
        for (int t = 0; t < 4 && !found; ++t) {
            int ni = i + dirs[t][0];
            int nj = j + dirs[t][1];
            if (ni >= 0 && ni < static_cast<int>(board.size())
                && nj >= 0 && nj < static_cast<int>(board[0].size())) {
                found = dfs(board, visited, word, ni, nj, k + 1);
            }
        }
        visited[i][j] = false;  // 回溯：释放当前格
        return found;
    }
};
```

- ⏱️ 时间复杂度：`O(M × N × 3^L)`，`L` 为 `word` 长度（起点 `M × N` 个；首步 4 个方向，其后每步至多 3 个未回头的方向）
- 💾 空间复杂度：`O(MN)`，visited 数组（递归栈 `O(L)`）

### 解法二：回溯 + 原地标记与词频剪枝（推荐）

**思路**：在解法一的基础上做两处优化：

1. **原地标记**：既然棋盘字符集不含 `'#'`，可直接把走过的格子改写成 `'#'` 充当 visited 标记，递归返回前恢复原字符——省掉整个 `O(MN)` 的 visited 数组，缓存局部性也更好。
2. **词频剪枝**：搜索前统计棋盘上每个字符的出现次数；若 `word` 中某字符的需求量超过棋盘存量，直接返回 `false`。这对"棋盘很小、单词里却堆满某稀有字符"的用例一刀切掉全部搜索。

其余逻辑不变：从每个起点出发，四方向回溯，`k` 走到 `word` 末尾即成功。

```cpp
#include <string>
#include <vector>

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        // 剪枝：word 中某字符的出现次数超过棋盘中该字符总数，必然无解
        int cnt[128] = {0};
        for (const auto& row : board) {
            for (char c : row) ++cnt[static_cast<unsigned char>(c)];
        }
        for (char c : word) {
            if (--cnt[static_cast<unsigned char>(c)] < 0) return false;
        }

        int m = static_cast<int>(board.size());
        int n = static_cast<int>(board[0].size());
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dfs(board, word, i, j, 0)) return true;  // 任一起点成功即可
            }
        }
        return false;
    }

private:
    // 尝试从 (i, j) 出发匹配 word[k..]
    bool dfs(vector<vector<char>>& board, const string& word, int i, int j, int k) {
        if (board[i][j] != word[k]) return false;
        if (k + 1 == static_cast<int>(word.size())) return true;  // 最后一个字符匹配成功

        board[i][j] = '#';  // 原地标记：当前格已在路径上
        static const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        bool found = false;
        for (int t = 0; t < 4 && !found; ++t) {
            int ni = i + dirs[t][0];
            int nj = j + dirs[t][1];
            if (ni >= 0 && ni < static_cast<int>(board.size())
                && nj >= 0 && nj < static_cast<int>(board[0].size())) {
                found = dfs(board, word, ni, nj, k + 1);
            }
        }
        board[i][j] = word[k];  // 回溯：恢复原字符
        return found;
    }
};
```

- ⏱️ 时间复杂度：`O(M × N × 3^L)`，词频剪枝可整体跳过明显无解的输入
- 💾 空间复杂度：`O(L)`，仅递归栈深度（标记直接写在棋盘上）

## ⚠️ 易错点

- **恢复现场不能省**：无论本分支成功与否都要把标记撤销（原地法恢复原字符、visited 法复位），否则失败路径会污染后续起点的搜索，把本来存在的解判成不存在。
- 标记时机是"进入格子时设置、返回后撤销"；写成"递归返回后才设置"逻辑完全错误。
- 找到一个成功路径就要立即层层返回 `true`（短路），否则会继续做无意义的全量搜索。
- 原地标记用 `'#'` 占位的前提是**字符集里没有 `'#'`**（本题仅英文字母）；若字符集开放，必须退回 visited 数组方案。

---

[← 返回目录](../../README.md)
