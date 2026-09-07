# 148. 排序链表

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/sort-list/) ｜ [国际站](https://leetcode.com/problems/sort-list/)
>
> 🟡 中等 ｜ 标签：`链表` `归并排序`

## 📝 题目描述

给定链表的头结点 `head`，请将其按**升序**排列并返回排序后的链表。

**进阶**：可以在 `O(n log n)` 时间复杂度和常数级空间复杂度下，对链表进行排序吗？

**示例 1：**

```
输入：head = [4,2,1,3]
输出：[1,2,3,4]
```

**示例 2：**

```
输入：head = [-1,5,3,4,0]
输出：[-1,0,3,4,5]
```

**示例 3：**

```
输入：head = []
输出：[]
```

**提示：**

- 链表中结点的数目在范围 `[0, 5 * 10^4]`
- `-10^5 <= Node.val <= 10^5`

## 💡 题解

### 解法一：借助数组排序

**思路**：链表不支持随机访问，快排类的分区操作很难施展；最直观的做法是把所有 `val` 倒进数组，用 `std::sort` 排好后按序**写回**各结点——结点结构一动不动，只换值。代码量最小，复杂度也达标，但完全绕开了链表操作，面试中只能算"能过"，不能算"会"。

```cpp
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        vector<int> vals;
        for (ListNode* cur = head; cur != nullptr; cur = cur->next) {
            vals.push_back(cur->val);  // 收集所有值
        }
        sort(vals.begin(), vals.end());
        int i = 0;
        for (ListNode* cur = head; cur != nullptr; cur = cur->next) {
            cur->val = vals[i++];  // 按序写回
        }
        return head;
    }
};
```

- ⏱️ 时间复杂度：`O(n log n)`
- 💾 空间复杂度：`O(n)`（数组）

### 解法二：自顶向下归并排序（递归）

**思路**：链表天然适合归并：**快慢指针**找中点把链表断成两半（`slow` 停在前半段最后一个结点），两半分别递归排序，再用"合并两个有序链表"（21 题）拼回。递归每层把问题规模减半，共 `log n` 层，每层合并合计 `O(n)`。注意 `fast` 要从 `head->next` 起步，否则两结点的链会分不出非空的两半。

```cpp
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        // 空链或单结点天然有序
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        // 快慢指针找中点：slow 停在前半段最后一个结点
        ListNode *slow = head, *fast = head->next;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode* right = slow->next;
        slow->next = nullptr;  // 断成两条链
        return merge(sortList(head), sortList(right));
    }

private:
    // 合并两个有序链表（同 21 题）
    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val <= l2->val) {  // <= 保持稳定
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        tail->next = (l1 != nullptr) ? l1 : l2;
        return dummy.next;
    }
};
```

- ⏱️ 时间复杂度：`O(n log n)`
- 💾 空间复杂度：`O(log n)`（递归调用栈）

### 解法三：自底向上归并排序（推荐）

**思路**：把递归展开成循环，从长度为 1 的有序段开始：每轮用 `cut` 从当前位置截出两段长度至多为 `sub` 的子链，`mergeAppend` 把它们合并接到已排序部分后面，一段扫完 `sub` 翻倍进入下一轮。`log n` 轮后整条链有序。全程只改指针、只用常数个辅助变量，是唯一同时满足时间与空间两项进阶要求的解法。`mergeAppend` 在合并后一路走到段尾，方便下一对段继续尾接。

```cpp
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        int n = 0;
        for (ListNode* cur = head; cur != nullptr; cur = cur->next) {
            ++n;  // 链表长度
        }
        ListNode dummy(0);
        dummy.next = head;
        // sub 为本轮有序段的长度，每轮翻倍
        for (int sub = 1; sub < n; sub <<= 1) {
            ListNode* tail = &dummy;  // 已合并部分的尾
            ListNode* cur = dummy.next;
            while (cur != nullptr) {
                ListNode* l1 = cur;           // 第一段
                ListNode* l2 = cut(l1, sub);  // 截出第二段（可能不足 sub 或为空）
                cur = cut(l2, sub);           // 本轮剩余部分
                tail = mergeAppend(tail, l1, l2);
            }
        }
        return dummy.next;
    }

private:
    // 从 from 截出前 n 个结点（不足则全部）作为一段，返回剩余部分的头
    ListNode* cut(ListNode* from, int n) {
        ListNode* cur = from;
        for (int i = 1; i < n && cur != nullptr; ++i) {
            cur = cur->next;
        }
        if (cur == nullptr) {
            return nullptr;  // 剩余不足 n 个，全给这一段
        }
        ListNode* rest = cur->next;
        cur->next = nullptr;  // 断开
        return rest;
    }

    // 把两段有序链 l1、l2 合并接到 tail 之后，返回合并后的尾
    ListNode* mergeAppend(ListNode* tail, ListNode* l1, ListNode* l2) {
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val <= l2->val) {  // <= 保持稳定
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        tail->next = (l1 != nullptr) ? l1 : l2;
        while (tail->next != nullptr) {  // 走到本段末尾
            tail = tail->next;
        }
        return tail;
    }
};
```

- ⏱️ 时间复杂度：`O(n log n)`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 递归版找中点时 `fast` 必须从 `head->next` 出发：从 `head` 出发的话，两个结点的链会分成"整条 + 空"，无限递归直至栈溢出。
- 递归版忘写 `slow->next = nullptr` 断链，"两半"其实仍是一条链，排序结果错乱。
- 自底向上版第二段可能不足 `sub` 甚至为空（`cut` 返回 `nullptr`），`mergeAppend` 与截段逻辑都必须能处理空链。
- 截段后一定要把段尾的 `next` 置空再参与合并，否则 `mergeAppend` 里"整体拼接剩余部分"会把本轮还没处理的结点也提前接上。
- 合并时用 `<=` 而非 `<`：相等时优先取前一段，保持排序稳定性（对判题无影响，但是好习惯）。

---

[← 返回目录](../../README.md)
