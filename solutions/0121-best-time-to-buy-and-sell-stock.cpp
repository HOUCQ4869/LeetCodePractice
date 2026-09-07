/**
 * @file    0121-best-time-to-buy-and-sell-stock.cpp
 * @brief   121. 买卖股票的最佳时机
 * @link    https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/
 *
 * 解法：一次遍历维护历史最低价
 * 思路：固定卖出日时最优买入日是其之前的最低价，边扫边维护 minPrice 并尝试用当天价减它更新答案。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

#include <vector>
#include <algorithm>

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minPrice = prices[0];  // 到目前为止的最低买入价
        int best = 0;
        for (int i = 1; i < (int)prices.size(); ++i) {
            best = max(best, prices[i] - minPrice);  // 今天卖出的最好结果
            minPrice = min(minPrice, prices[i]);     // 更新历史最低价
        }
        return best;
    }
};
