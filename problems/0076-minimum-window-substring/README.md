# 76. 最小覆盖子串

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/minimum-window-substring/) ｜ [国际站](https://leetcode.com/problems/minimum-window-substring/)
>
> 🔴 困难 ｜ 标签：`滑动窗口` `哈希表`

## 📝 题目描述

给你字符串 `s` 和 `t`，返回 `s` 中涵盖 `t` **所有字符**（含重复字符的次数要求）的**最小**子串。如果 `s` 中不存在这样的子串，返回空字符串 `""`。

题目保证答案唯一（若存在）。

**示例 1：**

```
输入：s = "ADOBECODEBANC", t = "ABC"
输出："BANC"
解释：最小覆盖子串 "BANC" 包含 t 中的 'A'、'B'、'C' 各一个。
```

**示例 2：**

```
输入：s = "a", t = "a"
输出："a"
解释：整个字符串即最小覆盖子串。
```

**示例 3：**

```
输入：s = "a", t = "aa"
输出：""
解释：t 中两个 'a' 都必须被覆盖，s 中只有一个 'a'，无解。
```

**提示：**

- `1 <= s.length, t.length <= 10^5`
- `s` 和 `t` 由英文字母（含大小写）组成

## 💡 题解

### 解法一：滑动窗口 + 计数数组整体比较

**思路**：`need` 记录 `t` 中每个字符的需求，`win` 记录窗口内每个字符的数量。右指针扩张直到窗口覆盖 `t`，随后左指针收缩到极限并记录最优，如此往复。判断「是否覆盖」时逐项扫描 128 维计数数组比较 `win[c] >= need[c]`，每次判断 `O(|Σ|)`。框架直观，适合入门。

```cpp
#include <string>
#include <vector>
#include <array>

class Solution {
public:
    string minWindow(string s, string t) {
        int n = s.size();
        array<int, 128> need{};
        for (char c : t) ++need[c];
        array<int, 128> win{};
        int bestLen = n + 1, bestStart = -1;
        int l = 0;
        for (int r = 0; r < n; ++r) {
            ++win[s[r]];
            while (covers(win, need)) {  // 已覆盖，收缩左边界
                if (r - l + 1 < bestLen) {
                    bestLen = r - l + 1;
                    bestStart = l;
                }
                --win[s[l++]];
            }
        }
        return bestStart < 0 ? "" : s.substr(bestStart, bestLen);
    }

private:
    // 判断窗口计数是否覆盖需求计数（逐项 O(128)）
    static bool covers(const array<int, 128>& win, const array<int, 128>& need) {
        for (int c = 0; c < 128; ++c) {
            if (win[c] < need[c]) return false;
        }
        return true;
    }
};
```

- ⏱️ 时间复杂度：`O(n * |Σ| + m)`，`|Σ| = 128`
- 💾 空间复杂度：`O(|Σ|)`

### 解法二：滑动窗口 + 有效字符计数（推荐）

**思路**：把「是否覆盖」的判断降为 `O(1)`。`need[c]` 记录 `t` 中字符还差多少，`required` 是 `t` 中出现的字符种数；窗口扩张/收缩时，某字符的数量**恰好达到**需求就令 `formed++`，**跌破**需求就令 `formed--`。`formed == required` 即覆盖。右指针扩张、满足后左指针收缩并记录最优，两指针各走一趟。

```cpp
#include <string>
#include <array>
#include <climits>

class Solution {
public:
    string minWindow(string s, string t) {
        array<int, 128> need{};
        for (char c : t) {
            ++need[c];
        }
        int required = 0;  // t 中出现过的字符种数
        for (int x : need) {
            if (x > 0) ++required;
        }
        array<int, 128> win{};
        int formed = 0;  // 窗口内已凑够次数的字符种数
        int bestLen = INT_MAX, bestStart = 0;
        int l = 0;
        for (int r = 0; r < static_cast<int>(s.size()); ++r) {
            char c = s[r];
            ++win[c];
            if (need[c] > 0 && win[c] == need[c]) ++formed;  // 恰好凑够一种
            while (formed == required) {                      // 已覆盖，收缩左边界
                if (r - l + 1 < bestLen) {
                    bestLen = r - l + 1;
                    bestStart = l;
                }
                char d = s[l++];
                if (need[d] > 0 && win[d] == need[d]) --formed;  // 先判断再减计数
                --win[d];
            }
        }
        return bestLen == INT_MAX ? "" : s.substr(bestStart, bestLen);
    }
};
```

- ⏱️ 时间复杂度：`O(n + m)`
- 💾 空间复杂度：`O(|Σ|)`，`|Σ| = 128`

## ⚠️ 易错点

- `t` 含重复字符，覆盖要求**次数也够**，不能只比较字符集合（示例 3）。
- 收缩左边界时，判断与减计数的顺序：必须**先**检查 `win[d] == need[d]` 再 `--win[d]`，否则 `formed` 漏更新、死循环或漏答案。
- 循环中只记录最优窗口的起点和长度，最后统一 `substr`，不要反复构造临时字符串。
- `s`、`t` 含大小写字母，计数数组要开 128（不能只开 26），并注意无符号索引。

---

[← 返回目录](../../README.md)
