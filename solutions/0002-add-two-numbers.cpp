/**
 * @file    0002-add-two-numbers.cpp
 * @brief   2. 两数相加
 * @link    https://leetcode.cn/problems/add-two-numbers/
 *
 * 解法：模拟竖式加法，边遍历边建链
 * 思路：逆序存储即个位对齐，逐位求和并维护进位；短链按 0 参与，最后进位非 0 时补节点。
 * 时间复杂度：O(max(m, n))
 * 空间复杂度：O(1)（不计返回链表）
 */

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);        // 哑节点，结果头不确定时简化拼接
        ListNode* tail = &dummy;  // 已建结果链的尾
        int carry = 0;            // 进位
        ListNode *p1 = l1, *p2 = l2;
        while (p1 != nullptr || p2 != nullptr || carry != 0) {
            int sum = carry;
            if (p1 != nullptr) {  // 较短的链表按 0 参与
                sum += p1->val;
                p1 = p1->next;
            }
            if (p2 != nullptr) {
                sum += p2->val;
                p2 = p2->next;
            }
            carry = sum / 10;     // 新进位
            tail->next = new ListNode(sum % 10);  // 当前位
            tail = tail->next;
        }
        return dummy.next;
    }
};
