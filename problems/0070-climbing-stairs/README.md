# 70. 爬楼梯

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/climbing-stairs/) ｜ [国际站](https://leetcode.com/problems/climbing-stairs/)
>
> 🟢 简单 ｜ 标签：`动态规划`

## 📝 题目描述

假设你正在爬楼梯，需要 `n` 阶才能到达楼顶。每次可以爬 `1` 或 `2` 个台阶，问有多少种不同的方法可以爬到楼顶。

**示例 1：**

```
输入：n = 2
输出：2
解释：有 2 种方法——(1 阶 + 1 阶) 或 (2 阶)。
```

**示例 2：**

```
输入：n = 3
输出：3
解释：3 种方法——(1+1+1)、(1+2)、(2+1)。
```

**提示：**

- `1 <= n <= 45`

## 💡 题解

### 解法一：记忆化递归

**思路**：设 `f(n)` 为爬到第 `n` 阶的方法数。到达第 `n` 阶的最后一步只能从第 `n - 1` 阶（爬 1 阶）或第 `n - 2` 阶（爬 2 阶）走来，故 `f(n) = f(n - 1) + f(n - 2)`，边界 `f(1) = 1`、`f(2) = 2`。直接递归会重复计算子问题（指数级），用数组缓存已算出的结果即可降到线性。

```cpp
#include <vector>

class Solution {
public:
    int climbStairs(int n) {
        memo.assign(n + 1, 0);
        return dfs(n);
    }

private:
    vector<int> memo;

    int dfs(int n) {
        if (n <= 2) return n;  // f(1) = 1, f(2) = 2
        if (memo[n] != 0) return memo[n];
        return memo[n] = dfs(n - 1) + dfs(n - 2);
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`

### 解法二：动态规划（数组）

**思路**：把自顶向下的递归改写为自底向上的递推：从 `f(1)`、`f(2)` 出发逐步推出 `f(n)`。转移只与前一阶、前两阶有关。

```cpp
#include <vector>

class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) return n;
        vector<int> dp(n + 1);
        dp[1] = 1;
        dp[2] = 2;
        for (int i = 3; i <= n; ++i) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`

### 解法三：滚动变量（推荐）

**思路**：转移只依赖最近两个状态，用两个变量滚动替换即可省去整个数组。本质就是迭代计算斐波那契数列。

```cpp
class Solution {
public:
    int climbStairs(int n) {
        int prev = 1, curr = 1;  // f(0) = 1, f(1) = 1
        for (int i = 2; i <= n; ++i) {
            int next = prev + curr;
            prev = curr;
            curr = next;
        }
        return curr;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 边界：`n = 1` 时答案是 1 不是 0，用 `f(0) = 1, f(1) = 1` 起推滚动写法可避开特判。
- 不要写裸递归不加记忆化——`n = 45` 时会超时（约 2^45 次调用）。
- 本题就是斐波那契，但"方案数"含义下 `f(2) = 2`、`f(3) = 3`，与"第 n 项斐波那契数"错位一位，容易下标写偏。

---

[← 返回目录](../../README.md)
