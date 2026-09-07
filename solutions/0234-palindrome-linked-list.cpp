/**
 * @file    0234-palindrome-linked-list.cpp
 * @brief   234. 回文链表
 * @link    https://leetcode.cn/problems/palindrome-linked-list/
 *
 * 解法：快慢指针找中点 + 反转后半 + 逐对比较
 * 思路：慢指针停在前半段末尾，反转 slow 之后的后半段，再从两头逐对比较值；O(1) 额外空间。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

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
