# 131. 分割回文串

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/palindrome-partitioning/) ｜ [国际站](https://leetcode.com/problems/palindrome-partitioning/)
>
> 🟡 中等 ｜ 标签：`回溯` `动态规划`

## 📝 题目描述

给定字符串 `s`，请将 `s` 分割成一些子串，使每个子串都是**回文串**。返回 `s` 所有可能的分割方案。

分割即把字符串切成若干段连续子串，每个字符恰好属于一段；段的顺序保持原串的相对顺序。

**示例 1：**

```
输入：s = "aab"
输出：[["a","a","b"],["aa","b"]]
解释："a" | "a" | "b" 与 "aa" | "b" 两种切法，每段都是回文串。
```

**示例 2：**

```
输入：s = "a"
输出：[["a"]]
```

**示例 3：**

```
输入：s = "aaa"
输出：[["a","a","a"],["a","aa"],["aa","a"],["aaa"]]
```

**提示：**

- `1 <= s.length <= 16`
- `s` 仅由小写英文字母组成

## 💡 题解

### 解法一：回溯 + 逐段判断回文

**思路**：在字符之间有 `n - 1` 个"潜在刀口"，分割方案就是刀口的子集，这天然适合回溯枚举：`backtrack(start)` 表示要切分后缀 `s[start..]`，从 `start` 起尝试每一段的结尾 `end`——用双指针检查 `s[start..end]` 是否回文，是则把这一段切下来放入 `path`，递归切分 `s[end + 1..]`，返回后撤销。当 `start` 走到串尾，说明整串被切成了一段段回文，收集 `path`。判断回文每次现算 `O(n)`，总代价偏高但实现直接。

```cpp
#include <string>
#include <vector>

class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> ans;
        vector<string> path;
        backtrack(s, 0, path, ans);
        return ans;
    }

private:
    void backtrack(const string& s, int start,
                   vector<string>& path, vector<vector<string>>& ans) {
        if (start == static_cast<int>(s.size())) {
            ans.push_back(path);  // 整串切分完毕
            return;
        }
        for (int end = start; end < static_cast<int>(s.size()); ++end) {
            if (!isPalindrome(s, start, end)) continue;  // 非回文的段直接跳过
            path.push_back(s.substr(start, end - start + 1));
            backtrack(s, end + 1, path, ans);
            path.pop_back();
        }
    }

    bool isPalindrome(const string& s, int i, int j) {
        while (i < j) {
            if (s[i++] != s[j--]) return false;
        }
        return true;
    }
};
```

- ⏱️ 时间复杂度：`O(n × 2^n)`，切分方案上界 `2^(n-1)`，每段回文判断另付 `O(n)`
- 💾 空间复杂度：`O(n)`，递归栈与 `path`（不计输出）

### 解法二：回溯 + 区间 DP 预处理回文表（推荐）

**思路**：回文判断会被反复调用同一区间，而它本身满足**区间 DP** 结构：`s[i..j]` 是回文 ⇔ 两端字符相等 **且** 去掉两端后的 `s[i+1..j-1]` 是回文（长度小于 3 时只需看两端）。于是先用 `O(n^2)` 把表 `isPal[i][j]` 整体算好，回溯中的判断降为 `O(1)` 查表。DP 外层 `i` 必须**倒序**（或按区间长度递增），保证算 `isPal[i][j]` 时依赖的 `isPal[i+1][j-1]` 已经算好。回溯骨架与解法一完全相同，只是"能不能切这一段"变成查表。

```cpp
#include <string>
#include <vector>

class Solution {
public:
    vector<vector<string>> partition(string s) {
        int n = static_cast<int>(s.size());
        // isPal[i][j]：s[i..j] 是否为回文串
        vector<vector<bool>> isPal(n, vector<bool>(n, false));
        for (int i = n - 1; i >= 0; --i) {  // i 从大到小，保证 i+1 行先算好
            for (int j = i; j < n; ++j) {
                isPal[i][j] = (s[i] == s[j]) && (j - i < 2 || isPal[i + 1][j - 1]);
            }
        }

        vector<vector<string>> ans;
        vector<string> path;
        backtrack(s, 0, isPal, path, ans);
        return ans;
    }

private:
    void backtrack(const string& s, int start, const vector<vector<bool>>& isPal,
                   vector<string>& path, vector<vector<string>>& ans) {
        if (start == static_cast<int>(s.size())) {  // 整串切分完毕
            ans.push_back(path);
            return;
        }
        for (int end = start; end < static_cast<int>(s.size()); ++end) {
            if (!isPal[start][end]) continue;  // 不是回文的段直接跳过
            path.push_back(s.substr(start, end - start + 1));
            backtrack(s, end + 1, isPal, path, ans);
            path.pop_back();
        }
    }
};
```

- ⏱️ 时间复杂度：`O(n × 2^n + n^2)`，回文判断 `O(1)`，DP 预处理 `O(n^2)`
- 💾 空间复杂度：`O(n^2)`，回文表（递归栈 `O(n)`）

## ⚠️ 易错点

- DP 预处理的遍历顺序：`isPal[i][j]` 依赖 `isPal[i + 1][j - 1]`，外层 `i` 必须**从大到小**（或按区间长度从小到大），正序会用到尚未计算的格子。
- 收集答案的时机是 `start == n`（整串切完），而不是"每切出一段回文就收集"——后者收集的是不完整的方案。
- `substr(start, len)` 的第二个参数是**长度**，不是结束下标；本题应传 `end - start + 1`。
- 朴素解法每步都双指针判回文，最坏 `O(n × 2^n)` 中的因子 `n` 在 `n = 16` 时仍可观；预处理表虽多了 `O(n^2)` 空间，但换来判定 `O(1)`，整体更稳。

---

[← 返回目录](../../README.md)
