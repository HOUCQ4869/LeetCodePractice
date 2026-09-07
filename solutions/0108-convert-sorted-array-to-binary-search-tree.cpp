/**
 * @file    0108-convert-sorted-array-to-binary-search-tree.cpp
 * @brief   108. 将有序数组转换为二叉搜索树
 * @link    https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree/
 *
 * 解法：递归分治（传递下标区间）
 * 思路：有序数组取中点为根，左半段递归建左子树、右半段递归建右子树，中点同时保证 BST 性质与高度平衡；递归只传 [lo, hi) 下标，不拷贝数组。
 * 时间复杂度：O(n)
 * 空间复杂度：O(log n)
 */

#include <vector>

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return build(nums, 0, static_cast<int>(nums.size()));  // [0, n)
    }

private:
    TreeNode* build(vector<int>& nums, int lo, int hi) {
        if (lo >= hi) return nullptr;     // 空区间：无子树
        int mid = lo + (hi - lo) / 2;     // 中点作根，左右长度差不超过 1
        auto* root = new TreeNode(nums[mid]);
        root->left = build(nums, lo, mid);       // 严格小于根的左半段
        root->right = build(nums, mid + 1, hi);  // 大于根的右半段
        return root;
    }
};
