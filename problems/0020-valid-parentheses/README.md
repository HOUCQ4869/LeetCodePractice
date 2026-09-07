# 20. 有效的括号

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/valid-parentheses/) ｜ [国际站](https://leetcode.com/problems/valid-parentheses/)
>
> 🟢 简单 ｜ 标签：`栈`

## 📝 题目描述

给定一个只包含 `'('`、`')'`、`'['`、`']'`、`'{'`、`'}'` 的字符串 `s`，判断字符串是否**有效**。有效需满足：左括号必须用**相同类型**的右括号闭合，且必须以**正确的顺序**闭合（括号可以嵌套，但不能交叉）。

**示例 1：**

```text
输入：s = "()"
输出：true
```

**示例 2：**

```text
输入：s = "()[]{}"
输出：true
```

**示例 3：**

```text
输入：s = "(]"
输出：false
解释：'(' 与 ']' 类型不匹配。
```

**示例 4：**

```text
输入：s = "([)]"
输出：false
解释：括号交叉嵌套，不合法。
```

**提示：**

- `1 <= s.length <= 10^4`
- `s` 仅由括号 `'()[]{}'` 组成

## 💡 题解

### 解法一：循环消除相邻配对

**思路**：合法字符串中，最内层的括号对必然**相邻**。反复把串中出现的 `"()"`、`"[]"`、`"{}"` 成对删除，最终能把整串删空当且仅当字符串合法。写法简单直观，但每轮删除都要移动字符，最坏 `O(n^2)`，仅适合帮助理解。

```cpp
#include <string>

class Solution {
public:
    bool isValid(string s) {
        while (s.find("()") != string::npos || s.find("[]") != string::npos ||
               s.find("{}") != string::npos) {
            eraseAll(s, "()");
            eraseAll(s, "[]");
            eraseAll(s, "{}");
        }
        return s.empty();  // 无法继续消除后，剩余为空才合法
    }

private:
    void eraseAll(string& s, const string& p) {
        size_t pos;
        while ((pos = s.find(p)) != string::npos) {
            s.erase(pos, 2);
        }
    }
};
```

- ⏱️ 时间复杂度：`O(n^2)`
- 💾 空间复杂度：`O(1)`

### 解法二：栈匹配（推荐）

**思路**：括号嵌套的结构天然符合"后进先出"：扫描字符串，遇到**左括号**就入栈；遇到**右括号**时，它必须与**栈顶**的左括号同类型——匹配则弹栈，栈为空或类型不符则立即判定非法。扫描结束后，栈必须为空，否则说明还有左括号没被闭合（如 `"((("`）。

```cpp
#include <string>
#include <stack>

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for (char c : s) {
            if (c == '(' || c == '[' || c == '{') {
                st.push(c);  // 左括号入栈
            } else {
                // 右括号出现时栈必须非空，且栈顶是同类型的左括号
                if (st.empty()) return false;
                char t = st.top();
                st.pop();
                if ((c == ')' && t != '(') || (c == ']' && t != '[') ||
                    (c == '}' && t != '{')) {
                    return false;
                }
            }
        }
        return st.empty();  // 栈空说明所有左括号都被匹配
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`

## ⚠️ 易错点

- 右括号到来时**栈已空**要立即返回 `false`（如 `")("`），否则继续 `top()` 会越界。
- 扫描结束后必须检查 `st.empty()`：`"((("` 在扫描全程都不触发失配，但显然非法。
- 只统计各种括号的数量是否相等不够：`"([)]"` 三种括号数量都匹配，却因交叉嵌套而非法。
- 匹配要比较**类型**而不只是"是不是左括号"，用映射表或三个并列条件均可，注意别把 `(` 与 `]` 配对。

---

[← 返回目录](../../README.md)
