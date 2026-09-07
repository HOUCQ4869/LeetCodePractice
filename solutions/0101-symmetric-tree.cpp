/**
 * @file    0101-symmetric-tree.cpp
 * @brief   101. 对称二叉树
 * @link    https://leetcode.cn/problems/symmetric-tree/
 *
 * 解法：递归
 * 思路：转化为判断两棵子树互为镜像——值相等且 a 的左与 b 的右、a 的右与 b 的左分别镜像；
 *       入口传 mirror(root, root) 统一处理边界。
 * 时间复杂度：O(n)
 * 空间复杂度：O(h)（递归栈，h 为树高）
 */

class Solution {
    // 判断 a、b 两棵子树是否互为镜像
    bool mirror(TreeNode* a, TreeNode* b) {
        if (a == nullptr && b == nullptr) return true;   // 同时为空
        if (a == nullptr || b == nullptr) return false;  // 一空一非空
        if (a->val != b->val) return false;              // 值不同
        return mirror(a->left, b->right) && mirror(a->right, b->left);
    }

public:
    bool isSymmetric(TreeNode* root) {
        return mirror(root, root);
    }
};
