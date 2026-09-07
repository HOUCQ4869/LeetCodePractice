# 3. 无重复字符的最长子串

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/longest-substring-without-repeating-characters/) ｜ [国际站](https://leetcode.com/problems/longest-substring-without-repeating-characters/)
>
> 🟡 中等 ｜ 标签：`滑动窗口` `哈希表`

## 📝 题目描述

给定一个字符串 `s`，请你找出其中不含有重复字符的**最长子串**（连续）的长度。

**示例 1：**

```
输入：s = "abcabcbb"
输出：3
解释：无重复字符的最长子串是 "abc"，长度为 3。
```

**示例 2：**

```
输入：s = "bbbbb"
输出：1
解释：无重复字符的最长子串是 "b"，长度为 1。
```

**示例 3：**

```
输入：s = "pwwkew"
输出：3
解释：最长子串是 "wke"，长度为 3。注意答案必须是子串，"pwke" 是子序列而非子串。
```

**提示：**

- `0 <= s.length <= 5 * 10^4`
- `s` 由英文字母、数字、符号和空格组成

## 💡 题解

### 解法一：枚举起点 + 哈希集合

**思路**：枚举每个起点 `i`，从 `i` 出发尽量向右扩展，用哈希集合判重，遇到重复字符立即停止，记录能达到的最远长度。起点之间的工作无法复用，最坏 `O(n^2)`（如全相同字符）。

```cpp
#include <string>
#include <unordered_set>

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size(), best = 0;
        for (int i = 0; i < n; ++i) {
            unordered_set<char> seen;
            int j = i;
            while (j < n && !seen.count(s[j])) {
                seen.insert(s[j]);
                ++j;
            }
            best = max(best, j - i);
        }
        return best;
    }
};
```

- ⏱️ 时间复杂度：`O(n^2)`
- 💾 空间复杂度：`O(min(n, |Σ|))`

### 解法二：滑动窗口 + 哈希集合

**思路**：右指针不断扩张窗口；仅当新字符与窗口内字符重复时，左指针逐步收缩（把左端字符移出集合）直到重复消除。每个字符至多进出窗口各一次，整体 `O(n)`。

```cpp
#include <string>
#include <unordered_set>

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> seen;
        int best = 0, l = 0;
        for (int r = 0; r < static_cast<int>(s.size()); ++r) {
            while (seen.count(s[r])) {  // 出现重复，收缩左边界
                seen.erase(s[l++]);
            }
            seen.insert(s[r]);
            best = max(best, r - l + 1);
        }
        return best;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(|Σ|)`

### 解法三：滑动窗口 + 记录最后出现位置（推荐）

**思路**：解法二中左指针是一位一位挪的，其实可以**直接跳跃**。用数组 `last[c]` 记录每个字符最近一次出现的下标；右指针扫到 `c` 时，若 `last[c]` 落在当前窗口内（`last[c] >= l`），则把左边界一步跳到 `last[c] + 1`。窗口长度始终用 `r - l + 1` 计算，一趟扫描，常数极小。

```cpp
#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> last(128, -1);  // 每个字符最后出现的下标
        int best = 0;
        for (int l = 0, r = 0; r < static_cast<int>(s.size()); ++r) {
            int c = static_cast<unsigned char>(s[r]);
            if (last[c] >= l) {
                l = last[c] + 1;  // 重复字符仍在窗口内，左边界直接跳过它
            }
            last[c] = r;
            best = max(best, r - l + 1);
        }
        return best;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(|Σ|)`，`|Σ| = 128`

## ⚠️ 易错点

- 求的是**子串**（连续），不是子序列，别用最长不重复子序列的 DP 去做。
- 解法三的左边界只能向右移动：必须判断 `last[c] >= l` 才跳跃，否则 `s = "abba"` 这类输入会让 `l` 倒退。
- 字符集不只小写字母（含空格、符号），计数数组要开到 128，并对字符做无符号转换防止负下标。
- 跳跃后窗口长度按 `r - l + 1` 重新计算，不要沿用旧值。

---

[← 返回目录](../../README.md)
