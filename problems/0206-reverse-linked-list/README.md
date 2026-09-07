# 206. 反转链表

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/reverse-linked-list/) ｜ [国际站](https://leetcode.com/problems/reverse-linked-list/)
>
> 🟢 简单 ｜ 标签：`链表` `递归`

## 📝 题目描述

给你单链表的头节点 `head`，请你**反转**该链表，并返回反转后的链表。

即把链表中所有节点的指向全部掉头：原链表的尾节点变成新链表的头节点，原头节点变成新链表的尾节点（其 `next` 指向 `nullptr`）。

**示例 1：**

```
输入：head = [1,2,3,4,5]
输出：[5,4,3,2,1]
解释：反转后链表变为 5 -> 4 -> 3 -> 2 -> 1。
```

**示例 2：**

```
输入：head = [1,2]
输出：[2,1]
```

**示例 3：**

```
输入：head = []
输出：[]
解释：空链表反转后仍为空。
```

**提示：**

- 链表中节点的数目范围是 `[0, 5000]`
- `-5000 <= Node.val <= 5000`

## 💡 题解

### 解法一：迭代（头插 / 三指针）

**思路**：用三个相邻的指针维护不变量：`prev` 指向**已经反转完成**的部分的头（初始为 `nullptr`），`curr` 指向**待处理**的第一个节点，`next` 在修改指针前暂存 `curr` 的后继。每一轮先把 `curr->next` 存进 `next`，再把 `curr->next` 反过来指向 `prev`，然后整体右移一步（`prev = curr`，`curr = next`）。循环结束时 `curr` 为 `nullptr`，`prev` 即新链表的头。

```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;   // 已反转部分的头
        ListNode* curr = head;      // 待反转部分的头
        while (curr != nullptr) {
            ListNode* next = curr->next;  // 暂存后继，防止断链
            curr->next = prev;            // 掉头，指向前驱
            prev = curr;                  // 已反转部分扩张一步
            curr = next;                  // 推进到下一个待处理节点
        }
        return prev;  // curr 为空时 prev 恰为新头
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(1)`

### 解法二：递归

**思路**：把问题拆成"反转除头节点外的剩余链表"与"把头节点接到尾部"两步。递归调用 `reverseList(head->next)` 得到剩余部分反转后的新头 `newHead`，此时原来的第二个节点 `head->next` 位于反转结果的尾部，只需令 `head->next->next = head` 把 `head` 接到末尾，再令 `head->next = nullptr` 封尾。递归触底条件：空链表或单节点链表直接返回自身。

```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        // 空链表或只剩一个节点，无需反转
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode* newHead = reverseList(head->next);  // 反转剩余部分
        head->next->next = head;  // 原第二个节点现在是尾，接回 head
        head->next = nullptr;     // head 成为新尾，封尾防止成环
        return newHead;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`（递归调用栈深度为 `n`）

### 解法三：迭代 dummy 头插法（推荐）

**思路**：与解法一等价的另一种迭代写法：借助一个哑节点 `dummy`，依次把原链表的每个节点**摘下来插到 `dummy` 之后**，即"头插法"。`next = curr->next` 保存后继，`curr->next = dummy->next` 把当前节点插到已收集部分的最前，`dummy->next = curr` 更新新头。所有节点处理完后 `dummy->next` 即答案。与三指针写法二选一即可，此写法思路可平移到"反转部分链表"等变形题。

```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode dummy(0);  // 哑节点，简化头部处理
        ListNode* curr = head;
        while (curr != nullptr) {
            ListNode* next = curr->next;   // 暂存后继
            curr->next = dummy.next;       // 当前节点插到结果链最前
            dummy.next = curr;
            curr = next;                   // 继续处理下一个
        }
        return dummy.next;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 修改 `curr->next` 之前必须先保存 `curr->next`（即 `next` 指针），否则后继节点丢失造成断链。
- 循环的返回值是 `prev`（或 `dummy.next`），不是 `head`——`head` 反转后已经变成尾节点。
- 递归解法中最后必须 `head->next = nullptr` 封尾，否则新链表尾部会指回倒数第二个节点形成环。
- 递归深度为链表长度，`n = 5000` 时栈深约 5000 层，通常可过但面试中迭代写法更稳妥。

---

[← 返回目录](../../README.md)
