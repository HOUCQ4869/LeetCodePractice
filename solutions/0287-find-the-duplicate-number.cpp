/**
 * @file    0287-find-the-duplicate-number.cpp
 * @brief   287. 寻找重复数
 * @link    https://leetcode.cn/problems/find-the-duplicate-number/
 *
 * 解法：快慢指针判环
 * 思路：视 i -> nums[i] 为链表，重复值被两个下标指向而形成环；Floyd 判圈找环入口，入口编号即重复数。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

#include <vector>

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        // 第一阶段：快慢指针在环内相遇
        int slow = 0, fast = 0;
        do {
            slow = nums[slow];        // 慢指针走一步
            fast = nums[nums[fast]];  // 快指针走两步
        } while (slow != fast);
        // 第二阶段：同速前进找环入口
        slow = 0;
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;  // 相遇点的下标恰为重复数（环入口编号即重复值）
    }
};
