/**
 * @file    0226-invert-binary-tree.cpp
 * @brief   226. 翻转二叉树
 * @link    https://leetcode.cn/problems/invert-binary-tree/
 *
 * 解法：递归
 * 思路：先递归翻转左右子树，再交换这两棵已翻转好的子树（后序），空节点直接返回。
 * 时间复杂度：O(n)
 * 空间复杂度：O(h)（递归栈，h 为树高）
 */

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) return nullptr;
        TreeNode* left = invertTree(root->left);    // 递归翻转左子树
        TreeNode* right = invertTree(root->right);  // 递归翻转右子树
        root->left = right;  // 交换两棵已翻转好的子树
        root->right = left;
        return root;
    }
};
