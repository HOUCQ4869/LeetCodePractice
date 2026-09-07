# 21. 合并两个有序链表

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/merge-two-sorted-lists/) ｜ [国际站](https://leetcode.com/problems/merge-two-sorted-lists/)
>
> 🟢 简单 ｜ 标签：`链表` `递归`

## 📝 题目描述

将两个**升序**链表合并为一个新的**升序**链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的（即复用原节点，而不是新建节点）。

**示例 1：**

```
输入：l1 = [1,2,4], l2 = [1,3,4]
输出：[1,1,2,3,4,4]
解释：两条链表都是升序，交错取较小者拼接即可。
```

**示例 2：**

```
输入：l1 = [], l2 = []
输出：[]
```

**示例 3：**

```
输入：l1 = [], l2 = [0]
输出：[0]
解释：一条链表为空时，结果就是另一条链表。
```

**提示：**

- 两个链表的节点数目范围是 `[0, 50]`
- `-100 <= Node.val <= 100`
- `l1` 和 `l2` 均按**非递减顺序**排列

## 💡 题解

### 解法一：递归

**思路**：合并两条有序链表的最小子问题很好回答：只要有一条为空，结果就是另一条。两条都非空时，**头节点较小者**应当作为合并结果的头，它的 `next` 指向"去掉这个头之后，与另一条链表继续合并"的结果——这正是原问题的缩小版，递归调用即可。函数返回"这两段链表合并后的头指针"，父层把它接到已确定的节点后面。

```cpp
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        // 某条链表为空，合并结果就是另一条
        if (list1 == nullptr) {
            return list2;
        }
        if (list2 == nullptr) {
            return list1;
        }
        // 较小者作头，其余部分递归合并接到其后
        if (list1->val <= list2->val) {
            list1->next = mergeTwoLists(list1->next, list2);
            return list1;
        } else {
            list2->next = mergeTwoLists(list1, list2->next);
            return list2;
        }
    }
};
```

- ⏱️ 时间复杂度：`O(m + n)`
- 💾 空间复杂度：`O(m + n)`（递归调用栈深度）

### 解法二：迭代 + 哑节点（推荐）

**思路**：维护一个**尾指针** `tail` 指向已合并部分的最后一个节点，用哑节点 `dummy` 统一处理"结果头不确定"的边界。每轮比较两条链表当前头节点的值，把较小者摘下接到 `tail` 后面并前移 `tail` 与该链表的头指针；直至某条链表耗尽，把另一条剩余部分整体接到 `tail` 后即可。迭代写法常数空间，且是归并排序链表版的核心部件。

```cpp
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy(0);        // 哑节点，简化头部边界
        ListNode* tail = &dummy;  // 已合并部分的尾
        ListNode *p1 = list1, *p2 = list2;
        while (p1 != nullptr && p2 != nullptr) {
            if (p1->val <= p2->val) {  // 取较小者（相等优先取 p1，保持稳定）
                tail->next = p1;
                p1 = p1->next;
            } else {
                tail->next = p2;
                p2 = p2->next;
            }
            tail = tail->next;
        }
        // 剩下的一条链表整体拼接（可能为空，同样适用）
        tail->next = (p1 != nullptr) ? p1 : p2;
        return dummy.next;
    }
};
```

- ⏱️ 时间复杂度：`O(m + n)`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 忘记前移 `tail`（`tail = tail->next`）会把所有节点接到同一位置，只剩一个节点。
- 循环结束后必须把**未耗尽那条链表的剩余部分**接上，逐节点继续比较虽然也对但多余。
- 返回值应是 `dummy.next` 而不是 `dummy` 本身，哑节点只是占位。
- 相等时优先取 `p1`（`<=`）可保持合并的**稳定性**，对归并排序等扩展场景重要。

---

[← 返回目录](../../README.md)
