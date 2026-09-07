/**
 * @file    0102-binary-tree-level-order-traversal.cpp
 * @brief   102. 二叉树的层序遍历
 * @link    https://leetcode.cn/problems/binary-tree-level-order-traversal/
 *
 * 解法：BFS 队列逐层处理
 * 思路：每轮处理一整层——先取定队列长度 sz（即本层节点数），出队访问并把非空孩子入队，
 *       下一轮处理新的一层，直至队列为空。
 * 时间复杂度：O(n)
 * 空间复杂度：O(w)（w 为最宽一层的节点数；不含输出数组）
 */

#include <queue>
#include <utility>
#include <vector>

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (root == nullptr) return res;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int sz = (int)q.size();  // 当前层的节点数（入队前取定）
            vector<int> level;
            level.reserve(sz);
            for (int i = 0; i < sz; ++i) {
                TreeNode* node = q.front();
                q.pop();
                level.push_back(node->val);  // 访问本层节点
                if (node->left != nullptr) q.push(node->left);
                if (node->right != nullptr) q.push(node->right);
            }
            res.push_back(move(level));  // 本层结果进入答案
        }
        return res;
    }
};
