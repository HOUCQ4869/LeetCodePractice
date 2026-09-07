/**
 * @file    0239-sliding-window-maximum.cpp
 * @brief   239. 滑动窗口最大值
 * @link    https://leetcode.cn/problems/sliding-window-maximum/
 *
 * 解法：单调队列
 * 思路：双端队列存下标并保持对应值单调递减；队头即窗口最大值，新元素入队前弹掉队尾所有不大于它的元素。
 * 时间复杂度：O(n)
 * 空间复杂度：O(k)
 */

#include <vector>
#include <deque>

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> ans;
        deque<int> dq;  // 存下标，对应值从队头到队尾单调递减
        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            if (!dq.empty() && dq.front() <= i - k) {
                dq.pop_front();  // 队头已滑出窗口
            }
            while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();  // 不大于新元素的旧元素不可能成为后续窗口的最大值
            }
            dq.push_back(i);
            if (i >= k - 1) {
                ans.push_back(nums[dq.front()]);
            }
        }
        return ans;
    }
};
