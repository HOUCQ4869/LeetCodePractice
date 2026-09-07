# 138. 随机链表的复制

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/copy-list-with-random-pointer/) ｜ [国际站](https://leetcode.com/problems/copy-list-with-random-pointer/)
>
> 🟡 中等 ｜ 标签：`链表` `哈希表`

## 📝 题目描述

给定一个长度为 `n` 的链表，每个结点除了普通的 `next` 指针外，还包含一个 `random` 指针，它可以指向链表中的**任意结点**，也可以为空。

请构造这个链表的**深拷贝**：新建 `n` 个结点，使新链表中 `next` 与 `random` 指向的都是**新链表里的结点**（不能指向原链表的任何结点），且两者的结构完全一致。返回新链表的头结点。

**示例 1：**

```
输入：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
输出：[[7,null],[13,0],[11,4],[10,2],[1,0]]
解释：每个二元组为 [val, random 指向结点的下标]（null 表示空）。
原链中 13、1 的 random 指向 7 号结点，11 的 random 指向 1 号结点，
10 的 random 指向 11 号结点；拷贝出的新链保持完全相同的指向关系。
```

**示例 2：**

```
输入：head = [[1,1],[2,1]]
输出：[[1,1],[2,1]]
解释：两个结点的 random 都指向链表最后一个结点（值为 2 的那个）。
```

**示例 3：**

```
输入：head = [[3,null],[3,0],[3,null]]
输出：[[3,null],[3,0],[3,null]]
```

**提示：**

- `0 <= n <= 1000`
- `-10^4 <= Node.val <= 10^4`
- `Node.random` 为 `null` 或指向链表中的结点
- 每个结点的 `val` 互不相同

## 💡 题解

### 解法一：哈希表

**思路**：深拷贝的难点只在 `random`——顺着 `next` 走随时能复制，但 `random` 可能指向"还没创建的结点"。用一张「原结点 → 拷贝结点」的哈希表化解：第一趟只管复制每个结点本身并登记映射；第二趟再统一接线，原结点的 `next` 指向谁，拷贝的 `next` 就查表取谁的拷贝，`random` 同理。两趟走完，所有指针都落在新建结点上。

```cpp
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }
        unordered_map<Node*, Node*> copied;  // 原结点 -> 拷贝结点
        // 第一趟：复制每个结点并登记映射
        for (Node* cur = head; cur != nullptr; cur = cur->next) {
            copied[cur] = new Node(cur->val);
        }
        // 第二趟：按原链的 next / random 关系查表接线
        for (Node* cur = head; cur != nullptr; cur = cur->next) {
            copied[cur]->next = (cur->next != nullptr) ? copied[cur->next] : nullptr;
            copied[cur]->random = (cur->random != nullptr) ? copied[cur->random] : nullptr;
        }
        return copied[head];
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`（哈希表）

### 解法二：原地拼接与拆分（推荐）

**思路**：不借助哈希表也能建立"原结点 → 拷贝结点"的映射——把拷贝直接**插到原结点后面**。三趟完成：① 复制：每个原结点后插入它的拷贝，形成 `1 -> 1' -> 2 -> 2' -> …` 的交错链，原结点 `cur` 的拷贝就是 `cur->next`；② 接 `random`：原结点的 `random` 指向某原结点，而那个原结点的拷贝正是它的下一个结点，故 `cur->next->random = cur->random->next`；③ 拆分：把交错链拆回原链与新链，两链互不干扰。额外空间只有常数个指针。

```cpp
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }
        // ① 每个 原结点 后插入其拷贝：1 -> 1' -> 2 -> 2' -> ...
        for (Node* cur = head; cur != nullptr; ) {
            Node* copy = new Node(cur->val);
            copy->next = cur->next;
            cur->next = copy;
            cur = copy->next;  // 跳过拷贝，走到下一个原结点
        }
        // ② 借助相邻关系设置 random：cur 的拷贝的 random = cur->random 的拷贝
        for (Node* cur = head; cur != nullptr; cur = cur->next->next) {
            if (cur->random != nullptr) {
                cur->next->random = cur->random->next;
            }
        }
        // ③ 拆分交错链：原链还原，拷贝串成新链
        Node* newHead = head->next;
        for (Node* cur = head; cur != nullptr; cur = cur->next) {
            Node* copy = cur->next;          // 记下当前拷贝
            cur->next = copy->next;          // 原链跳过拷贝
            copy->next = (copy->next != nullptr) ? copy->next->next : nullptr;
        }
        return newHead;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`，三趟各扫一遍
- 💾 空间复杂度：`O(1)`（不算输出链表本身）

## ⚠️ 易错点

- 深拷贝要求新链的 `next` / `random` **一律指向新建结点**；直接写 `copy->random = cur->random` 会让新链指向原链结点，判题不通过。
- 哈希表法必须"先建完所有结点、再统一接线"：一遍边复制边接 `random` 时，`random` 可能指向尚未创建的后面结点。
- 原地法第二步设置 `random` 时，`cur->random` 本身可能为空，不判空就写 `cur->random->next` 会解引用空指针。
- 原地法拆链时三个动作顺序敏感：先记下 `copy`，再让原链跳过拷贝，最后让拷贝指向下一个拷贝（`copy->next->next`）；读写在 `cur->next` 被改写前后要格外小心，容易丢结点。

---

[← 返回目录](../../README.md)
