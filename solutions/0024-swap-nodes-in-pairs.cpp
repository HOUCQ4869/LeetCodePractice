/**
 * @file    0024-swap-nodes-in-pairs.cpp
 * @brief   24. 两两交换链表中的节点
 * @link    https://leetcode.cn/problems/swap-nodes-in-pairs/
 *
 * 解法：迭代 + 哑节点
 * 思路：prev 指向待交换一对结点的前驱，三条指针赋值完成交换；交换后的末尾结点成为下一轮的前驱。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

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
