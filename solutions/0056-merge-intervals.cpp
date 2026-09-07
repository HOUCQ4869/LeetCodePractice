/**
 * @file    0056-merge-intervals.cpp
 * @brief   56. 合并区间
 * @link    https://leetcode.cn/problems/merge-intervals/
 *
 * 解法：排序 + 原地合并
 * 思路：按左端点排序后，用写指针 k 指向已合并的最后一个区间，逐个比较扩展或后移，最后 resize 截断。
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(1)（不计返回值与排序栈）
 */

#include <algorithm>
#include <vector>

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        int k = 0;  // 写指针：已合并区间的最后位置
        for (int i = 1; i < (int)intervals.size(); ++i) {
            if (intervals[i][0] <= intervals[k][1]) {
                intervals[k][1] = max(intervals[k][1], intervals[i][1]);  // 重叠：扩展右端点
            } else {
                intervals[++k] = intervals[i];  // 无重叠：写入下一段
            }
        }
        intervals.resize(k + 1);
        return intervals;
    }
};
