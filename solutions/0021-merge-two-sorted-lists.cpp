/**
 * @file    0021-merge-two-sorted-lists.cpp
 * @brief   21. 合并两个有序链表
 * @link    https://leetcode.cn/problems/merge-two-sorted-lists/
 *
 * 解法：迭代 + 哑节点
 * 思路：tail 指向已合并部分末尾，每轮摘下两链表中较小的头接上，剩余一条整体拼接；返回 dummy.next。
 * 时间复杂度：O(m + n)
 * 空间复杂度：O(1)
 */

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
