# 1143. 最长公共子序列

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/longest-common-subsequence/) ｜ [国际站](https://leetcode.com/problems/longest-common-subsequence/)
>
> 🟡 中等 ｜ 标签：`动态规划` `字符串`

## 📝 题目描述

给定两个字符串 `text1` 和 `text2`，返回它们**最长公共子序列**的长度；不存在公共子序列则返回 `0`。

**子序列**是从原字符串中删除若干个（也可以不删）字符、且不改变剩余字符相对位置得到的新字符串——例如 `"ace"` 是 `"abcde"` 的子序列，但 `"aec"` 不是。

公共子序列是同时属于两个字符串的子序列。

**示例 1：**

```
输入：text1 = "abcde", text2 = "ace"
输出：3
解释：最长公共子序列是 "ace"，长度为 3。
```

**示例 2：**

```
输入：text1 = "abc", text2 = "abc"
输出：3
解释：最长公共子序列是 "abc"，长度为 3。
```

**示例 3：**

```
输入：text1 = "abc", text2 = "def"
输出：0
解释：两个字符串没有公共子序列，返回 0。
```

**提示：**

- `1 <= text1.length, text2.length <= 1000`
- `text1` 和 `text2` 仅由小写英文字母组成

## 💡 题解

### 解法一：二维动态规划

**思路**：设 `dp[i][j]` 表示 `text1` 的前 `i` 个字符与 `text2` 的前 `j` 个字符的 LCS 长度（`dp[0][*]`、`dp[*][0]` 均为 0）。考察两个前缀的最后一个字符：

- `text1[i-1] == text2[j-1]`：这个字符一定可以接到两者 LCS 的末尾，`dp[i][j] = dp[i-1][j-1] + 1`（可证明不劣于舍弃其一的任何方案）；
- 不相等：LCS 不可能同时以这两个字符结尾，至少要舍弃其一，`dp[i][j] = max(dp[i-1][j], dp[i][j-1])`。

答案为 `dp[m][n]`。

```cpp
#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = (int)text1.size(), n = (int)text2.size();
        // dp[i][j]：text1 前 i 个与 text2 前 j 个字符的 LCS 长度
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
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

**思路**：计算第 `i` 行只用到上一行与当前行左侧的值，可压缩成一维。关键是用 `prev` 保管左上角 `dp[i-1][j-1]`：进入第 `j` 列前先把旧值 `dp[j]`（即 `dp[i-1][j]`）暂存到 `cur`，本列更新完再把 `cur` 移交给 `prev` 供下一列使用。另外把较短的串放到内层做列，空间进一步降为 `O(min(m, n))`。

```cpp
#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        if (text1.size() < text2.size()) swap(text1, text2);  // 短串做列，空间更省
        int m = (int)text1.size(), n = (int)text2.size();
        vector<int> dp(n + 1, 0);
        for (int i = 1; i <= m; ++i) {
            int prev = 0;                        // dp[i-1][j-1]，j=1 时即 dp[i-1][0] = 0
            for (int j = 1; j <= n; ++j) {
                int cur = dp[j];                 // 暂存 dp[i-1][j]
                if (text1[i - 1] == text2[j - 1]) {
                    dp[j] = prev + 1;
                } else {
                    dp[j] = max(dp[j], dp[j - 1]);
                }
                prev = cur;
            }
        }
        return dp[n];
    }
};
```

- ⏱️ 时间复杂度：`O(mn)`
- 💾 空间复杂度：`O(min(m, n))`

## ⚠️ 易错点

- 字符**相等**时应取 `dp[i-1][j-1] + 1`，不要写成 `max(dp[i-1][j], dp[i][j-1]) + 1`：后者会重复利用同一字符，如 `text1 = "aab"`、`text2 = "a"` 时会错算出 2。
- 滚动数组里 `prev` 必须在覆盖 `dp[j]` **之前**从旧值 `dp[j]` 接过来，且每行开始时重置为 0（对应 `dp[i-1][0]`），否则左上角会错位一行。
- 下标偏移：`dp` 按"前 i 个字符"定义（1 基），访问字符要写 `text1[i-1]`、`text2[j-1]`，直接用 `text1[i]` 在 `i == m` 时越界。
- 答案就是 `dp[m][n]`，不需要中途记录最大值（dp 值随 `i`、`j` 单调不减），别照搬回文题"打表取 max"的写法。

---

[← 返回目录](../../README.md)
