# 208. 实现 Trie（前缀树）

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/implement-trie-prefix-tree/) ｜ [国际站](https://leetcode.com/problems/implement-trie-prefix-tree/)
>
> 🟡 中等 ｜ 标签：`设计` `树`

## 📝 题目描述

**Trie（发音类似 "try"）或者说前缀树**是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。Trie 由一系列节点组成，从根到某一节点的路径拼出一个字符串前缀。

请你实现 Trie 类：

- `Trie()`：初始化前缀树对象；
- `void insert(string word)`：向前缀树中插入字符串 `word`；
- `bool search(string word)`：当且仅当 `word` **之前被完整插入过**时返回 `true`（精确匹配整词）；
- `bool startsWith(string prefix)`：当且仅当之前插入的某个字符串**以 `prefix` 为前缀**时返回 `true`。

各操作都应达到 `O(|word|)` 级别，这正是 Trie 相比逐个比对字符串集合的优势。

**示例 1：**

```
输入：
["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
[[],      ["apple"], ["apple"], ["app"],   ["app"],      ["app"],  ["app"]]
输出：
[null,    null,      true,      false,     true,         null,     true]

解释：
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");    // 返回 True（整词已插入）
trie.search("app");      // 返回 False（只插入过 "apple"，"app" 不是完整词）
trie.startsWith("app");  // 返回 True（"apple" 以 "app" 为前缀）
trie.insert("app");
trie.search("app");      // 返回 True（现在 "app" 是完整词了）
```

**提示：**

- `1 <= word.length, prefix.length <= 2000`
- `word` 和 `prefix` 仅由小写英文字母组成
- `insert`、`search` 和 `startsWith` 调用次数总计不超过 `3 × 10^4`

## 💡 题解

### 解法一：哈希表存子节点

**思路**：Trie 的每个节点只需两样东西：**孩子映射**（字符 → 子节点）与**词尾标记** `isEnd`。用 `unordered_map<char, TrieNode*>` 做孩子映射，写法自然、按需分配内存，且不限定字符集（想支持任意字符也只需换映射的键类型）。三个操作共用一个 `walk` 辅助函数——沿字符串逐层下钻，中途断链返回空；`startsWith` 只要走得到就为真，`search` 还要求终点 `isEnd` 为真。

```cpp
#include <string>
#include <unordered_map>

class Trie {
public:
    Trie() : root(new TrieNode()) {}

    void insert(string word) {
        TrieNode* cur = root;
        for (char ch : word) {
            if (cur->children.count(ch) == 0) {
                cur->children[ch] = new TrieNode();  // 路径缺失则新建节点
            }
            cur = cur->children[ch];
        }
        cur->isEnd = true;  // 词尾标记
    }

    bool search(string word) {
        TrieNode* node = walk(word);
        return node != nullptr && node->isEnd;  // 走得到且恰是词尾
    }

    bool startsWith(string prefix) {
        return walk(prefix) != nullptr;  // 只要路径存在即可
    }

private:
    struct TrieNode {
        unordered_map<char, TrieNode*> children;  // 字符 -> 子节点
        bool isEnd = false;                       // 是否有单词在此结束
    };

    TrieNode* root;

    // 沿字符串逐层下钻，返回走到的节点；中途断链返回 nullptr
    TrieNode* walk(const string& s) {
        TrieNode* cur = root;
        for (char ch : s) {
            auto it = cur->children.find(ch);
            if (it == cur->children.end()) return nullptr;
            cur = it->second;
        }
        return cur;
    }
};
```

- ⏱️ 时间复杂度：单次操作 `O(L)`，`L` 为词 / 前缀长度（哈希查找有常数因子）
- 💾 空间复杂度：O(所有插入字符串的总字符数)，每个节点只为实际出现的字符付出内存

### 解法二：定长数组存子节点（推荐）

**思路**：字符集固定为 26 个小写字母时，把哈希表换成**长度为 26 的指针数组**，用 `ch - 'a'` 直接下标寻址：查孩子从哈希计算降为数组随机访问，无哈希冲突、缓存更友好，是竞赛与工程中最标准的 Trie 实现。代价是每个节点固定占 26 个指针，字符稀疏时内存浪费明显——但这正是两种实现互为补充的地方。其余逻辑（`walk` 下钻、`isEnd` 区分整词与前缀）与解法一完全一致。

```cpp
#include <string>

class Trie {
public:
    Trie() : root(new TrieNode()) {}

    void insert(string word) {
        TrieNode* cur = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (cur->children[idx] == nullptr) {
                cur->children[idx] = new TrieNode();  // 路径缺失则新建节点
            }
            cur = cur->children[idx];
        }
        cur->isEnd = true;  // 词尾标记
    }

    bool search(string word) {
        const TrieNode* node = walk(word);
        return node != nullptr && node->isEnd;  // 走得到且恰是词尾
    }

    bool startsWith(string prefix) {
        return walk(prefix) != nullptr;  // 只要路径存在即可
    }

private:
    struct TrieNode {
        TrieNode* children[26] = {};  // 值初始化：全部为 nullptr
        bool isEnd = false;           // 是否有单词在此结束
    };

    TrieNode* root;

    // 沿字符串逐层下钻，返回走到的节点；中途断链返回 nullptr
    const TrieNode* walk(const string& s) const {
        const TrieNode* cur = root;
        for (char ch : s) {
            cur = cur->children[ch - 'a'];
            if (cur == nullptr) return nullptr;
        }
        return cur;
    }
};
```

- ⏱️ 时间复杂度：单次操作 `O(L)`，每步下钻严格 `O(1)`
- 💾 空间复杂度：`O(26 × 所有插入字符串的总字符数)`

## ⚠️ 易错点

- `search` 与 `startsWith` 的区别只在最后一步：前者要求终点 `isEnd == true`，后者只要路径存在；漏判 `isEnd` 会把仅作为前缀出现过的串（如只插过 `"apple"` 时查 `"app"`）误判为已插入。
- 忘记在 `insert` 结束时给末节点置 `isEnd`，导致所有 `search` 都返回 `false`。
- 数组版孩子指针必须初始化为 `nullptr`（写成 `TrieNode* children[26] = {};`）；不加 `= {}` 时数组内容是未定义的垃圾值，判空会出错。
- 建议把 `search` / `startsWith` 的公共"下钻"逻辑抽成 `walk`，两处分别复用——分开手写极易在边界（空串、断链位置）上写出不一致的代码。

---

[← 返回目录](../../README.md)
