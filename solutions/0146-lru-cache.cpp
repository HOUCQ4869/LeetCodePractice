/**
 * @file    0146-lru-cache.cpp
 * @brief   146. LRU 缓存
 * @link    https://leetcode.cn/problems/lru-cache/
 *
 * 解法：手写双向链表 + 哈希表
 * 思路：哑头/哑尾双向链表按使用时间序维护 (key, value)，哈希表存 key -> 结点；命中即 moveToFront，容量满时淘汰队尾并按结点里的 key 同步删哈希表项。
 * 时间复杂度：get / put 均为 O(1)
 * 空间复杂度：O(capacity)
 */

#include <unordered_map>

class LRUCache {
public:
    LRUCache(int capacity) : cap(capacity) {
        head.next = &tail;
        tail.prev = &head;
    }

    int get(int key) {
        auto it = pos.find(key);
        if (it == pos.end()) {
            return -1;
        }
        Node* node = it->second;
        moveToFront(node);  // 访问即视为最近使用
        return node->value;
    }

    void put(int key, int value) {
        auto it = pos.find(key);
        if (it != pos.end()) {  // 已存在：更新值并提前
            Node* node = it->second;
            node->value = value;
            moveToFront(node);
            return;
        }
        if (static_cast<int>(pos.size()) == cap) {  // 容量满：淘汰队尾
            Node* victim = tail.prev;
            detach(victim);
            pos.erase(victim->key);  // 结点存 key 就是为了这里能反查
            delete victim;
        }
        Node* node = new Node(key, value);
        pushFront(node);
        pos[key] = node;
    }

private:
    struct Node {
        int key;
        int value;
        Node* prev;
        Node* next;
        Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    void pushFront(Node* node) {  // 插到哑头之后
        node->prev = &head;
        node->next = head.next;
        head.next->prev = node;
        head.next = node;
    }

    void detach(Node* node) {  // 从链表中摘下（不释放内存）
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToFront(Node* node) {
        detach(node);
        pushFront(node);
    }

    int cap;
    Node head{0, 0};  // 哑头：head.next 是队首（最近使用）
    Node tail{0, 0};  // 哑尾：tail.prev 是队尾（最久未用）
    unordered_map<int, Node*> pos;  // key -> 链表结点
};
