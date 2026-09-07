/**
 * @file    0104-maximum-depth-of-binary-tree.cpp
 * @brief   104. 二叉树的最大深度
 * @link    https://leetcode.cn/problems/maximum-depth-of-binary-tree/
 *
 * 解法：自底向上的 DFS（后序求高度）
 * 思路：树的最大深度 = max(左子树深度, 右子树深度) + 1，空节点深度为 0，后序递归合并即得。
 * 时间复杂度：O(n)
 * 空间复杂度：O(h)（递归栈，h 为树高）
 */

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};
