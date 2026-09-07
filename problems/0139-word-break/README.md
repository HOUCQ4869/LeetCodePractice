# 139. 单词拆分

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/word-break/) ｜ [国际站](https://leetcode.com/problems/word-break/)
>
> 🟡 中等 ｜ 标签：`动态规划` `哈希表`

## 📝 题目描述

给定一个字符串 `s` 和一个字符串列表 `wordDict` 作为字典，判断是否可以利用字典中出现的单词拼接出 `s`。

注意：**字典中的单词可以重复使用**，且字典中不存在重复单词。

**示例 1：**

```
输入：s = "leetcode", wordDict = ["leet", "code"]
输出：true
解释：s 可以由 "leet" + "code" 拼接而成。
```

**示例 2：**

```
输入：s = "applepenapple", wordDict = ["apple", "pen"]
输出：true
解释：s = "apple" + "pen" + "apple"，"apple" 被重复使用是允许的。
```

**示例 3：**

```
输入：s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
输出：false
解释：无论 "cats"+"and..." 还是 "cat"+"sand..." 都无法完整拼出 "catsandog"。
```

**提示：**

- `1 <= s.length <= 300`
- `1 <= wordDict.length <= 1000`
- `1 <= wordDict[i].length <= 20`
- `s` 和 `wordDict[i]` 仅由小写英文字母组成

## 💡 题解

### 解法一：记忆化搜索

**思路**：设 `canBreak(start)` 表示 `s` 的后缀 `s[start..]` 能否被字典拼出。枚举第一个单词的结束位置 `end`：若 `s[start..end)` 在字典中且 `canBreak(end)` 为真，则整个后缀可拼出。用数组缓存结果避免重复递归；用 `unordered_set` 做 O(1) 的单词查找。

```cpp
#include <string>
#include <vector>
#include <unordered_set>

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        dict = unordered_set<string>(wordDict.begin(), wordDict.end());
        memo.assign(s.size(), -1);  // -1 未计算，0 假，1 真
        return dfs(s, 0);
    }

private:
    unordered_set<string> dict;
    vector<int> memo;

    bool dfs(const string& s, int start) {
        if (start == (int)s.size()) return true;  // 完整拼出
        if (memo[start] != -1) return memo[start];
        bool ok = false;
        for (int end = start + 1; end <= (int)s.size() && !ok; ++end) {
            if (dict.count(s.substr(start, end - start))) {
                ok = dfs(s, end);
            }
        }
        return memo[start] = ok;
    }
};
```

- ⏱️ 时间复杂度：`O(n^2 * m)`（`n` 为 `s` 长度，`m` 为单词平均长度，含哈希与子串构造）
- 💾 空间复杂度：`O(n + 字典总长)`

### 解法二：动态规划（推荐）

**思路**：设 `dp[i]` 表示 `s` 的前 `i` 个字符（即前缀 `s[0..i)`）能否被拼出，`dp[0] = true`（空前缀恒可拼）。转移时枚举最后一个单词的起点 `j`：若 `dp[j]` 为真且子串 `s[j..i)` 在字典中，则 `dp[i] = true`。答案为 `dp[n]`。相比记忆化搜索，迭代版自底向上，无递归栈开销。用 `unordered_set` 存字典后每次子串查询是 O(1)（子串构造本身 O(长度)）。

```cpp
#include <string>
#include <vector>
#include <unordered_set>

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        int n = (int)s.size();
        vector<bool> dp(n + 1, false);
        dp[0] = true;  // 空串可拼出
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                // 前缀 s[0..j) 可拼，且 s[j..i) 是字典单词
                if (dp[j] && dict.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[n];
    }
};
```

- ⏱️ 时间复杂度：`O(n^2 * m)`（`m` 为单词平均长度）
- 💾 空间复杂度：`O(n + 字典总长)`

## ⚠️ 易错点

- `dp` 数组长度是 `n + 1`，`dp[0]` 表示空串且必须初始化为 `true`，否则所有转移失败。
- 内层枚举 `j` 找到一组合法切分即可 `break`，继续枚举只是浪费时间。
- 枚举最后一个单词的**起点**比枚举第一个单词的终点更符合 DP 语义（`dp[j]` 已算好），别把下标方向写反。
- 单词长度上限可用来剪枝：`i - j` 超过字典里最长单词长度时提前终止内层循环。
- `substr(pos, len)` 的参数是"起点 + 长度"，不是"起点 + 终点"，容易传错。

---

[← 返回目录](../../README.md)
