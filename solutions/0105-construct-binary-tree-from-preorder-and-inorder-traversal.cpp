/**
 * @file    0105-construct-binary-tree-from-preorder-and-inorder-traversal.cpp
 * @brief   105. 从前序与中序遍历序列构造二叉树
 * @link    https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
 *
 * 解法：哈希表定位 + 前序游标（递归分治）
 * 思路：前序首元素为根，哈希表 O(1) 定位根在中序中的位置并划分左右子树区间；
 *       全局游标按「根-左-右」顺序依次消费前序，先递归左子树再递归右子树。
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 */

#include <unordered_map>
#include <vector>

class Solution {
    unordered_map<int, int> idx;  // 值 -> 中序下标
    int preIdx = 0;               // 前序中下一个待消费的位置（即下一个根）

    // 用 inorder[il..ir] 区间递归建树，根从 preorder[preIdx] 依次取
    TreeNode* build(const vector<int>& preorder, int il, int ir) {
        if (il > ir) return nullptr;
        int rootVal = preorder[preIdx++];       // 消费一个根
        int k = idx[rootVal];                   // O(1) 定位根在中序中的位置
        auto root = new TreeNode(rootVal);
        root->left = build(preorder, il, k - 1);    // 必须先建左子树
        root->right = build(preorder, k + 1, ir);   // 再建右子树
        return root;
    }

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        idx.clear();
        for (int i = 0; i < (int)inorder.size(); ++i) idx[inorder[i]] = i;
        preIdx = 0;
        return build(preorder, 0, (int)inorder.size() - 1);
    }
};
