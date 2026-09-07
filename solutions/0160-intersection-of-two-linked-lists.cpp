/**
 * @file    0160-intersection-of-two-linked-lists.cpp
 * @brief   160. 相交链表
 * @link    https://leetcode.cn/problems/intersection-of-two-linked-lists/
 *
 * 解法：双指针两次遍历
 * 思路：pA 走完 A 转 B、pB 走完 B 转 A，两指针路程均为 a+b，会在相交起点相遇（不相交则同时为空）。
 * 时间复杂度：O(m + n)
 * 空间复杂度：O(1)
 */

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headA == nullptr || headB == nullptr) {
            return nullptr;
        }
        ListNode *pA = headA, *pB = headB;
        while (pA != pB) {  // 相遇（或同时为空）时退出
            // pA 走到 A 尾后切换到 B；仍在 A 中则后移一步
            pA = (pA == nullptr) ? headB : pA->next;
            pB = (pB == nullptr) ? headA : pB->next;
        }
        return pA;  // 相交则为目标节点；不相交则为 nullptr
    }
};
