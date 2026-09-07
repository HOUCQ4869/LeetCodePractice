# 45. 跳跃游戏 II

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/jump-game-ii/) ｜ [国际站](https://leetcode.com/problems/jump-game-ii/)
>
> 🟡 中等 ｜ 标签：`贪心`

## 📝 题目描述

给定一个非负整数数组 `nums`，最初位于数组的**第一个下标**。数组中每个元素代表在该位置可以跳跃的**最大**长度。

你的目标是使用**最少**的跳跃次数到达数组的最后一个下标。题目保证测试用例构造的结果**总是可以到达**最后一个下标。

**示例 1：**

```
输入：nums = [2,3,1,1,4]
输出：2
解释：先跳到下标 1（跳 1 步），再从下标 1 跳 3 步到最后一个下标，共 2 步。
```

**示例 2：**

```
输入：nums = [2,3,0,1,4]
输出：2
```

**提示：**

- `1 <= nums.length <= 10^4`
- `0 <= nums[i] <= 1000`
- 题目保证总是可以到达 `nums[n - 1]`

## 💡 题解

### 解法一：动态规划

**思路**：设 `dp[i]` 为到达下标 `i` 的最少跳跃次数。转移时枚举 `i` 的所有前置可达下标 `j`（`j + nums[j] >= i` 且 `j < i`），取最小值加一。双重循环 `O(n^2)`，在本题 `n <= 10^4` 的规模下能过，但不是最优。

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int jump(vector<int>& nums) {
        int n = (int)nums.size();
        const int INF = 1e9;
        vector<int> dp(n, INF);
        dp[0] = 0;
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (j + nums[j] >= i) {
                    dp[i] = min(dp[i], dp[j] + 1);
                }
            }
        }
        return dp[n - 1];
    }
};
```

- ⏱️ 时间复杂度：`O(n^2)`
- 💾 空间复杂度：`O(n)`

### 解法二：贪心——分层跳跃（隐式 BFS）（推荐）

**思路**：把问题想象成 BFS 的分层：第 `steps` 跳能覆盖的下标恰好构成一段连续区间 `[curBegin, curEnd]`。扫描这段区间时，不断计算从中出发能到达的最远位置 `farthest`；当 `i` 走到当前层右端点 `curEnd` 时，说明这一层耗尽，必须再跳一次进入下一层，新区间为 `(curEnd, farthest]`。由于题目保证可达，走到 `n - 1` 时的层数即最少跳跃次数。每一步都选择能延伸最远的落点，这正是贪心最优性的来源。

```cpp
#include <vector>

class Solution {
public:
    int jump(vector<int>& nums) {
        int n = (int)nums.size();
        int steps = 0;
        int curEnd = 0;      // 当前这一跳能到达的右边界
        int farthest = 0;    // [0, i] 出发能到达的最远位置
        for (int i = 0; i < n - 1; ++i) {
            farthest = max(farthest, i + nums[i]);
            if (i == curEnd) {        // 扫完当前层，必须再跳一步
                ++steps;
                curEnd = farthest;
                if (curEnd >= n - 1) break;
            }
        }
        return steps;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 循环条件是 `i < n - 1` 而非 `i < n`：到达末尾后无需再跳，若扫到 `n - 1` 且 `i == curEnd` 会多计一步。
- `farthest` 要在判断 `i == curEnd` **之前**更新，否则下一层的边界会少算当前层的贡献。
- `n == 1` 时答案为 `0`，代码中循环体不执行、直接返回 `steps = 0`，注意别把初始化写错。
- 别把"能到达的最远位置"与"当前层的右端点"混为一谈：前者是累积最大值，后者在层耗尽时才刷新。

---

[← 返回目录](../../README.md)
