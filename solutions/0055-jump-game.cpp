/**
 * @file    0055-jump-game.cpp
 * @brief   55. 跳跃游戏
 * @link    https://leetcode.cn/problems/jump-game/
 *
 * 解法：贪心——维护最远可达位置
 * 思路：边扫边维护 farthest = max(i + nums[i])，一旦下标越过 farthest 即不可达，farthest 到达末尾即成功。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

#include <vector>

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = (int)nums.size();
        int farthest = 0;  // 从 [0, i-1] 出发能到达的最远下标
        for (int i = 0; i < n; ++i) {
            if (i > farthest) return false;  // 当前位置已越过边界，不可达
            farthest = max(farthest, i + nums[i]);
            if (farthest >= n - 1) return true;
        }
        return true;  // n == 1 时起点即终点
    }
};
