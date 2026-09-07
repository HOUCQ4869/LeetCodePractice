# 763. 划分字母区间

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/partition-labels/) ｜ [国际站](https://leetcode.com/problems/partition-labels/)
>
> 🟡 中等 ｜ 标签：`贪心` `哈希表`

## 📝 题目描述

给定一个字符串 `s`，要求把它划分为**尽可能多**的片段，使得每个字母（如 `'a'`、`'b'`）最多只出现在**一个**片段中，同一个片段内可以出现多个不同的字母。

返回一个列表，列出每个片段的长度。划分结果需要把 `s` 的所有字符都覆盖且不重叠。

**示例 1：**

```
输入：s = "ababcbacadefegdehijhklij"
输出：[9,7,8]
解释：划分为 "ababcbaca"（9）、"defegde"（7）、"hijhklij"（8）。
     每个字母都只出现在一个片段中；若把 "defegde" 与 "hijhklij" 合并成更多
     或更少片段都会导致某字母跨片段出现。
```

**示例 2：**

```
输入：s = "eccbbbbdec"
输出：[10]
解释：所有字母的最后一个出现位置都在末尾附近，只能划分为一个片段。
```

**提示：**

- `1 <= s.length <= 500`
- `s` 只包含小写英文字母

## 💡 题解

### 解法一：区间合并

**思路**：把每个字母在 `s` 中第一次出现到最后一次出现之间的范围看成一个**闭区间**。一个片段要合法，必须完整包含落在其中的所有字母区间——即片段是若干个**相交或相邻**的字母区间的并集。于是问题转化为区间合并：按左端点排序后，若当前区间的左端点不超过已合并区间的右端点，就并入；否则开启新片段。每个字母区间长度之和最多为 `26 * n`，排序后线性扫描。

```cpp
#include <vector>
#include <string>
#include <algorithm>

class Solution {
public:
    vector<int> partitionLabels(string s) {
        int n = (int)s.size();
        vector<int> first(26, -1), last(26, -1);
        for (int i = 0; i < n; ++i) {
            int c = s[i] - 'a';
            if (first[c] == -1) first[c] = i;
            last[c] = i;
        }

        // 收集出现过的字母的 [first, last] 区间
        vector<pair<int, int>> segs;
        for (int c = 0; c < 26; ++c) {
            if (first[c] != -1) segs.emplace_back(first[c], last[c]);
        }
        sort(segs.begin(), segs.end());

        vector<int> res;
        int start = 0, end = -1;  // 当前片段的覆盖范围
        for (auto& [l, r] : segs) {
            if (l > end) {           // 与当前片段不相交，可在这里切一刀
                if (end != -1) res.push_back(end - start + 1);
                start = l;
                end = r;
            } else {
                end = max(end, r);   // 相交则扩展片段
            }
        }
        res.push_back(end - start + 1);  // 最后一个片段
        return res;
    }
};
```

- ⏱️ 时间复杂度：`O(n + Σ log Σ)`，其中 `Σ <= 26` 为不同字母数，整体 `O(n)`
- 💾 空间复杂度：`O(Σ)`，即 `O(26)`

### 解法二：贪心——记录最后出现位置（推荐）

**思路**：一次预处理：记录每个字母的**最后出现下标** `last[c]`。再从左往右扫描，用 `end` 维护当前片段必须延伸到的最远位置——每遇到字符 `c`，`end = max(end, last[c])`，因为 `c` 的所有出现都得留在当前片段里。当扫描下标 `i` 追上 `end` 时，说明 `[片段起点, i]` 内所有字母的最后一次出现都已覆盖，可以安全切断，记录长度并开启新片段。这正是"在能切的最早位置切"的贪心，片段数自然最多。

```cpp
#include <vector>
#include <string>

class Solution {
public:
    vector<int> partitionLabels(string s) {
        int last[26] = {0};
        int n = (int)s.size();
        for (int i = 0; i < n; ++i) last[s[i] - 'a'] = i;

        vector<int> res;
        int start = 0, end = 0;
        for (int i = 0; i < n; ++i) {
            end = max(end, last[s[i] - 'a']);  // 当前片段必须延伸到 end
            if (i == end) {                    // 片段内字母已全部收尾
                res.push_back(i - start + 1);
                start = i + 1;
            }
        }
        return res;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(26)`

## ⚠️ 易错点

- 切分条件是 `i == end` 而不是 `i >= end`，且必须**先**更新 `end` 再判断，否则会漏切。
- 只需要每个字母的**最后**出现位置，中间出现位置无需关心。
- 遍历字母时用 `s[i] - 'a'` 映射下标，别忘了预处理循环与扫描循环分开（先完整建表再扫描）。
- 别把片段长度写成 `i - start`，片段是闭区间，长度为 `i - start + 1`。
- 若某字母只出现一次，其 `first == last`，两种解法都应正确处理这一退化区间。

---

[← 返回目录](../../README.md)
