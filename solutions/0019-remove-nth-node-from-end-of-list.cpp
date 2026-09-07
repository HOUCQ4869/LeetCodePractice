/**
 * @file    0019-remove-nth-node-from-end-of-list.cpp
 * @brief   19. 删除链表的倒数第 N 个结点
 * @link    https://leetcode.cn/problems/remove-nth-node-from-end-of-list/
 *
 * 解法：快慢双指针，一趟扫描
 * 思路：哑节点出发，fast 先走 n + 1 步拉开间距，再与 slow 同步推进；fast 为空时 slow 恰停在待删结点的前驱，摘链即可。
 * 时间复杂度：O(L)，L 为链表长度
 * 空间复杂度：O(1)
 */

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
