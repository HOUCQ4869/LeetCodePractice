/**
 * @file    0124-binary-tree-maximum-path-sum.cpp
 * @brief   124. 二叉树中的最大路径和
 * @link    https://leetcode.cn/problems/binary-tree-maximum-path-sum/
 *
 * 解法：负贡献归零（后序 DFS）
 * 思路：gain(x) 返回以 x 为一端、向下延伸的最大链和（空节点为 0，负贡献与 0 取 max 舍弃）；
 *       拐点处用 val + l + r 更新全局答案，向上只返回 val + max(l, r)。
 * 时间复杂度：O(n)
 * 空间复杂度：O(h)，最坏 O(n)
 */

#include <algorithm>
#include <climits>

class Solution {
    int ans = INT_MIN;

    // 返回以 node 为一端、只向下延伸的最大链和（至少含 node，可为负）
    int gain(TreeNode* node) {
        if (!node) return 0;
        int l = max(gain(node->left), 0);    // 左链负贡献直接舍弃
        int r = max(gain(node->right), 0);   // 右链负贡献直接舍弃
        ans = max(ans, node->val + l + r);   // 以 node 为拐点的最优路径
        return node->val + max(l, r);        // 向上只能延伸到一边
    }

public:
    int maxPathSum(TreeNode* root) {
        gain(root);
        return ans;
    }
};
