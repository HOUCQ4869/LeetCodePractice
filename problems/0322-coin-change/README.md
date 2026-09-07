# 322. 零钱兑换

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/coin-change/) ｜ [国际站](https://leetcode.com/problems/coin-change/)
>
> 🟡 中等 ｜ 标签：`动态规划` `广度优先搜索`

## 📝 题目描述

给定不同面额的硬币数组 `coins` 和一个总金额 `amount`。每种硬币的数量是**无限**的。计算凑成总金额所需的**最少**硬币个数。如果没有任何一种硬币组合能凑出总金额，返回 `-1`。可以认为每种硬币的数量是无限的。

**示例 1：**

```
输入：coins = [1, 2, 5], amount = 11
输出：3
解释：11 = 5 + 5 + 1，共使用 3 枚硬币。
```

**示例 2：**

```
输入：coins = [2], amount = 3
输出：-1
解释：只用面额 2 的硬币无法凑出 3。
```

**示例 3：**

```
输入：coins = [1], amount = 0
输出：0
```

**提示：**

- `1 <= coins.length <= 12`
- `1 <= coins[i] <= 2^31 - 1`
- `0 <= amount <= 10^4`
- 题目数据保证 `coins` 中的元素互不相同

## 💡 题解

### 解法一：记忆化搜索

**思路**：自顶向下思考——凑出金额 `x` 的最后一枚硬币必是某个 `c`，所以 `f(x) = min(f(x - c)) + 1`，边界 `f(0) = 0`，无法凑出（含 `x < 0`）记为"无穷"。递归加缓存即得答案，改写 `f` 调用为迭代就是解法二的 DP，两者本质相同。

```cpp
#include <vector>
#include <algorithm>
#include <climits>

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        memo.assign(amount + 1, -2);  // -2 表示未计算
        int res = dfs(coins, amount);
        return res == INT_MAX ? -1 : res;
    }

private:
    vector<int> memo;

    int dfs(vector<int>& coins, int x) {
        if (x == 0) return 0;
        if (x < 0) return INT_MAX;       // 非法状态
        if (memo[x] != -2) return memo[x];
        int best = INT_MAX;
        for (int c : coins) {
            int sub = dfs(coins, x - c);
            if (sub != INT_MAX) best = min(best, sub + 1);
        }
        return memo[x] = best;
    }
};
```

- ⏱️ 时间复杂度：`O(amount * n)`（`n` 为硬币种数）
- 💾 空间复杂度：`O(amount)`

### 解法二：动态规划——完全背包（推荐）

**思路**：把 `amount` 当作背包容量、硬币面额当作物品（可重复选取），求装满背包的最少物品数。设 `dp[i]` 为凑出金额 `i` 的最少硬币数：

- 初始 `dp[0] = 0`，其余设为"不可达"（用 `INT_MAX` 或 `amount + 1` 哨兵）；
- 转移：`dp[i] = min(dp[i - c] + 1)`，对所有满足 `c <= i` 的面额 `c`。

`dp[i - c]` 不可达时要跳过（否则 `INT_MAX + 1` 会溢出）。最终 `dp[amount]` 仍不可达则返回 `-1`。

```cpp
#include <vector>
#include <algorithm>
#include <climits>

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, INT_MAX);  // INT_MAX 表示不可达
        dp[0] = 0;
        for (int i = 1; i <= amount; ++i) {
            for (int c : coins) {
                if (c <= i && dp[i - c] != INT_MAX) {
                    dp[i] = min(dp[i], dp[i - c] + 1);
                }
            }
        }
        return dp[amount] == INT_MAX ? -1 : dp[amount];
    }
};
```

- ⏱️ 时间复杂度：`O(amount * n)`
- 💾 空间复杂度：`O(amount)`

## ⚠️ 易错点

- 判断 `dp[i - c] != INT_MAX` 不可省略：`INT_MAX + 1` 溢出为负数会污染结果；也可用 `amount + 1` 作哨兵规避。
- 硬币面额可能大于 `amount`，转移前必须检查 `c <= i`。
- 无法凑出要返回 `-1` 而不是 0 或极大值；`amount = 0` 应返回 0。
- 这是**完全**背包（每种硬币无限），与 416 题 01 背包的区别在于物品可重复使用，本题按金额维遍历时天然支持重复选取。

---

[← 返回目录](../../README.md)
