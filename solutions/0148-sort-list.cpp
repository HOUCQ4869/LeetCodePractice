/**
 * @file    0148-sort-list.cpp
 * @brief   148. 排序链表
 * @link    https://leetcode.cn/problems/sort-list/
 *
 * 解法：自底向上归并排序
 * 思路：从长度 1 的有序段起，每轮 cut 截出两段长至多 sub 的子链，mergeAppend 合并尾接，sub 逐轮翻倍，log n 轮后整链有序。
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(1)
 */

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        int n = 0;
        for (ListNode* cur = head; cur != nullptr; cur = cur->next) {
            ++n;  // 链表长度
        }
        ListNode dummy(0);
        dummy.next = head;
        // sub 为本轮有序段的长度，每轮翻倍
        for (int sub = 1; sub < n; sub <<= 1) {
            ListNode* tail = &dummy;  // 已合并部分的尾
            ListNode* cur = dummy.next;
            while (cur != nullptr) {
                ListNode* l1 = cur;           // 第一段
                ListNode* l2 = cut(l1, sub);  // 截出第二段（可能不足 sub 或为空）
                cur = cut(l2, sub);           // 本轮剩余部分
                tail = mergeAppend(tail, l1, l2);
            }
        }
        return dummy.next;
    }

private:
    // 从 from 截出前 n 个结点（不足则全部）作为一段，返回剩余部分的头
    ListNode* cut(ListNode* from, int n) {
        ListNode* cur = from;
        for (int i = 1; i < n && cur != nullptr; ++i) {
            cur = cur->next;
        }
        if (cur == nullptr) {
            return nullptr;  // 剩余不足 n 个，全给这一段
        }
        ListNode* rest = cur->next;
        cur->next = nullptr;  // 断开
        return rest;
    }

    // 把两段有序链 l1、l2 合并接到 tail 之后，返回合并后的尾
    ListNode* mergeAppend(ListNode* tail, ListNode* l1, ListNode* l2) {
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val <= l2->val) {  // <= 保持稳定
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        tail->next = (l1 != nullptr) ? l1 : l2;
        while (tail->next != nullptr) {  // 走到本段末尾
            tail = tail->next;
        }
        return tail;
    }
};
