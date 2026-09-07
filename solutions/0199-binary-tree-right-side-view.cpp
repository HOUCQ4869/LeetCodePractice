/**
 * @file    0199-binary-tree-right-side-view.cpp
 * @brief   199. 二叉树的右视图
 * @link    https://leetcode.cn/problems/binary-tree-right-side-view/
 *
 * 解法：DFS 根-右-左
 * 思路：按「根-右-左」先右后左地深搜，某深度第一个被访问到的节点即该层右视图所见；用 res.size() 隐式记录已覆盖的层数，相等时入列。
 * 时间复杂度：O(n)
 * 空间复杂度：O(h)
 */

#include <vector>

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        dfs(root, 0, res);
        return res;
    }

private:
    void dfs(TreeNode* node, int depth, vector<int>& res) {
        if (!node) return;
        if (depth == static_cast<int>(res.size())) {  // 该深度首个被访问的节点
            res.push_back(node->val);
        }
        dfs(node->right, depth + 1, res);  // 先走右侧
        dfs(node->left, depth + 1, res);   // 右侧走完再走左侧
    }
};
