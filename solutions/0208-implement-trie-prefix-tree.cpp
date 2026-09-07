/**
 * @file    0208-implement-trie-prefix-tree.cpp
 * @brief   208. 实现 Trie（前缀树）
 * @link    https://leetcode.cn/problems/implement-trie-prefix-tree/
 *
 * 解法：26 叉定长数组前缀树
 * 思路：每个节点含 26 个孩子指针和一个词尾标记 isEnd。insert 沿字符逐层下钻，
 *      缺失的节点随建，结尾节点置 isEnd；search / startsWith 共用 walk 下钻到
 *      前缀末节点：前缀存在即返回 true，整词还要求末节点 isEnd 为 true。
 * 时间复杂度：单次操作 O(L)，L 为词 / 前缀长度
 * 空间复杂度：O(Σ × 总字符数)，Σ = 26
 */

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
