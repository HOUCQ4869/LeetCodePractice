# 32. 最长有效括号

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/longest-valid-parentheses/) ｜ [国际站](https://leetcode.com/problems/longest-valid-parentheses/)
>
> 🔴 困难 ｜ 标签：`动态规划` `栈`

## 📝 题目描述

给定一个只包含 `'('` 和 `')'` 的字符串 `s`，找出其中**最长**的**格式正确且连续**的有效括号子串的长度。

有效括号串需满足：从左到右扫描时，任意前缀中 `'('` 的数量都不少于 `')'` 的数量，且最终两者数量相等。

**示例 1：**

```
输入：s = "(()"
输出：2
解释：最长有效括号子串是 "()"。
```

**示例 2：**

```
输入：s = ")()())"
输出：4
解释：最长有效括号子串是 "()()"。
```

**示例 3：**

```
输入：s = ""
输出：0
```

**提示：**

- `0 <= s.length <= 3 * 10^4`
- `s[i]` 为 `'('` 或 `')'`

## 💡 题解

### 解法一：栈

**思路**：栈里存**下标**而不是字符。栈底始终保留一个"当前有效段左侧的分界下标"（初始为 `-1` 哨兵）。扫描过程：

- 遇 `'('`：下标入栈，等待匹配；
- 遇 `')'`：先弹出栈顶。弹出后若栈变空，说明这个 `')'` 无法匹配，把它自身作为新的分界下标入栈；若栈非空，当前 `')'` 与栈顶对应的 `'('`（或分界）之间构成有效段，长度为 `i - st.top()`。

每个元素至多入栈出栈一次，一遍扫完。

```cpp
#include <string>
#include <stack>
#include <algorithm>

class Solution {
public:
    int longestValidParentheses(string s) {
        int best = 0;
        stack<int> st;
        st.push(-1);  // 分界哨兵：最后一个未匹配位置
        for (int i = 0; i < (int)s.size(); ++i) {
            if (s[i] == '(') {
                st.push(i);
            } else {
                st.pop();
                if (st.empty()) {
                    st.push(i);              // 无法匹配的 ')' 成为新分界
                } else {
                    best = max(best, i - st.top());
                }
            }
        }
        return best;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`

### 解法二：动态规划

**思路**：设 `dp[i]` 为**以 `s[i]` 结尾**的最长有效括号长度（`s[i]` 必是 `')'`，否则为 0）。分两种情况：

- `s[i-1] == '('`：形如 `...()`，直接配对，`dp[i] = dp[i-2] + 2`（若 `i >= 2`）；
- `s[i-1] == ')'`：形如 `...))`，需要向前跳过长度 `dp[i-1]` 的有效段，看再前一个字符是否是 `'('`。设 `j = i - dp[i-1] - 1`，若 `s[j] == '('`，则 `dp[i] = dp[i-1] + 2 + dp[j-1]`——最后加上 `dp[j-1]` 是为了把紧邻前面的有效段拼接起来（如 `"()(()())"` 中结尾段要接上开头的 `"()"`）。

```cpp
#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int longestValidParentheses(string s) {
        int n = (int)s.size();
        vector<int> dp(n, 0);  // 以 i 结尾的最长有效括号长度
        int best = 0;
        for (int i = 1; i < n; ++i) {
            if (s[i] == ')') {
                if (s[i - 1] == '(') {
                    // 情形一："...()" 直接配对
                    dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
                } else if (int j = i - dp[i - 1] - 1; j >= 0 && s[j] == '(') {
                    // 情形二："...((...))" 跳过内层有效段再配对，并拼接前段
                    dp[i] = dp[i - 1] + 2 + (j >= 1 ? dp[j - 1] : 0);
                }
                best = max(best, dp[i]);
            }
        }
        return best;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`

### 解法三：双向扫描计数（推荐）

**思路**：用两个计数器 `left`、`right` 分别记录当前段中 `'('` 与 `')'` 的个数。

- **从左向右**扫：两数相等时，`2 * left` 是一段有效长度，更新答案；一旦 `right > left`，当前段已不可能有效，双双清零。
- 但单向扫描会漏掉 `left > right` 悬而不决的情况（如 `"(()"`），所以再**从右向左**扫一遍，方向对称：`left > right` 时清零。

两个方向合起来覆盖所有情形，全程不用栈和数组。证明思路：任何有效段的两个端点必然在某一方向扫描中恰好"配平"。

```cpp
#include <string>
#include <algorithm>

class Solution {
public:
    int longestValidParentheses(string s) {
        int n = (int)s.size();
        int best = 0;

        // 从左到右：right 超过 left 即失效
        int left = 0, right = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '(') ++left; else ++right;
            if (left == right) {
                best = max(best, 2 * right);
            } else if (right > left) {
                left = right = 0;
            }
        }

        // 从右到左：left 超过 right 即失效
        left = right = 0;
        for (int i = n - 1; i >= 0; --i) {
            if (s[i] == '(') ++left; else ++right;
            if (left == right) {
                best = max(best, 2 * left);
            } else if (left > right) {
                left = right = 0;
            }
        }
        return best;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 栈解法里存的是**下标**，且必须先 `pop` 再判断栈空，把空栈时的 `')'` 下标压回作为新分界。
- DP 情形二别忘记拼接 `dp[j - 1]`：`"()(()())"` 若漏加前段，答案会从 8 错成 6。
- DP 的所有下标（`i - 2`、`j - 1`）都要检查非负，否则越界。
- 双向扫描只扫一个方向是不够的：`"(()"` 与 `"())"` 分别只能被其中一个方向正确捕捉。
- 求的是**连续子串**长度，不是可离散选取的括号对数，别把问题当成 20 题"有效括号"的删除版。

---

[← 返回目录](../../README.md)
