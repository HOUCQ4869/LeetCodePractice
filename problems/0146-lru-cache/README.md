# 146. LRU 缓存

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/lru-cache/) ｜ [国际站](https://leetcode.com/problems/lru-cache/)
>
> 🟡 中等 ｜ 标签：`设计` `哈希表` `双向链表`

## 📝 题目描述

请设计并实现一个满足 **LRU（最近最少使用）** 约束的缓存结构，支持如下操作：

- `LRUCache(int capacity)`：以正整数 `capacity` 初始化容量；
- `int get(int key)`：如果关键字 `key` 存在于缓存中，返回其值，否则返回 `-1`；
- `void put(int key, int value)`：关键字已存在则变更其值；不存在则插入该键值对。若插入导致关键字数量超过 `capacity`，**逐出最久未使用**的关键字。

函数 `get` 与 `put` 每次调用均计为一次"使用"；`put` 更新已存在的关键字也算使用。要求 `get` 与 `put` 的平均时间复杂度为 `O(1)`。

**示例 1：**

```
输入：
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
输出：
[null, null, null, 1, null, -1, null, -1, 3, 4]

解释：
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1);      // 缓存是 {1=1}
lRUCache.put(2, 2);      // 缓存是 {1=1, 2=2}
lRUCache.get(1);         // 返回 1，此时 1 变为最近使用
lRUCache.put(3, 3);      // 容量已满，逐出最久未使用的 2，缓存是 {1=1, 3=3}
lRUCache.get(2);         // 返回 -1（未找到）
lRUCache.put(4, 4);      // 逐出最久未使用的 1，缓存是 {4=4, 3=3}
lRUCache.get(1);         // 返回 -1（未找到）
lRUCache.get(3);         // 返回 3
lRUCache.get(4);         // 返回 4
```

**提示：**

- `1 <= capacity <= 3000`
- `0 <= key <= 10^4`
- `0 <= value <= 10^5`
- 最多调用 `2 * 10^5` 次 `get` 和 `put`

## 💡 题解

### 解法一：STL `list` + `unordered_map`

**思路**：LRU 需要两件事——`O(1)` 定位某个 key、`O(1)` 调整它的使用次序。用 `list<pair<int,int>>` 按时间序存 `(key, value)`（表头 = 最近使用，表尾 = 最久未用），哈希表存 `key -> 链表迭代器`。命中后用 `splice` 把对应结点搬到表头——它只重接指针、**不使其他迭代器失效**，正好胜任；淘汰时删表尾结点并按其 `key` 同步删哈希表项。

```cpp
class LRUCache {
public:
    LRUCache(int capacity) : cap(capacity) {}

    int get(int key) {
        auto it = pos.find(key);
        if (it == pos.end()) {
            return -1;
        }
        cache.splice(cache.begin(), cache, it->second);  // 搬到表头 = 最近使用
        return it->second->second;
    }

    void put(int key, int value) {
        auto it = pos.find(key);
        if (it != pos.end()) {  // 已存在：更新值并提前
            it->second->second = value;
            cache.splice(cache.begin(), cache, it->second);
            return;
        }
        if (static_cast<int>(cache.size()) == cap) {  // 满了：淘汰表尾
            pos.erase(cache.back().first);
            cache.pop_back();
        }
        cache.emplace_front(key, value);
        pos[key] = cache.begin();
    }

private:
    int cap;
    list<pair<int, int>> cache;  // (key, value)，表头为最近使用
    unordered_map<int, list<pair<int, int>>::iterator> pos;  // key -> 迭代器
};
```

- ⏱️ 时间复杂度：`get` / `put` 均为 `O(1)`
- 💾 空间复杂度：`O(capacity)`

### 解法二：手写双向链表 + 哈希表（推荐）

**思路**：把链表部分换成自己实现：**哑头 + 哑尾**的双向链表配「key → 结点指针」哈希表，头插、摘除都是 `O(1)`，还省掉了 STL 迭代器的细节。两个关键点：① 结点必须**同时存 `key` 和 `value`**——淘汰队尾结点时要反查它的 `key` 才能同步删哈希表项，只存 `value` 的新手写法在这里卡死；② 哑结点让"链表为空""只剩一个""淘汰队尾"等边界全部统一，不必判空。面试白板可写，也能体现对指针操作的掌握。

```cpp
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
```

- ⏱️ 时间复杂度：`get` / `put` 均为 `O(1)`
- 💾 空间复杂度：`O(capacity)`

## ⚠️ 易错点

- 双向链表结点必须**同时存 `key`**：淘汰队尾时要从结点反查 `key` 删除哈希表项，只存 `value` 会漏删映射，之后 `get` 旧 key 命中悬垂指针。
- `put` 更新已存在的 key 是"**原地更新 + 提前**"，不是"先淘汰再插入"；`get` 与 `put` 命中都要刷新使用时间。
- 淘汰必须发生在**插入之前**（先删队尾腾位，再 `new` 新结点入表），顺序颠倒会出现瞬时超容。
- 用裸的头/尾指针（无哑结点）时，空表插入、单元素删除、淘汰队尾都需特判，极易写错；哑头/哑尾能统一所有边界。
- 哈希表与链表是**同一份数据的两份索引**，任何增删改都必须两边同步，漏掉一边就会出现"链表里有、表里没有"或反之的幽灵状态。

---

[← 返回目录](../../README.md)
