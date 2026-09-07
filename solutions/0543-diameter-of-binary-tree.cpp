/**
 * @file    0543-diameter-of-binary-tree.cpp
 * @brief   543. 二叉树的直径
 * @link    https://leetcode.cn/problems/diameter-of-binary-tree/
 *
 * 解法：后序 DFS 返回「深度 + 直径」二元组
 * 思路：递归返回 {子树最大深度（节点数）, 子树内最大直径（边数）}；
 *       直径在左子树直径、右子树直径、横跨当前节点的 左深度+右深度 三者中取最大。
 * 时间复杂度：O(n)
 * 空间复杂度：O(h)（递归栈，h 为树高）
 */

#include <algorithm>
#include <utility>

class Solution {
    // 返回 {子树最大深度（节点数）, 子树内最大直径（边数）}
    pair<int, int> dfs(TreeNode* node) {
        if (node == nullptr) return {0, 0};
        auto [ld, lans] = dfs(node->left);
        auto [rd, rans] = dfs(node->right);
        int depth = max(ld, rd) + 1;
        int best = max({lans, rans, ld + rd});  // 左、右、横跨 node 三种情况
        return {depth, best};
    }

public:
    int diameterOfBinaryTree(TreeNode* root) {
        return dfs(root).second;
    }
};
