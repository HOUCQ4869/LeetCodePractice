/**
 * @file    0098-validate-binary-search-tree.cpp
 * @brief   98. 验证二叉搜索树
 * @link    https://leetcode.cn/problems/validate-binary-search-tree/
 *
 * 解法：中序遍历（迭代栈）
 * 思路：BST 的中序遍历严格递增；用显式栈迭代中序遍历，prev 记录上一个访问的节点，一旦出现 cur->val <= prev->val 即非法，可立即返回。
 * 时间复杂度：O(n)
 * 空间复杂度：O(h)
 */

#include <stack>

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        stack<TreeNode*> stk;
        TreeNode* prev = nullptr;
        TreeNode* cur = root;
        while (cur || !stk.empty()) {
            while (cur) {              // 一路向左，依次压栈
                stk.push(cur);
                cur = cur->left;
            }
            cur = stk.top();           // 栈顶即中序当前节点
            stk.pop();
            if (prev && cur->val <= prev->val) {
                return false;          // 中序序列必须严格递增
            }
            prev = cur;
            cur = cur->right;          // 转向右子树
        }
        return true;
    }
};
