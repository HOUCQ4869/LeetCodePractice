# 24. 两两交换链表中的节点

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/swap-nodes-in-pairs/) ｜ [国际站](https://leetcode.com/problems/swap-nodes-in-pairs/)
>
> 🟡 中等 ｜ 标签：`链表` `递归`

## 📝 题目描述

给定一个链表，**两两交换其中相邻的结点**，并返回交换后链表的头结点。

- 必须通过改变结点间的指针来完成交换，**不能只修改结点内部的值**；
- 链表中的结点个数为奇数时，最后一个结点落单，保持不动；
- 空链表或只有一个结点时无需任何操作。

**示例 1：**

```
输入：head = [1,2,3,4]
输出：[2,1,4,3]
解释：(1,2) 交换为 (2,1)，(3,4) 交换为 (4,3)。
```

**示例 2：**

```
输入：head = []
输出：[]
解释：空链表，直接返回。
```

**示例 3：**

```
输入：head = [1]
输出：[1]
解释：单个结点无法配对，保持原样。
```

**提示：**

- 链表中结点的数目范围是 `[0, 100]`
- `0 <= Node.val <= 100`

## 💡 题解

### 解法一：递归

**思路**：把链表看作"最前面两个结点 + 余下部分"。最小子问题很明确：不足两个结点（空或单结点）时无需交换，直接返回。否则记前两个结点为 `head` 和 `head->next`：递归处理 `head->next->next` 之后的链表得到已交换的剩余部分，让 `head` 接上它；再让第二个结点反过来指向 `head`，完成本组交换。函数返回本段交换后的新头，恰好是原来的第二个结点。

```cpp
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        // 不足两个结点，无需交换
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode* newHead = head->next;         // 本组交换后的新头
        head->next = swapPairs(newHead->next);  // 原头接上后面已处理的部分
        newHead->next = head;                   // 新头指向原头
        return newHead;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`，每个结点只被访问一次
- 💾 空间复杂度：`O(n)`（递归调用栈深度约为 n/2）

### 解法二：迭代 + 哑节点（推荐）

**思路**：用 `prev` 指向**待交换那一对结点的前驱**，哑节点保证第一对也有前驱。每轮检查 `prev` 后面确实有两个结点，取出 `first`、`second`，只需三次指针赋值即可完成交换：`first` 越过 `second` 指向后继、`second` 回指 `first`、`prev` 改指 `second`。交换后 `first` 成为这一对的末尾，正好作为下一轮的 `prev`。常数空间，且是后面"K 个一组翻转"取 `k = 2` 的特例，思想可以推广。

```cpp
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode* prev = &dummy;  // 指向待交换一对结点的前驱
        while (prev->next != nullptr && prev->next->next != nullptr) {
            ListNode* first = prev->next;
            ListNode* second = first->next;
            // 交换：prev -> second -> first -> (后续)
            first->next = second->next;
            second->next = first;
            prev->next = second;
            prev = first;  // first 交换后成为这一对的末尾，作为下一轮的前驱
        }
        return dummy.next;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 题目明确要求真实交换结点，只交换两个结点的 `val` 虽能通过判题，但违背题意、也学不到指针操作。
- 循环条件必须**同时**检查 `prev->next` 与 `prev->next->next`，否则链表长为奇数时会对 `nullptr` 解引用。
- 三条赋值语句看似顺序无关（`first`、`second` 已存入局部变量），但漏写任何一条都会断链或成环，写完后建议在纸上走一遍 `1 -> 2 -> 3 -> 4`。
- 下一轮的前驱是**交换后的末尾结点**（即原 `first`）；若误写为 `prev = second` 会向前回退，造成死循环。

---

[← 返回目录](../../README.md)
