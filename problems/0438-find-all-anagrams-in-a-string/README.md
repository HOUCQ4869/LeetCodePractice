# 438. 找到字符串中所有字母异位词

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/find-all-anagrams-in-a-string/) ｜ [国际站](https://leetcode.com/problems/find-all-anagrams-in-a-string/)
>
> 🟡 中等 ｜ 标签：`滑动窗口` `哈希表`

## 📝 题目描述

给定两个字符串 `s` 和 `p`，找到 `s` 中所有 `p` 的**异位词**子串，返回这些子串的**起始下标**。答案顺序不限。

异位词指通过字母重排得到的字符串（含相同的字母及相同的出现次数）。

**示例 1：**

```
输入：s = "cbaebabacd", p = "abc"
输出：[0,6]
解释：起始下标 0 的子串 "cba" 与起始下标 6 的子串 "bac" 都是 "abc" 的异位词。
```

**示例 2：**

```
输入：s = "abab", p = "ab"
输出：[0,1,2]
解释：子串 "ab"、"ba"、"ab" 均为 "ab" 的异位词。
```

**提示：**

- `1 <= s.length, p.length <= 3 * 10^4`
- `s` 和 `p` 仅包含小写英文字母

## 💡 题解

### 解法一：逐窗口排序比较（超时方案）

**思路**：窗口长度固定为 `m = |p|`，枚举 `s` 的每个起点，把窗口子串排序后与排好序的 `p` 比较，相同则记录。思路最直白，但每个窗口都要 `O(m log m)` 排序，总量 `O(n * m log m)`，大数据会超时，仅作参照。

```cpp
#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int n = s.size(), m = p.size();
        vector<int> ans;
        if (n < m) return ans;
        string sortedP = p;
        sort(sortedP.begin(), sortedP.end());
        for (int i = 0; i + m <= n; ++i) {
            string w = s.substr(i, m);
            sort(w.begin(), w.end());
            if (w == sortedP) ans.push_back(i);
        }
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n * m log m)`
- 💾 空间复杂度：`O(n + m)`

### 解法二：定长窗口 + 计数数组比较

**思路**：异位词等价于「26 个字母出现次数完全相同」。维护窗口计数 `win` 与 `p` 的计数 `need`，窗口每滑动一步只需更新**进、出**两个字符（`std::array` 支持逐元素 `==` 比较）。把排序比较变成计数比较，总量 `O(26n)`。

```cpp
#include <string>
#include <vector>
#include <array>

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int n = s.size(), m = p.size();
        vector<int> ans;
        if (n < m) return ans;
        array<int, 26> need{}, win{};
        for (char c : p) ++need[c - 'a'];
        for (int i = 0; i < m; ++i) ++win[s[i] - 'a'];
        if (win == need) ans.push_back(0);
        for (int i = m; i < n; ++i) {
            ++win[s[i] - 'a'];        // 右端进入
            --win[s[i - m] - 'a'];    // 左端离开
            if (win == need) ans.push_back(i - m + 1);
        }
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(26 * n)`
- 💾 空间复杂度：`O(26)`

### 解法三：定长窗口 + 差异计数（推荐）

**思路**：解法二每滑一步仍要比较整个计数数组。改为维护「`need - win`」的差值数组 `cnt` 以及**差值非零的字母个数** `differ`：窗口滑动时只有进、出两个字母的差值可能跨越 0，据此 `O(1)` 增减 `differ`；`differ == 0` 当且仅当两计数完全一致，即为异位词。

```cpp
#include <string>
#include <vector>
#include <array>

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int n = s.size(), m = p.size();
        vector<int> ans;
        if (n < m) return ans;
        array<int, 26> cnt{};  // need - win 的差值
        for (char c : p) ++cnt[c - 'a'];
        for (int i = 0; i < m; ++i) --cnt[s[i] - 'a'];
        int differ = 0;  // 差值非零的字母个数
        for (int x : cnt) {
            if (x != 0) ++differ;
        }
        if (differ == 0) ans.push_back(0);
        for (int i = m; i < n; ++i) {
            int in = s[i] - 'a', out = s[i - m] - 'a';
            if (cnt[in] == 0) ++differ;   // 进入字符：差值将从 0 变为 -1
            --cnt[in];
            if (cnt[in] == 0) --differ;
            if (cnt[out] == 0) ++differ;  // 离开字符：差值将从 0 变为 +1
            ++cnt[out];
            if (cnt[out] == 0) --differ;
            if (differ == 0) ans.push_back(i - m + 1);
        }
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n + m)`
- 💾 空间复杂度：`O(26)`

## ⚠️ 易错点

- `s` 比 `p` 短时直接返回空列表。
- 差异计数的更新顺序：必须**先**判断旧值是否为 0（决定 `differ` 增减）、**再**修改 `cnt`，写反会漏更新。
- 窗口右端从 `i = m` 开始滑动时，离开的字符是 `s[i - m]`，别误写成 `s[i - m - 1]`。
- 记录答案的下标是窗口左端 `i - m + 1`（或直接枚举左端），容易差一。

---

[← 返回目录](../../README.md)
