/**
 * @file    0141-linked-list-cycle.cpp
 * @brief   141. 环形链表
 * @link    https://leetcode.cn/problems/linked-list-cycle/
 *
 * 解法：Floyd 快慢指针
 * 思路：慢指针走 1 步、快指针走 2 步；无环时快指针先到 nullptr，有环时快指针必在环内追上慢指针。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *slow = head;  // 每次走 1 步
        ListNode *fast = head;  // 每次走 2 步
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;        // 慢走一步
            fast = fast->next->next;  // 快走两步
            if (slow == fast) {       // 快追上慢，说明有环
                return true;
            }
        }
        return false;  // fast 到达 nullptr，链表有尾，无环
    }
};
