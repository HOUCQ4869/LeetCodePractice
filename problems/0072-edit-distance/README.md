# 72. 编辑距离

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/edit-distance/) ｜ [国际站](https://leetcode.com/problems/edit-distance/)
>
> 🔴 困难 ｜ 标签：`动态规划` `字符串`

## 📝 题目描述

给你两个单词 `word1` 和 `word2`，请返回将 `word1` 转换成 `word2` 所使用的**最少操作数**。

每次可以对 `word1` 执行如下三种操作之一：

- 插入一个字符
- 删除一个字符
- 替换一个字符

**示例 1：**

```
输入：word1 = "horse", word2 = "ros"
输出：3
解释：
horse -> rorse (将 'h' 替换为 'r')
rorse -> rose  (删除 'r')
rose  -> ros   (删除 'e')
```

**示例 2：**

```
输入：word1 = "intention", word2 = "execution"
输出：5
解释：
intention -> inention  (删除 't')
inention  -> enention  (将 'i' 替换为 'e')
enention  -> exention  (将 'n' 替换为 'x')
exention  -> exection  (将 'n' 替换为 'c')
exection  -> execution (插入 'u')
```

**提示：**

- `0 <= word1.length, word2.length <= 500`
- `word1` 和 `word2` 由小写英文字母组成

## 💡 题解

### 解法一：二维动态规划

**思路**：设 `dp[i][j]` 表示 `word1` 的前 `i` 个字符变成 `word2` 的前 `j` 个字符所需的最少操作数。边界：`dp[i][0] = i`（删光 `i` 个字符），`dp[0][j] = j`（逐个插入 `j` 个字符）。考察两串末尾字符：

- `word1[i-1] == word2[j-1]`：末尾已对齐，无需任何操作，`dp[i][j] = dp[i-1][j-1]`；
- 不相等：最后一步必是三种操作之一，取代价最小——
  - **替换**：把 `word1[i-1]` 改成 `word2[j-1]`，余下 `dp[i-1][j-1]`；
  - **删除**：删掉 `word1[i-1]`，余下 `dp[i-1][j]`；
  - **插入**：在 `word1` 末尾补上 `word2[j-1]`，余下 `dp[i][j-1]`。

  即 `dp[i][j] = 1 + min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1])`。

答案为 `dp[m][n]`。

```cpp
#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = (int)word1.size(), n = (int)word2.size();
        // dp[i][j]：word1 前 i 个字符变成 word2 前 j 个字符的最少操作数
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int i = 0; i <= m; ++i) dp[i][0] = i;  // 全部删除
        for (int j = 0; j <= n; ++j) dp[0][j] = j;  // 全部插入
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];    // 末尾对齐，无需操作
                } else {
                    dp[i][j] = 1 + min({dp[i - 1][j - 1],  // 替换
                                        dp[i - 1][j],      // 删除 word1[i-1]
                                        dp[i][j - 1]});    // 插入 word2[j-1]
                }
            }
        }
        return dp[m][n];
    }
};
```

- ⏱️ 时间复杂度：`O(mn)`
- 💾 空间复杂度：`O(mn)`

### 解法二：滚动数组（推荐）

**思路**：转移只依赖本行左侧、正上方与左上角三个值，压成一维后用 `prev` 保管左上角 `dp[i-1][j-1]`：进入第 `j` 列前先把旧 `dp[j]`（即 `dp[i-1][j]`）暂存到 `cur`，本列更新完再移交给 `prev`。注意每行开始要先把上一行的 `dp[0]` 存入 `prev`，再把 `dp[0]` 更新为 `i`（对应 `dp[i][0] = i`），顺序不能颠倒。

```cpp
#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = (int)word1.size(), n = (int)word2.size();
        vector<int> dp(n + 1);
        for (int j = 0; j <= n; ++j) dp[j] = j;   // 第 0 行：dp[0][j] = j
        for (int i = 1; i <= m; ++i) {
            int prev = dp[0];                      // dp[i-1][0]
            dp[0] = i;                             // dp[i][0] = i
            for (int j = 1; j <= n; ++j) {
                int cur = dp[j];                   // 暂存 dp[i-1][j]
                if (word1[i - 1] == word2[j - 1]) {
                    dp[j] = prev;                  // 末尾对齐，无需操作
                } else {
                    dp[j] = 1 + min({dp[j],        // 删除 word1[i-1]（旧 dp[j]）
                                     dp[j - 1],    // 插入 word2[j-1]
                                     prev});       // 替换
                }
                prev = cur;
            }
        }
        return dp[n];
    }
};
```

- ⏱️ 时间复杂度：`O(mn)`
- 💾 空间复杂度：`O(n)`

## ⚠️ 易错点

- 边界 `dp[i][0] = i`、`dp[0][j] = j` 分别是"删光"与"逐个插入"的代价，别初始化成 0；空串是合法输入（长度可以为 0）。
- 字符相等时必须走 `dp[i-1][j-1]` 分支：若一律写 `1 + min(...)`，`"a" -> "a"` 会算成 1 而正确答案是 0。
- 三种操作与下标的对应容易记反：`dp[i-1][j] + 1` 是**删除** `word1[i-1]`，`dp[i][j-1] + 1` 是在末尾**插入** `word2[j-1]`，`dp[i-1][j-1] + 1` 是**替换**——都在 `min` 里时结果不受影响，但还原具体操作序列的变形题（如打印方案）会出错。
- 滚动数组中 `prev = dp[0]` 与 `dp[0] = i` 的先后顺序不能反：必须先取走上一行的 `dp[i-1][0]`，再覆盖为本行的 `dp[i][0]`。

---

[← 返回目录](../../README.md)
