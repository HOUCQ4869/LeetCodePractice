/**
 * @file    0206-reverse-linked-list.cpp
 * @brief   206. 反转链表
 * @link    https://leetcode.cn/problems/reverse-linked-list/
 *
 * 解法：迭代（三指针）
 * 思路：prev 维护已反转部分的头，每轮暂存后继、把 curr 掉头指向 prev，再整体右移；结束时 prev 即新头。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

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
