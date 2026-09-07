# 234. 回文链表

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/palindrome-linked-list/) ｜ [国际站](https://leetcode.com/problems/palindrome-linked-list/)
>
> 🟢 简单 ｜ 标签：`链表` `双指针`

## 📝 题目描述

给你单链表的头节点 `head`，请你判断该链表是否为**回文链表**。如果是，返回 `true`；否则返回 `false`。

回文链表指链表节点序列从头读到尾与从尾读到头**完全相同**，例如 `1 -> 2 -> 2 -> 1` 是回文链表，而 `1 -> 2` 不是。

**进阶**：你能否用 `O(n)` 时间复杂度和 `O(1)` 空间复杂度解决此题？

**示例 1：**

```
输入：head = [1,2,2,1]
输出：true
解释：序列正读、反读均为 1,2,2,1，是回文。
```

**示例 2：**

```
输入：head = [1,2]
输出：false
解释：正读为 1,2，反读为 2,1，不相同。
```

**提示：**

- 链表中节点数目在范围 `[1, 10^5]` 内
- `0 <= Node.val <= 9`

## 💡 题解

### 解法一：复制到数组 + 双指针

**思路**：单链表不支持从尾往前走，最直接的办法是先遍历一次链表，把所有值复制到动态数组中，再用经典的左右双指针向中间夹逼比较。判断的是**值序列**是否回文，与节点地址无关。

```cpp
#include <vector>

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        vector<int> vals;
        for (auto p = head; p != nullptr; p = p->next) {
            vals.push_back(p->val);  // 链表值复制到数组
        }
        int left = 0, right = static_cast<int>(vals.size()) - 1;
        while (left < right) {
            if (vals[left] != vals[right]) {
                return false;  // 有一对不对称即非回文
            }
            ++left;
            --right;
        }
        return true;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`

### 解法二：快慢指针找中点 + 反转后半 + 逐对比较（推荐）

**思路**：为满足进阶的 `O(1)` 空间要求，分三步走：
1. **找中点**：快指针每次走两步、慢指针每次走一步，快指针到尾时慢指针停在中间（节点数为偶数时停在**前半段的最后一个节点**，配合 `slow->next` 取后半段，奇偶统一）；
2. **反转后半**：用迭代法反转 `slow->next` 开始的后半段链表；
3. **逐对比较**：从原头 `head` 与后半段新头 `p2` 同步前进比较值，`p2` 先到尾（奇数长度时正中那个节点不参与比较），全部相等即回文。
比较阶段不改前半段指向，后半段虽被反转但不影响判断结果。

```cpp
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (head->next == nullptr) {
            return true;  // 单节点必为回文
        }

        // 1. 快慢指针找中点，slow 停在前半段最后一个节点
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // 2. 反转后半段
        ListNode* prev = nullptr;
        ListNode* curr = slow->next;
        while (curr != nullptr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        // 3. 前后半段逐对比较
        ListNode* p1 = head;
        ListNode* p2 = prev;  // 后半段反转后的头
        while (p2 != nullptr) {  // 后半段更短，p2 先到尾
            if (p1->val != p2->val) {
                return false;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        return true;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 快慢指针的循环条件是 `fast->next != nullptr && fast->next->next != nullptr`，写错会导致偶数长度时慢指针停偏，前后半段划分不均。
- 奇数长度时正中间节点属于哪一半都不影响正确性，但比较循环必须以**后半段指针**（更短的一侧）为结束条件，否则会访问空指针。
- 反转后半段时忘记暂存 `curr->next` 会断链；这是链表反转题最常见的错误。
- 若题目环境要求"不能修改输入链表"，`O(1)` 解法在比较完成后应把后半段反转回去再返回结果。

---

[← 返回目录](../../README.md)
