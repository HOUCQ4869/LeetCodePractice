# 5. 最长回文子串

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/longest-palindromic-substring/) ｜ [国际站](https://leetcode.com/problems/longest-palindromic-substring/)
>
> 🟡 中等 ｜ 标签：`动态规划` `中心扩展`

## 📝 题目描述

给你一个字符串 `s`，找到 `s` 中最长的**回文子串**（连续的一段），并将其返回。

回文串是正着读和反着读都相同的字符串。若存在多个长度相同的最长回文子串，返回其中任意一个即可。

**示例 1：**

```
输入：s = "babad"
输出："bab"
解释："aba" 同样是符合题意的答案。
```

**示例 2：**

```
输入：s = "cbbd"
输出："bb"
```

**示例 3：**

```
输入：s = "a"
输出："a"
```

**提示：**

- `1 <= s.length <= 1000`
- `s` 仅由数字和英文字母（大写和/或小写）组成

## 💡 题解

### 解法一：动态规划

**思路**：设 `dp[i][j]` 表示子串 `s[i..j]` 是否为回文。转移只看两端字符：

- `s[i] == s[j]` 且区间长度小于 3（长度 1、2 时中间不再有字符，长度 3 时中间只剩一个字符）时，`dp[i][j] = true`；
- 否则 `dp[i][j] = (s[i] == s[j]) && dp[i+1][j-1]`——两端匹配后，问题收缩到内层子串。

填表顺序必须保证内层的 `dp[i+1][j-1]` 先于 `dp[i][j]` 计算：**按子串长度从短到长**枚举即可。填表过程中顺手记录最长回文的起点与长度。

```cpp
#include <string>
#include <vector>

class Solution {
public:
    string longestPalindrome(string s) {
        int n = (int)s.size();
        if (n < 2) return s;
        // dp[i][j]：s[i..j] 是否为回文
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        int start = 0, bestLen = 1;
        for (int len = 1; len <= n; ++len) {          // 按长度从短到长填表
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1;
                dp[i][j] = (s[i] == s[j]) && (len < 3 || dp[i + 1][j - 1]);
                if (dp[i][j] && len > bestLen) {
                    bestLen = len;
                    start = i;
                }
            }
        }
        return s.substr(start, bestLen);
    }
};
```

- ⏱️ 时间复杂度：`O(n^2)`
- 💾 空间复杂度：`O(n^2)`

### 解法二：中心扩展（推荐）

**思路**：回文一定关于某个"中心"对称，而中心只有两类：某个字符（对应奇数长度回文，如 `"aba"`），或相邻两个字符之间的空隙（对应偶数长度回文，如 `"abba"`），合计恰好 `2n - 1` 个。逐个枚举中心，从内向外同步扩张左右指针，直到字符失配或越界，记录能达到的最长回文。相比 DP 少了 `O(n^2)` 的表格，常数也更小。

```cpp
#include <string>

class Solution {
public:
    string longestPalindrome(string s) {
        int n = (int)s.size();
        if (n < 2) return s;
        int start = 0, bestLen = 1;
        // 共 2n-1 个中心：下标 c 为偶数时中心是字符 c/2，为奇数时是 (c/2, c/2+1) 的间隙
        for (int c = 0; c < 2 * n - 1; ++c) {
            int l = c / 2, r = l + c % 2;
            while (l >= 0 && r < n && s[l] == s[r]) {  // 从中心向两侧扩张
                --l;
                ++r;
            }
            int len = r - l - 1;                       // 失配后回退一步
            if (len > bestLen) {
                bestLen = len;
                start = l + 1;
            }
        }
        return s.substr(start, bestLen);
    }
};
```

- ⏱️ 时间复杂度：`O(n^2)`（每个中心至多扩展 `O(n)` 步）
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 中心扩展必须覆盖**两类中心**：只枚举字符中心会漏掉所有偶数长度的回文（`"cbbd"` 就得不到 `"bb"`）。统一枚举 `2n - 1` 个中心最不易出错。
- 扩张循环退出时 `l`、`r` 已越界或失配，有效回文实际是 `[l+1, r-1]`，长度是 `r - l - 1`；直接用 `r - l` 会多算两个失配字符。
- DP 若按 `i` 递增的顺序填表，`dp[i+1][j-1]` 尚未计算就已被引用，结果错误；必须按长度递增（或 `i` 递减、`j` 递增）。
- 求的是**连续子串**，不是可以跳着选的子序列（那是 516 题）：如 `"abcda"` 的子串答案只是单个字符，而回文子序列可以是 `"aca"`（长度 3）。

---

[← 返回目录](../../README.md)
