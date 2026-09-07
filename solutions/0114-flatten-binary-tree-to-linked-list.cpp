/**
 * @file    0114-flatten-binary-tree-to-linked-list.cpp
 * @brief   114. 二叉树展开为链表
 * @link    https://leetcode.cn/problems/flatten-binary-tree-to-linked-list/
 *
 * 解法：迭代寻找前驱（O(1) 空间）
 * 思路：对每个节点，若有左子树则找到左子树最右节点（前序前驱），把原右子树接到前驱之后，再把左子树整体搬到右侧并置空 left；然后右移处理下一个节点。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

class Solution {
public:
    void flatten(TreeNode* root) {
        TreeNode* cur = root;
        while (cur) {
            if (cur->left) {
                TreeNode* pred = cur->left;              // 进入左子树
                while (pred->right) pred = pred->right;  // 左子树最右节点 = 前序前驱
                pred->right = cur->right;                // 原右子树接到前驱之后
                cur->right = cur->left;                  // 左子树整体上移为右链
                cur->left = nullptr;
            }
            cur = cur->right;  // 移动到链表的下一个节点
        }
    }
};
