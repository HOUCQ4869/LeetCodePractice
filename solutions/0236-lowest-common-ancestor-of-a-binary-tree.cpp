/**
 * @file    0236-lowest-common-ancestor-of-a-binary-tree.cpp
 * @brief   236. 二叉树的最近公共祖先
 * @link    https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/
 *
 * 解法：后序 DFS 一次遍历
 * 思路：递归返回当前子树中找到的 p / q / LCA；节点命中 p 或 q 即返回，
 *       左右返回值均非空说明 p、q 分居两侧，当前节点即 LCA，否则上传非空一侧。
 * 时间复杂度：O(n)
 * 空间复杂度：O(h)，最坏 O(n)
 */

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || root == p || root == q) return root;  // 空节点或命中目标
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        if (left && right) return root;   // p、q 分居两侧：当前节点即 LCA
        return left ? left : right;       // 都在同一侧：上传非空的那个
    }
};
