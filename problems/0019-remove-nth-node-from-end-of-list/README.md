# 19. 删除链表的倒数第 N 个结点

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/remove-nth-node-from-end-of-list/) ｜ [国际站](https://leetcode.com/problems/remove-nth-node-from-end-of-list/)
>
> 🟡 中等 ｜ 标签：`链表` `双指针`

## 📝 题目描述

给定一个链表的头结点 `head`，删除链表的**倒数第 `n` 个结点**，并返回新的头结点。题目保证 `n` 不超过链表长度，即待删结点一定存在。

**进阶**：你能只使用一趟扫描实现吗？

**示例 1：**

```
输入：head = [1,2,3,4,5], n = 2
输出：[1,2,3,5]
解释：链表中倒数第 2 个结点是 4，删除后链表变为 1 -> 2 -> 3 -> 5。
```

**示例 2：**

```
输入：head = [1], n = 1
输出：[]
解释：唯一的结点被删除，链表为空。
```

**示例 3：**

```
输入：head = [1,2], n = 1
输出：[1]
解释：删除尾结点 2，只剩 1。
```

**提示：**

- 链表中结点的数目为 `sz`，`1 <= sz <= 30`
- `0 <= Node.val <= 100`
- `1 <= n <= sz`

## 💡 题解

### 解法一：两次遍历（先求长度）

**思路**：倒数第 `n` 个结点就是正数第 `len - n + 1` 个结点（`len` 为链表长度）。第一趟扫描统计出 `len`，第二趟从头走 `len - n` 步，恰好停在待删结点的**前驱**上，把它的 `next` 跳过待删结点即可。引入哑节点 `dummy` 指向头结点，这样"删除头结点"（`n == len`）与普通情形完全统一，无需特判。

```cpp
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // 第一趟：统计链表长度
        int len = 0;
        for (ListNode* cur = head; cur != nullptr; cur = cur->next) {
            ++len;
        }
        // 倒数第 n 个 = 正数第 len - n + 1 个，其前驱是正数第 len - n 个
        ListNode dummy(0);
        dummy.next = head;
        ListNode* prev = &dummy;
        for (int i = 0; i < len - n; ++i) {
            prev = prev->next;
        }
        ListNode* removed = prev->next;  // 待删结点
        prev->next = removed->next;      // 跳过待删结点
        delete removed;                  // 释放结点（LeetCode 上可省略）
        return dummy.next;
    }
};
```

- ⏱️ 时间复杂度：`O(L)`，`L` 为链表长度（两趟合计仍线性）
- 💾 空间复杂度：`O(1)`

### 解法二：快慢双指针，一趟扫描（推荐）

**思路**：既然要找"倒数第 `n` 个的前驱"，就让两个指针保持固定距离一起走。`fast` 从哑节点出发先走 `n + 1` 步，此时 `fast` 与 `slow`（仍在哑节点）相距 `n + 1`；随后两者同步前进，直到 `fast` 越过表尾变为 `nullptr`。由于间距恒为 `n + 1`，`slow` 停下的位置距离表尾 `n + 1`，正是待删结点的前驱。整条链只扫一趟，满足进阶要求。

```cpp
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode *fast = &dummy, *slow = &dummy;
        for (int i = 0; i <= n; ++i) {  // fast 先走 n + 1 步，与 slow 拉开 n + 1 的间距
            fast = fast->next;
        }
        while (fast != nullptr) {  // 同步推进，结束时 slow 停在待删结点的前驱
            fast = fast->next;
            slow = slow->next;
        }
        ListNode* removed = slow->next;  // 待删结点
        slow->next = removed->next;      // 摘链
        delete removed;                  // 释放结点（LeetCode 上可省略）
        return dummy.next;
    }
};
```

- ⏱️ 时间复杂度：`O(L)`，一趟扫描
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 删除头结点（`n` 等于链表长度）时若无哑节点需要单独特判；使用哑节点后所有情形统一，这是链表删除类题目的通用技巧。
- 快指针应从哑节点先走 **`n + 1`** 步而非 `n` 步：目标是让慢指针最终停在待删结点的**前驱**，差一步都会让慢指针落在待删结点本身而无法摘链。
- 两个指针都必须**从哑节点出发**；若从 `head` 出发再走 `n + 1` 步，间距就多算了一个结点。
- 单结点链表删除后返回空链表，靠 `dummy.next`（此时为 `nullptr`）自然得到正确结果，不要习惯性地返回 `head`。

---

[← 返回目录](../../README.md)
