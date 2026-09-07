# 394. 字符串解码

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/decode-string/) ｜ [国际站](https://leetcode.com/problems/decode-string/)
>
> 🟡 中等 ｜ 标签：`栈`

## 📝 题目描述

给定一个经过编码的字符串 `s`，返回解码后的字符串。编码规则为 `k[encoded_string]`，表示方括号内的字符串重复 `k` 次，其中 `k` 为正整数。方括号可以嵌套，需从内向外逐层展开。`s` 由小写英文字母、数字和方括号组成，题目保证输入总是有效的。

**示例 1：**

```text
输入：s = "3[a]2[bc]"
输出："aaabcbc"
解释：a 重复 3 次得到 aaa，bc 重复 2 次得到 bcbc，拼接为 aaabcbc。
```

**示例 2：**

```text
输入：s = "3[a2[c]]"
输出："accaccacc"
解释：内层 2[c] 展开为 cc，外层 3[acc] 展开为 accaccacc。
```

**示例 3：**

```text
输入：s = "2[abc]3[cd]ef"
输出："abcabccdcdcdef"
```

**提示：**

- `1 <= s.length <= 30`
- `s` 由小写英文字母、数字和方括号 `'[]'` 组成
- 题目保证 `s` 是有效的输入，`k` 的取值范围为 `[1, 300]`
- 保证解码后的字符串长度不超过 `10^5`

## 💡 题解

### 解法一：递归下降

**思路**：把 `k[...]` 视为一个可递归的子问题：顺序扫描字符串，普通字母直接追加到当前层结果；遇到数字就读完整数（可能多位），随后跳过 `'['`，把从当前位置开始的括号内容交给递归函数解码，得到内层结果后重复 `k` 次追加。递归天然按"从内向外"的顺序展开嵌套括号。用引用参数 `i` 贯穿各层，记录当前扫描位置。

```cpp
#include <string>
#include <cctype>

class Solution {
public:
    string decodeString(string s) {
        int i = 0;
        return parse(s, i);
    }

private:
    // 解析 s[i..] 直到遇到 ']' 或字符串末尾的一段，并推进 i
    string parse(const string& s, int& i) {
        string res;
        int n = s.size();
        while (i < n && s[i] != ']') {
            if (!isdigit(s[i])) {
                res += s[i++];  // 普通字母直接追加
            } else {
                int k = 0;
                while (isdigit(s[i])) {
                    k = k * 10 + (s[i++] - '0');  // 读完整数（可能多位）
                }
                ++i;                         // 跳过 '['
                string inner = parse(s, i);  // 递归解码括号内部
                ++i;                         // 跳过 ']'
                while (k--) res += inner;    // 重复 k 次
            }
        }
        return res;
    }
};
```

- ⏱️ 时间复杂度：`O(解码后字符串长度)`
- 💾 空间复杂度：`O(嵌套深度 + 解码后字符串长度)`

### 解法二：双栈迭代（推荐）

**思路**：递归能做的栈也能做。维护**数字栈**（每层括号的重复次数）与**字符串栈**（进入该层括号前已拼好的串），配一个当前层正在构建的字符串 `cur`：

- 遇到数字：累加进 `num`（可能多位）；
- 遇到 `'['`：把 `(cur, num)` 压栈保存"现场"，然后清空 `cur`、置零 `num`，开始收集括号内的内容；
- 遇到 `']'`：弹出 `(prev, k)`，结果为 `prev + k 份 cur`，赋回 `cur`，完成一层展开；
- 遇到字母：直接追加到 `cur`。

扫描结束后 `cur` 即完整解码结果，避免了递归的函数栈开销。

```cpp
#include <string>
#include <stack>
#include <cctype>
#include <utility>

class Solution {
public:
    string decodeString(string s) {
        stack<int> numSt;     // 每层括号的重复次数
        stack<string> strSt;  // 进入该层括号前已拼好的字符串
        string cur;           // 当前层正在构建的字符串
        int num = 0;          // 当前读到的重复次数
        for (char c : s) {
            if (isdigit(c)) {
                num = num * 10 + (c - '0');  // 数字可能有多位
            } else if (c == '[') {
                numSt.push(num);  // 保存现场：重复次数
                strSt.push(cur);  // 保存现场：之前的字符串
                cur.clear();
                num = 0;
            } else if (c == ']') {
                int k = numSt.top();
                numSt.pop();
                string prev = strSt.top();
                strSt.pop();
                for (int t = 0; t < k; t++) {
                    prev += cur;  // 拼出 prev + k 份 cur
                }
                cur = move(prev);
            } else {
                cur += c;  // 普通字母直接追加
            }
        }
        return cur;
    }
};
```

- ⏱️ 时间复杂度：`O(解码后字符串长度)`
- 💾 空间复杂度：`O(解码后字符串长度)`

## ⚠️ 易错点

- 数字可能不止一位（如 `"100[leetcode]"`），必须用 `num = num * 10 + (c - '0')` 累加读取，按单字符处理会得到错误次数。
- 遇到 `'['` 时要先把**当前的 `num` 与 `cur` 压栈并清零/清空**，否则下一层会覆盖上一层的现场，`]` 展开时拿不到之前的串和次数。
- 展开 `']'` 的拼接顺序是 `prev + k 份 cur`（外层串在前），写反会得到 `k 份 cur + prev` 的错误顺序。
- 解码结果可能远长于原串（`k` 最大 300 且可嵌套），拼接时用 `+=` / `move` 减少无谓拷贝。

---

[← 返回目录](../../README.md)
