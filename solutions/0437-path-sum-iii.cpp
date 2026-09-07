/**
 * @file    0437-path-sum-iii.cpp
 * @brief   437. 路径总和 III
 * @link    https://leetcode.cn/problems/path-sum-iii/
 *
 * 解法：前缀和 + 哈希表 + 回溯
 * 思路：根到节点前缀和之差即一段向下路径的和；DFS 维护当前链上「前缀和 -> 次数」
 *       的哈希表，查询 cur - target 的出现次数并累加，离开子树时回溯撤销登记。
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 */

#include <unordered_map>

class Solution {
    unordered_map<long long, int> cnt;  // 当前根到节点链上的 前缀和 -> 出现次数

    int dfs(TreeNode* node, long long cur, long long target) {
        if (!node) return 0;
        cur += node->val;   // 根到当前节点的前缀和
        int res = cnt.count(cur - target) ? cnt[cur - target] : 0;
        ++cnt[cur];                       // 登记后再进入子树
        res += dfs(node->left, cur, target);
        res += dfs(node->right, cur, target);
        --cnt[cur];                       // 回溯：撤销登记
        return res;
    }

public:
    int pathSum(TreeNode* root, int targetSum) {
        cnt.clear();
        cnt[0] = 1;  // 空路径：根之前的“空前缀”
        return dfs(root, 0, targetSum);
    }
};
