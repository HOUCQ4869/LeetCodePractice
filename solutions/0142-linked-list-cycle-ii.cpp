/**
 * @file    0142-linked-list-cycle-ii.cpp
 * @brief   142. 环形链表 II
 * @link    https://leetcode.cn/problems/linked-list-cycle-ii/
 *
 * 解法：Floyd 快慢指针 + 数学推导
 * 思路：快慢指针在环内相遇后，一指针回头、两指针同速前进，再次相遇处即入环点（由 a = (k-1)(b+c) + c 保证）。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        // 第一阶段：快慢指针判环并找到相遇点
        ListNode *slow = head;
        ListNode *fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;        // 慢走 1 步
            fast = fast->next->next;  // 快走 2 步
            if (slow == fast) {       // 有环，在环内相遇
                // 第二阶段：一个指针回头，同速前进找入环点
                ListNode *p = head;
                while (p != slow) {   // 再次相遇处即入环点
                    p = p->next;
                    slow = slow->next;
                }
                return p;
            }
        }
        return nullptr;  // fast 到达 nullptr，无环
    }
};
