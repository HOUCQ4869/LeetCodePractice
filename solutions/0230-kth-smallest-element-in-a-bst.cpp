/**
 * @file    0230-kth-smallest-element-in-a-bst.cpp
 * @brief   230. 二叉搜索树中第 K 小的元素
 * @link    https://leetcode.cn/problems/kth-smallest-element-in-a-bst/
 *
 * 解法：迭代中序遍历（提前终止）
 * 思路：BST 中序遍历为升序，用显式栈迭代中序，每弹出一个节点计数减一，第 k 个弹出的节点即第 k 小，立即返回。
 * 时间复杂度：O(h + k)
 * 空间复杂度：O(h)
 */

#include <stack>

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> stk;
        TreeNode* cur = root;
        while (cur || !stk.empty()) {
            while (cur) {          // 一路向左压栈
                stk.push(cur);
                cur = cur->left;
            }
            cur = stk.top();       // 栈顶即当前未访问的最小节点
            stk.pop();
            if (--k == 0) {
                return cur->val;   // 第 k 个被访问的节点
            }
            cur = cur->right;      // 转向右子树
        }
        return -1;                 // 不会到达（题目保证 1 <= k <= n）
    }
};
