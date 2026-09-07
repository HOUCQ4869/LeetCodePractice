/**
 * @file    0169-majority-element.cpp
 * @brief   169. 多数元素
 * @link    https://leetcode.cn/problems/majority-element/
 *
 * 解法：摩尔投票
 * 思路：维护候选人与票数，同元素加票、异元素减票，归零换人；多数元素超过半数必存活到最后。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

#include <vector>

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int candidate = 0;  // 候选人
        int count = 0;      // 候选人票数
        for (int x : nums) {
            if (count == 0) {
                candidate = x;  // 票数耗尽，更换候选人
            }
            count += (x == candidate) ? 1 : -1;  // 同阵营 +1，异阵营对拼 -1
        }
        return candidate;
    }
};
