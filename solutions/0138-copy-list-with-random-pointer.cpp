/**
 * @file    0138-copy-list-with-random-pointer.cpp
 * @brief   138. 随机链表的复制
 * @link    https://leetcode.cn/problems/copy-list-with-random-pointer/
 *
 * 解法：原地拼接与拆分
 * 思路：每个原结点后插入其拷贝形成交错链，利用相邻关系 cur->next->random = cur->random->next 接好 random，最后拆回两条链。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }
        // ① 每个 原结点 后插入其拷贝：1 -> 1' -> 2 -> 2' -> ...
        for (Node* cur = head; cur != nullptr; ) {
            Node* copy = new Node(cur->val);
            copy->next = cur->next;
            cur->next = copy;
            cur = copy->next;  // 跳过拷贝，走到下一个原结点
        }
        // ② 借助相邻关系设置 random：cur 的拷贝的 random = cur->random 的拷贝
        for (Node* cur = head; cur != nullptr; cur = cur->next->next) {
            if (cur->random != nullptr) {
                cur->next->random = cur->random->next;
            }
        }
        // ③ 拆分交错链：原链还原，拷贝串成新链
        Node* newHead = head->next;
        for (Node* cur = head; cur != nullptr; cur = cur->next) {
            Node* copy = cur->next;          // 记下当前拷贝
            cur->next = copy->next;          // 原链跳过拷贝
            copy->next = (copy->next != nullptr) ? copy->next->next : nullptr;
        }
        return newHead;
    }
};
