# 49. 字母异位词分组

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/group-anagrams/) ｜ [国际站](https://leetcode.com/problems/group-anagrams/)
>
> 🟡 中等 ｜ 标签：`哈希表` `字符串`

## 📝 题目描述

给定一个字符串数组 `strs`，将**字母异位词**组合在一起，返回分组后的结果。

字母异位词指的是**字母完全相同、仅排列顺序不同**的字符串，例如 `"eat"` 与 `"tea"`。返回结果中组与组之间的顺序、每组内部的顺序均可以是任意的。

**示例 1：**

```
输入：strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
输出：[["bat"],["nat","tan"],["ate","eat","tea"]]
解释：互为异位词的字符串被聚合到同一组。
```

**示例 2：**

```
输入：strs = [""]
输出：[[""]]
```

**示例 3：**

```
输入：strs = ["a"]
输出：[["a"]]
```

**提示：**

- `1 <= strs.length <= 10^4`
- `0 <= strs[i].length <= 100`
- `strs[i]` 仅包含小写英文字母

## 💡 题解

### 解法一：排序后的字符串作为哈希键

**思路**：互为异位词的两个字符串，把各自字符排序后一定得到完全相同的串；反之，排序结果不同就必然不是异位词。于是以「排序后的串」为哈希键，把原字符串聚合到同一个桶中，最后把所有桶按任意顺序输出即可。思路简单、不易出错。

```cpp
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;
        for (const string& s : strs) {
            string key = s;
            sort(key.begin(), key.end());  // 异位词排序后必然相同
            groups[key].push_back(s);
        }
        vector<vector<string>> ans;
        for (auto& kv : groups) {
            ans.push_back(move(kv.second));
        }
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n * k log k)`，`n` 为字符串数量，`k` 为字符串最大长度
- 💾 空间复杂度：`O(n * k)`

### 解法二：字母计数编码作为哈希键（推荐）

**思路**：异位词的本质特征是「每个字母出现次数相同」。为每个字符串统计 26 个字母的出现次数，把这份计数拼成固定格式的字符串（如 `"1#0#2#…#"`）作为哈希键，即可省去排序，键的构造从 `O(k log k)` 降为 `O(k)`。注意拼接时**必须加分隔符**，否则计数 `1,11` 与 `11,1` 会拼出相同的键，导致错误合并。

```cpp
#include <vector>
#include <string>
#include <array>
#include <unordered_map>

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;
        for (const string& s : strs) {
            array<int, 26> cnt{};
            for (char c : s) {
                ++cnt[c - 'a'];
            }
            string key;
            for (int x : cnt) {  // 用 '#' 分隔，避免 "1|11" 与 "11|1" 之类的键冲突
                key += to_string(x);
                key += '#';
            }
            groups[key].push_back(s);
        }
        vector<vector<string>> ans;
        for (auto& kv : groups) {
            ans.push_back(move(kv.second));
        }
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n * k)`
- 💾 空间复杂度：`O(n * k)`

## ⚠️ 易错点

- 计数拼接键必须加分隔符（如 `#`），否则不同的计数序列可能拼出相同的键。
- 空字符串是合法输入，它自身构成一组；`""` 作为哈希键也完全合法，不要特判跳过。
- 结果顺序题目不作要求，不要额外排序浪费时间。
- 想用 `vector<int>` 作键需要自定义哈希函数，直接拼成 `string` 作键最省事。

---

[← 返回目录](../../README.md)
