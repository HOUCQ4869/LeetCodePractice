# 22. 括号生成

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/generate-parentheses/) ｜ [国际站](https://leetcode.com/problems/generate-parentheses/)
>
> 🟡 中等 ｜ 标签：`回溯` `深度优先搜索`

## 📝 题目描述

数字 `n` 代表生成括号的对数。请你设计一个函数，用于能够生成所有可能的并且**有效的**括号组合。

有效括号组合需满足：整个串中左括号与右括号数量相等，且任意前缀中右括号的数量不超过左括号的数量。

**示例 1：**

```
输入：n = 3
输出：["((()))","(()())","(())()","()(())","()()()"]
```

**示例 2：**

```
输入：n = 1
输出：["()"]
```

**提示：**

- `1 <= n <= 8`

## 💡 题解

### 解法一：暴力枚举 + 合法性检查

**思路**：长度为 `2n` 的串，每个位置不是 `'('` 就是 `')'`，先无脑枚举全部 `2^(2n)` 种串，再逐一用"前缀和非负 + 总和为零"检验合法性。它只用来理解问题规模与"剪枝从何而来"：`n = 8` 时要枚举 `2^16 = 65536` 个串，而其中合法的只有第 `n` 个**卡特兰数** `C(n)`（`n = 8` 时仅 1430 个）——绝大多数分支在构造中途就已注定非法。

```cpp
#include <string>
#include <vector>

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        string cur(2 * n, ' ');
        brute(n, 0, cur, ans);
        return ans;
    }

private:
    void brute(int n, int pos, string& cur, vector<string>& ans) {
        if (pos == 2 * n) {
            if (valid(cur)) ans.push_back(cur);  // 枚举完再检查
            return;
        }
        cur[pos] = '(';
        brute(n, pos + 1, cur, ans);
        cur[pos] = ')';
        brute(n, pos + 1, cur, ans);
    }

    bool valid(const string& s) {
        int balance = 0;
        for (char c : s) {
            balance += (c == '(') ? 1 : -1;
            if (balance < 0) return false;  // 前缀中右括号更多，非法
        }
        return balance == 0;
    }
};
```

- ⏱️ 时间复杂度：`O(2^(2n) × n)`，枚举全部串再各花 `O(n)` 检查
- 💾 空间复杂度：`O(n)`，递归栈与当前串（不计输出）

### 解法二：回溯——构造过程中剪枝（推荐）

**思路**：非法串的特征在**前缀**里就暴露（右括号多于左括号），因此不必等构造完再检查，而是在每一步放置前就保证前缀仍合法。维护两个计数：`open`（已放左括号数）与 `close`（已放右括号数），放置规则为：

- `open < n` 时可以放 `'('`——左括号还没用完；
- `close < open` 时可以放 `')'`——右括号数严格小于左括号数，放下去前缀仍然合法。

按规则生成的**每一个**到达长度 `2n` 的串都天然合法，直接收集。搜索树从"满二叉树"收缩为"只含合法前缀的树"，枚举量从 `2^(2n)` 降到卡特兰数 `C(n)`。

```cpp
#include <string>
#include <vector>

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        string path;
        backtrack(n, 0, 0, path, ans);
        return ans;
    }

private:
    // open / close：已使用的左 / 右括号个数
    void backtrack(int n, int open, int close, string& path, vector<string>& ans) {
        if (static_cast<int>(path.size()) == 2 * n) {
            ans.push_back(path);  // 构造过程中已保证合法
            return;
        }
        if (open < n) {  // 左括号还没用完，可以放 '('
            path.push_back('(');
            backtrack(n, open + 1, close, path, ans);
            path.pop_back();
        }
        if (close < open) {  // 右括号数小于左括号数，前缀仍合法，可放 ')'
            path.push_back(')');
            backtrack(n, open, close + 1, path, ans);
            path.pop_back();
        }
    }
};
```

- ⏱️ 时间复杂度：`O(4^n / √n)`，卡特兰数 `C(n)` 的渐近规模乘上每个串的 `O(n)` 输出
- 💾 空间复杂度：`O(n)`，递归栈与 `path`（不计输出）

## ⚠️ 易错点

- 放右括号的条件是 `close < open`（**严格小于**）；写成 `close < n` 会生成 `")("` 之类前缀非法的串，写成 `close <= open` 则会多放一个右括号。
- 终止条件是路径长度到达 `2n`；只判断 `open == n` 会在右括号还没补齐时提前收集。
- 两个分支（放左、放右）各自都要 `push_back` / `pop_back` **成对出现**，只在其中一个分支撤销会污染后续路径。
- 暴力解法的合法性检查必须同时验证"任意前缀右括号不越界"与"总数平衡"，只查总数会放过 `")("`。

---

[← 返回目录](../../README.md)
