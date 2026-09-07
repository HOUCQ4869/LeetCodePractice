# 17. 电话号码的字母组合

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/letter-combinations-of-a-phone-number/) ｜ [国际站](https://leetcode.com/problems/letter-combinations-of-a-phone-number/)
>
> 🟡 中等 ｜ 标签：`回溯` `哈希表`

## 📝 题目描述

给定一个仅包含数字 `2` 到 `9` 的字符串 `digits`，返回它能表示的所有字母组合。答案可以按任意顺序返回。

数字到字母的映射与电话九宫格键盘一致（与阿拉伯数字上的字母相同）：

- `2` → `abc`，`3` → `def`，`4` → `ghi`，`5` → `jkl`
- `6` → `mno`，`7` → `pqrs`，`8` → `tuv`，`9` → `wxyz`

注意 `digits` 为空串时应返回**空数组**，而不是包含空串的数组。

**示例 1：**

```
输入：digits = "23"
输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]
解释：数字 2 可选 a/b/c，数字 3 可选 d/e/f，两两组合共 3 × 3 = 9 种。
```

**示例 2：**

```
输入：digits = ""
输出：[]
```

**示例 3：**

```
输入：digits = "2"
输出：["a","b","c"]
```

**提示：**

- `0 <= digits.length <= 4`
- `digits[i]` 是范围 `['2', '9']` 的一个数字

## 💡 题解

### 解法一：迭代逐位拼接

**思路**：把组合过程看作"逐位扩展"：初始只有空串前缀；处理第 `i` 个数字时，把已有每个前缀分别拼上该数字对应的每个字母，得到新的前缀集合。处理完所有数字，剩下的就是全部组合。例如 `"23"`：`{""}` → `{"a","b","c"}` → `{"ad","ae",…,"cf"}`。无递归、无撤销，思路直白；代价是每轮重建整个字符串数组，常数开销略大。

```cpp
#include <string>
#include <vector>

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};

        const vector<string> mapping = {"", "", "abc", "def", "ghi",
                                        "jkl", "mno", "pqrs", "tuv", "wxyz"};
        vector<string> curr = {""};  // 空前缀出发
        for (char d : digits) {
            vector<string> next;
            for (const string& prefix : curr) {
                for (char ch : mapping[d - '0']) {  // 拼上该数字的每个字母
                    next.push_back(prefix + ch);
                }
            }
            curr = std::move(next);
        }
        return curr;
    }
};
```

- ⏱️ 时间复杂度：`O(4^n × n)`，`n` 为数字位数（7、9 各对应 4 个字母），每个组合构造 `O(n)`
- 💾 空间复杂度：`O(n)`，当前轮的前缀集合（不计输出）

### 解法二：回溯（推荐）

**思路**：这是回溯专题最纯粹的入门题——**每一层决策一个数字对应的字母**。`path` 逐位追加字符，`pos` 扫描 `digits`；每层只枚举当前数字映射的字母，选定后递归 `pos + 1`，返回后 `pop_back()` 撤销。当 `pos` 到达串尾，每个数字都选定了一个字母，把 `path` 拷贝进答案。相比迭代法无需整层重建字符串，状态只在一条路径上增减；这套"路径 + 位置 + 撤销"的骨架可以直接迁移到全排列、组合、括号生成等所有回溯题。注意特判：空输入返回 `{}`。

```cpp
#include <string>
#include <vector>

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};  // 空输入返回空数组，而不是 [""]

        // 下标即数字：0、1 没有对应字母，占位为空串
        const vector<string> mapping = {"", "", "abc", "def", "ghi",
                                        "jkl", "mno", "pqrs", "tuv", "wxyz"};
        vector<string> ans;
        string path;
        backtrack(digits, 0, mapping, path, ans);
        return ans;
    }

private:
    void backtrack(const string& digits, int pos, const vector<string>& mapping,
                   string& path, vector<string>& ans) {
        if (pos == static_cast<int>(digits.size())) {
            ans.push_back(path);  // 每个数字都选定了一个字母
            return;
        }
        for (char ch : mapping[digits[pos] - '0']) {  // 只枚举当前数字的字母
            path.push_back(ch);
            backtrack(digits, pos + 1, mapping, path, ans);
            path.pop_back();  // 回溯：撤销选择
        }
    }
};
```

- ⏱️ 时间复杂度：`O(4^n × n)`，组合总数不超过 `4^n`，每个拷贝 `O(n)`
- 💾 空间复杂度：`O(n)`，递归栈与 `path`（不计输出）

## ⚠️ 易错点

- `digits` 为空串时必须返回**空数组** `{}` 而不是 `{""}`——从空前缀迭代到底或忘记特判回溯入口，都会多出一个空串。
- 映射表用**下标即数字**的组织方式（`0`、`1` 占位空串），用 `digits[pos] - '0'` 直接索引；若按 '2' 到 '9' 顺序硬编码字符串，极易错位。
- 每层只应枚举**当前数字**对应的字母集合，把所有数字的字母混在一层枚举会得到长度错误的串。
- 收集答案时要拷贝 `path`（`push_back(path)` 传值），`path` 在回溯中会被继续修改。

---

[← 返回目录](../../README.md)
