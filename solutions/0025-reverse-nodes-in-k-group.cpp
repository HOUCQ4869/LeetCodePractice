/**
 * @file    0025-reverse-nodes-in-k-group.cpp
 * @brief   25. K 个一组翻转链表
 * @link    https://leetcode.cn/problems/reverse-nodes-in-k-group/
 *
 * 解法：迭代模拟（哑节点 + 组前驱）
 * 思路：groupPrev 指向当前组的前驱；每轮先探测是否凑够 k 个，够则头插翻转本组（prev 从下一组头起步保证衔接），原组头翻转变组尾后充当下一轮前驱。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode* groupPrev = &dummy;  // 当前组的前驱

        for (;;) {
            // 探测本组是否凑够 k 个结点
            ListNode* check = groupPrev;
            for (int i = 0; i < k; ++i) {
                check = check->next;
                if (check == nullptr) {
                    return dummy.next;  // 剩余不足 k 个，整体结束
                }
            }
            ListNode* groupHead = groupPrev->next;  // 原组头，翻转后成为组尾
            ListNode* nextGroup = check->next;      // 下一组的头
            // 头插法翻转本组：prev 从 nextGroup 起步，保证与下一组衔接
            ListNode* prev = nextGroup;
            ListNode* cur = groupHead;
            while (cur != nextGroup) {
                ListNode* nxt = cur->next;
                cur->next = prev;
                prev = cur;
                cur = nxt;
            }
            // 前驱接本组新头；原组头变为组尾，充当下一轮前驱
            groupPrev->next = prev;
            groupPrev = groupHead;
        }
    }
};
