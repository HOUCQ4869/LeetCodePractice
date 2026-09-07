# 55. 跳跃游戏

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/jump-game/) ｜ [国际站](https://leetcode.com/problems/jump-game/)
>
> 🟡 中等 ｜ 标签：`贪心`

## 📝 题目描述

给定一个非负整数数组 `nums`，最初位于数组的**第一个下标**。数组中每个元素代表在该位置可以跳跃的**最大**长度（可以跳不超过该长度的任意步）。

判断是否能够到达最后一个下标。若能返回 `true`，否则返回 `false`。

**示例 1：**

```
输入：nums = [2,3,1,1,4]
输出：true
解释：先跳 1 步到下标 1，再跳 3 步到最后一个下标 4。
```

**示例 2：**

```
输入：nums = [3,2,1,0,4]
输出：false
解释：无论怎样跳，最多只能到达下标 3（值为 0，无法继续），到不了下标 4。
```

**提示：**

- `1 <= nums.length <= 3 * 10^4`
- `0 <= nums[i] <= 10^5`

## 💡 题解

### 解法一：动态规划

**思路**：设 `dp[i]` 表示下标 `i` 是否可达。初始 `dp[0] = true`；对每个可达的下标 `i`，它能跳到的区间 `[i + 1, i + nums[i]]` 内所有下标都标记为可达。答案即 `dp[n - 1]`。双重循环最坏 `O(n^2)`（`n` 达 `3 * 10^4` 时勉强可行但不优），用作理解与对照。

```cpp
#include <vector>

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = (int)nums.size();
        vector<bool> dp(n, false);
        dp[0] = true;
        for (int i = 0; i < n; ++i) {
            if (!dp[i]) continue;  // 不可达的位置无法继续扩散
            for (int j = i + 1; j <= min(n - 1, i + nums[i]); ++j) {
                dp[j] = true;
            }
        }
        return dp[n - 1];
    }
};
```

- ⏱️ 时间复杂度：`O(n^2)`（乘上最大跳跃长度，可视为 `O(n * maxJump)`）
- 💾 空间复杂度：`O(n)`

### 解法二：贪心——维护最远可达位置（推荐）

**思路**：不必关心"怎么跳"，只需关心"最远能到哪"。从左往右扫，用 `farthest` 维护从所有**已到达**下标出发能到达的最远位置：

- 若当前下标 `i > farthest`，说明 `i` 越过了能力边界，永远到不了，返回 `false`；
- 否则用 `i + nums[i]` 更新 `farthest`。

一旦 `farthest >= n - 1` 即可提前返回 `true`。正确性来自"可达区间连续"：若能到达位置 `x`，则所有小于 `x` 的位置也都可达（跳跃长度可任选），因此维护一个不断右扩的边界即可。

```cpp
#include <vector>

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = (int)nums.size();
        int farthest = 0;  // 从 [0, i-1] 出发能到达的最远下标
        for (int i = 0; i < n; ++i) {
            if (i > farthest) return false;   // 当前位置已越过边界，不可达
            farthest = max(farthest, i + nums[i]);
            if (farthest >= n - 1) return true;
        }
        return true;  // n == 1 时起点即终点
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 判断条件是 `i > farthest`（当前位置不可达）而不是 `i >= farthest`——`i == farthest` 时仍可从 `i` 继续起跳。
- `nums[i]` 是**最大**跳跃长度，可以少跳；不要理解成必须恰好跳 `nums[i]` 步。
- 下标为 `0` 的位置是"死点"：一旦 `farthest` 停在某个 0 前就会返回 `false`，注意别让边界判断漏掉这种情况。
- `n == 1` 时即使 `nums[0] == 0` 也应返回 `true`（起点即终点）。

---

[← 返回目录](../../README.md)
