# 279. 完全平方数

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/perfect-squares/) ｜ [国际站](https://leetcode.com/problems/perfect-squares/)
>
> 🟡 中等 ｜ 标签：`动态规划` `广度优先搜索`

## 📝 题目描述

给定一个正整数 `n`，求最少需要多少个**完全平方数**（如 `1, 4, 9, 16, ...`，即 `k * k` 形式的数）的和恰好等于 `n`。

同一个完全平方数可以被重复使用多次。

**示例 1：**

```
输入：n = 12
输出：3
解释：12 = 4 + 4 + 4，用到 3 个完全平方数。
```

**示例 2：**

```
输入：n = 13
输出：2
解释：13 = 4 + 9，用到 2 个完全平方数。
```

**提示：**

- `1 <= n <= 10^4`

## 💡 题解

### 解法一：动态规划（完全背包）

**思路**：把 `1, 4, 9, ...`（所有不超过 `n` 的平方数）看作"硬币面额"，每个可无限次使用，问题就是求凑出金额 `n` 的最少硬币数——即完全背包版"零钱兑换"。设 `dp[i]` 为凑出 `i` 的最少平方数个数，则 `dp[i] = min(dp[i - j * j]) + 1`，其中 `j * j <= i`。

```cpp
#include <vector>
#include <algorithm>
#include <climits>

class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j * j <= i; ++j) {
                dp[i] = min(dp[i], dp[i - j * j] + 1);
            }
        }
        return dp[n];
    }
};
```

- ⏱️ 时间复杂度：`O(n * sqrt(n))`
- 💾 空间复杂度：`O(n)`

### 解法二：广度优先搜索

**思路**：把每个 `0..n` 的数值看作节点，从 `i` 减去任意一个平方数 `j * j` 就是一条边，问题变成求从 `n` 走到 `0` 的**最短路**——边权全为 1，用 BFS 即可，第一次到达 `0` 的层数就是答案。为避免同一数值重复入队，用布尔数组标记访问过的状态。

```cpp
#include <vector>
#include <queue>

class Solution {
public:
    int numSquares(int n) {
        vector<bool> visited(n + 1, false);
        queue<pair<int, int>> q;  // (当前数值, 已用平方数个数)
        q.emplace(n, 0);
        visited[n] = true;
        while (!q.empty()) {
            auto [cur, step] = q.front();
            q.pop();
            if (cur == 0) return step;
            for (int j = 1; j * j <= cur; ++j) {
                int next = cur - j * j;
                if (!visited[next]) {
                    visited[next] = true;
                    q.emplace(next, step + 1);
                }
            }
        }
        return -1;  // 理论上不会到达
    }
};
```

- ⏱️ 时间复杂度：`O(n * sqrt(n))`
- 💾 空间复杂度：`O(n)`

### 解法三：数学——拉格朗日四平方定理（推荐）

**思路**：**拉格朗日四平方定理**保证任何正整数都能表示为至多 4 个完全平方数之和，因此答案只会是 1、2、3 或 4。利用两条判定规则可以逐一排除：

1. **答案为 4** 当且仅当 `n` 形如 `4^a * (8b + 7)`（勒让德三平方定理的否定形式）；
2. **答案为 1** 当且仅当 `n` 本身是完全平方数；
3. **答案为 2** 当且仅当存在 `a` 使 `n - a^2` 是完全平方数（枚举 `a <= sqrt(n)` 即可）；
4. 其余情况答案必为 **3**。

```cpp
#include <cmath>

class Solution {
public:
    int numSquares(int n) {
        // 判断 x 是否为完全平方数
        auto isSquare = [](int x) {
            int r = (int)sqrt((double)x);
            return r * r == x;
        };

        // 规则 1：形如 4^a * (8b + 7) 时答案为 4
        int m = n;
        while (m % 4 == 0) m /= 4;
        if (m % 8 == 7) return 4;

        // 规则 2：n 本身是完全平方数，答案为 1
        if (isSquare(n)) return 1;

        // 规则 3：能拆成两个平方数之和，答案为 2
        for (int a = 1; (long long)a * a <= n; ++a) {
            if (isSquare(n - a * a)) return 2;
        }

        // 其余情况答案为 3
        return 3;
    }
};
```

- ⏱️ 时间复杂度：`O(sqrt(n))`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- DP 中 `j * j` 可能超出 `int` 上界（`j` 较大时），循环条件写成 `(long long)j * j <= n` 或 `j <= n / j` 更稳妥。
- BFS 必须标记访问过的数值，否则同一状态被反复入队，复杂度爆炸。
- 判 `4^a * (8b + 7)` 时要**先把因子 4 除干净**再模 8，顺序颠倒会误判。
- 浮点 `sqrt` 有精度风险，比较前可对 `r` 做 `±1` 微调，或用 `r * r == x` 严格验证。
- 边界 `n = 1` 的答案是 1（`1 = 1^2`），数学解法的判定顺序要先查 4 再查 1、2，别漏。

---

[← 返回目录](../../README.md)
