# 121. 买卖股票的最佳时机

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/) ｜ [国际站](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)
>
> 🟢 简单 ｜ 标签：`贪心` `动态规划`

## 📝 题目描述

给定一个数组 `prices`，它的第 `i` 个元素 `prices[i]` 表示一支股票第 `i` 天的价格。

只能选择**某一天**买入并选择**之后的另一天**卖出（先买后卖，各一次），设计算法计算所能获得的最大利润。如果不能获得任何利润（价格单调不增），返回 `0`。

**示例 1：**

```
输入：prices = [7,1,5,3,6,4]
输出：5
解释：第 2 天（下标 1）买入，第 5 天（下标 4）卖出，利润 6 - 1 = 5。
     注意 7 - 1 = 6 不合法，因为买入必须发生在卖出之前。
```

**示例 2：**

```
输入：prices = [7,6,4,3,1]
输出：0
解释：价格持续下跌，不进行交易，利润为 0。
```

**提示：**

- `1 <= prices.length <= 10^5`
- `0 <= prices[i] <= 10^4`

## 💡 题解

### 解法一：暴力枚举

**思路**：枚举每一对满足 `i < j` 的买卖组合，取 `prices[j] - prices[i]` 的最大值。共 `O(n^2)` 对组合，`n = 10^5` 时会超时，仅用于理解题意。

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = (int)prices.size();
        int best = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                best = max(best, prices[j] - prices[i]);
            }
        }
        return best;
    }
};
```

- ⏱️ 时间复杂度：`O(n^2)`
- 💾 空间复杂度：`O(1)`

### 解法二：动态规划

**思路**：站在第 `i` 天结束时只有两种状态：**持有股票**（此前某天买入，含今天刚买）或**不持有**。设 `hold` 为持有状态下的最大收益（是负数或 0，表示买入成本），`cash` 为不持有状态的最大收益。转移：

- `hold = max(hold, -prices[i])`——要么延续之前持有，要么今天才买；
- `cash = max(cash, hold + prices[i])`——要么延续之前不持有，要么今天卖出。

初始 `hold = -prices[0]`、`cash = 0`，答案为 `cash`。这一状态机写法可以无缝推广到 122、123、188 等股票系列题。

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int hold = -prices[0];  // 持有股票时的最大收益
        int cash = 0;           // 不持有股票时的最大收益
        for (int i = 1; i < (int)prices.size(); ++i) {
            cash = max(cash, hold + prices[i]);       // 今天卖出
            hold = max(hold, -prices[i]);             // 今天买入
        }
        return cash;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(1)`

### 解法三：一次遍历维护历史最低价（推荐）

**思路**：最优卖出日固定时，最佳买入日一定是它**之前**价格最低的那天。于是一次遍历：记录到目前为止的最低价 `minPrice`，每到一天就用 `prices[i] - minPrice` 尝试更新答案，再用 `prices[i]` 更新 `minPrice`。等价于"在每一步做出局部最优选择"的贪心。

```cpp
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
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 买入必须在卖出**之前**，先更新 `best` 再更新 `minPrice` 的顺序不能反（否则可能"当天又买又卖"）。
- 无法获利时要返回 `0`，`best` 初值取 `0` 而不是最小整数。
- `minPrice` 应初始化为 `prices[0]`（或极大值），循环从下标 1 开始，避免越界或漏算。

---

[← 返回目录](../../README.md)
