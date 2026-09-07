/**
 * @file    0039-combination-sum.cpp
 * @brief   39. 组合总和
 * @link    https://leetcode.cn/problems/combination-sum/
 *
 * 解法：回溯（排序 + 剪枝）
 * 思路：先排序；从 start 起枚举候选数，剩余目标减去该数后递归，递归仍传 i
 *      （同一个数可重复选），传 start 保证组合之间不重复。
 *      排序后一旦 candidates[i] > remain 即 break，其后更大的数整体剪掉。
 * 时间复杂度：O(n^(t/m))，n 为候选数、t 为 target、m 为最小候选值（搜索树规模上界）
 * 空间复杂度：O(t/m)，递归栈与 path 的最大深度
 */

#include <algorithm>
#include <vector>

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());  // 排序是剪枝的前提
        vector<vector<int>> ans;
        vector<int> path;
        backtrack(candidates, 0, target, path, ans);
        return ans;
    }

private:
    void backtrack(const vector<int>& candidates, int start, int remain,
                   vector<int>& path, vector<vector<int>>& ans) {
        if (remain == 0) {  // 恰好凑出目标，收集并返回
            ans.push_back(path);
            return;
        }
        for (int i = start; i < static_cast<int>(candidates.size()); ++i) {
            if (candidates[i] > remain) break;  // 已排序，其后更大，整体剪枝
            path.push_back(candidates[i]);
            backtrack(candidates, i, remain - candidates[i], path, ans);  // 传 i：可重复选
            path.pop_back();
        }
    }
};
