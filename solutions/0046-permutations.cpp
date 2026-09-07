/**
 * @file    0046-permutations.cpp
 * @brief   46. 全排列
 * @link    https://leetcode.cn/problems/permutations/
 *
 * 解法：回溯（原地交换）
 * 思路：确定第 depth 个位置时，把 [depth, n) 内每个候选轮流换到 depth，
 *      递归处理 depth + 1 后再换回。无需 used 数组与路径数组，
 *      到达叶子时 nums 本身就是一个完整排列，拷贝进答案即可。
 * 时间复杂度：O(n × n!)，排列共 n! 个，每个拷贝 O(n)
 * 空间复杂度：O(n)，递归栈深度（不计输出）
 */

#include <utility>
#include <vector>

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        backtrack(nums, 0, ans);
        return ans;
    }

private:
    // [0, depth) 已确定，[depth, n) 为剩余候选
    void backtrack(vector<int>& nums, int depth, vector<vector<int>>& ans) {
        if (depth == static_cast<int>(nums.size())) {
            ans.push_back(nums);  // 此时 nums 本身就是一份完整排列
            return;
        }
        for (int i = depth; i < static_cast<int>(nums.size()); ++i) {
            swap(nums[depth], nums[i]);  // 把 nums[i] 换到当前位置
            backtrack(nums, depth + 1, ans);
            swap(nums[depth], nums[i]);  // 回溯：换回原位
        }
    }
};
