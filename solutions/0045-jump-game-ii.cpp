/**
 * @file    0045-jump-game-ii.cpp
 * @brief   45. 跳跃游戏 II
 * @link    https://leetcode.cn/problems/jump-game-ii/
 *
 * 解法：贪心——分层跳跃（隐式 BFS）
 * 思路：维护当前跳的覆盖区间右端 curEnd 与累积最远 farthest，扫完一层必须再跳一步并进入下一层，层数即最少跳跃次数。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

#include <vector>

class Solution {
public:
    int jump(vector<int>& nums) {
        int n = (int)nums.size();
        int steps = 0;
        int curEnd = 0;    // 当前这一跳能到达的右边界
        int farthest = 0;  // [0, i] 出发能到达的最远位置
        for (int i = 0; i < n - 1; ++i) {
            farthest = max(farthest, i + nums[i]);
            if (i == curEnd) {  // 扫完当前层，必须再跳一步
                ++steps;
                curEnd = farthest;
                if (curEnd >= n - 1) break;
            }
        }
        return steps;
    }
};
