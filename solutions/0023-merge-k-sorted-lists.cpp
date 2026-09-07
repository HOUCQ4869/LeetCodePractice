/**
 * @file    0023-merge-k-sorted-lists.cpp
 * @brief   23. 合并 K 个升序链表
 * @link    https://leetcode.cn/problems/merge-k-sorted-lists/
 *
 * 解法：分治合并
 * 思路：mergeRange 把 k 条链对半分治、各自合并成一条，再用 21 题的两两有序链表合并拼回；每条链只参与 log k 次合并。
 * 时间复杂度：O(N log k)，N 为总结点数
 * 空间复杂度：O(log k)（递归调用栈）
 */

#include <vector>

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) {
            return nullptr;
        }
        return mergeRange(lists, 0, static_cast<int>(lists.size()) - 1);
    }

private:
    // 合并 lists[lo..hi] 范围内的所有链表
    ListNode* mergeRange(vector<ListNode*>& lists, int lo, int hi) {
        if (lo == hi) {
            return lists[lo];  // 只剩一条（可能是空链）
        }
        int mid = lo + (hi - lo) / 2;
        return mergeTwo(mergeRange(lists, lo, mid), mergeRange(lists, mid + 1, hi));
    }

    ListNode* mergeTwo(ListNode* a, ListNode* b) {
        ListNode dummy(0);
        ListNode* tail = &dummy;
        while (a != nullptr && b != nullptr) {
            if (a->val <= b->val) {  // <= 保持稳定
                tail->next = a;
                a = a->next;
            } else {
                tail->next = b;
                b = b->next;
            }
            tail = tail->next;
        }
        tail->next = (a != nullptr) ? a : b;
        return dummy.next;
    }
};
