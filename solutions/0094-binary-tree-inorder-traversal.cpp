/**
 * @file    0094-binary-tree-inorder-traversal.cpp
 * @brief   94. 二叉树的中序遍历
 * @link    https://leetcode.cn/problems/binary-tree-inorder-traversal/
 *
 * 解法：Morris 中序遍历
 * 思路：借空闲右指针建线索：有左子树时找到前驱（左子树最右节点）指回当前节点再进左子树；
 *       回到当前节点说明左子树访问完，拆线索、访问并转向右子树，实现 O(1) 空间。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

#include <vector>

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        TreeNode* cur = root;
        while (cur != nullptr) {
            if (cur->left != nullptr) {
                // 找中序前驱：左子树的最右节点
                TreeNode* pred = cur->left;
                while (pred->right != nullptr && pred->right != cur) {
                    pred = pred->right;
                }
                if (pred->right == nullptr) {
                    pred->right = cur;  // 建线索，方便之后回到 cur
                    cur = cur->left;
                } else {
                    pred->right = nullptr;  // 左子树已访问完，拆线索
                    res.push_back(cur->val);
                    cur = cur->right;
                }
            } else {
                res.push_back(cur->val);  // 无左子树，直接访问
                cur = cur->right;
            }
        }
        return res;
    }
};
