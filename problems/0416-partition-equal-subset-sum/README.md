# 416. 分割等和子集

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/partition-equal-subset-sum/) ｜ [国际站](https://leetcode.com/problems/partition-equal-subset-sum/)
>
> 🟡 中等 ｜ 标签：`动态规划` `背包`

## 📝 题目描述

给定一个**只包含正整数**的非空数组 `nums`，判断是否能把数组分割成两个子集，使得两个子集的元素和**相等**。

每个元素必须且只能被分进其中一个子集（即选取一个子集，剩下的元素自动构成另一个子集）。

**示例 1：**

```
输入：nums = [1,5,11,5]
输出：true
解释：可以分割成 [1, 5, 5] 和 [11]，两者之和都是 11。
```

**示例 2：**

```
输入：nums = [1,2,3,5]
输出：false
解释：数组总和为 11（奇数），不可能分割成两个和相等的子集。
```

**提示：**

- `1 <= nums.length <= 200`
- `1 <= nums[i] <= 100`

## 💡 题解

### 解法一：记忆化搜索

**思路**：设数组总和为 `sum`，若 `sum` 为奇数直接返回 `false`。否则问题变成：能否从数组中选出一些数，使它们的和恰好等于 `target = sum / 2`。定义 `dfs(i, rest)` 表示从下标 `i` 往后、还差 `rest` 未凑够时能否成功。每个元素有"选"与"不选"两个分支，用二维数组缓存结果。判掉 `sum` 为奇数与某元素大于 `target` 的情形可以大幅剪枝。

```cpp
#include <vector>
#include <numeric>

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 == 1) return false;
        int target = sum / 2;
        memo.assign(nums.size(), vector<char>(target + 1, -1));
        return dfs(nums, 0, target);
    }

private:
    vector<vector<char>> memo;  // -1 未计算，0 假，1 真

    bool dfs(vector<int>& nums, int i, int rest) {
        if (rest == 0) return true;         // 恰好凑够
        if (i == (int)nums.size() || rest < 0) return false;
        if (memo[i][rest] != -1) return memo[i][rest];
        // 不选 nums[i] 或选 nums[i]
        bool ok = dfs(nums, i + 1, rest) || dfs(nums, i + 1, rest - nums[i]);
        return memo[i][rest] = ok;
    }
};
```

- ⏱️ 时间复杂度：`O(n * target)`
- 💾 空间复杂度：`O(n * target)`

### 解法二：一维 01 背包（推荐）

**思路**：问题等价于 01 背包"能否恰好装满容量为 `target` 的背包"。设 `dp[j]` 表示能否选出若干数凑出和 `j`，初始仅 `dp[0] = true`。转移方程：

```
dp[j] = dp[j] || dp[j - nums[i]]
```

关键在于**外层遍历物品、内层容量从大到小**：`dp[j - nums[i]]` 必须是"还没考虑第 `i` 个数"的旧值，倒序才能保证每个数只被选一次（这正是 01 背包与完全背包在实现上的唯一差别）。若倒序误写成正序，同一个数会被重复选取，例如 `[1, 2, 5]` 会误判能凑出 4。最后返回 `dp[target]`。

```cpp
#include <vector>
#include <numeric>

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 == 1) return false;
        int target = sum / 2;

        vector<char> dp(target + 1, 0);  // char 当布尔用
        dp[0] = true;
        for (int x : nums) {
            for (int j = target; j >= x; --j) {  // 倒序：保证每数只用一次
                if (dp[j - x]) dp[j] = 1;
            }
        }
        return dp[target];
    }
};
```

- ⏱️ 时间复杂度：`O(n * target)`
- 💾 空间复杂度：`O(target)`

## ⚠️ 易错点

- 总和为**奇数**必须提前返回 `false`，否则 `target` 取整后判断的就不是"等和"问题。
- 内层循环必须**倒序**（`j` 从 `target` 到 `nums[i]`），正序会让同一元素被重复使用。
- 内层下界是 `j >= x`（即 `j - x >= 0`），写成 `j >= 0` 会越界。
- `dp` 大小是 `target + 1`，且 `dp[0] = true`（空集凑出 0）别漏初始化。
- 元素全是**正整数**是本题前提，若含负数或 0，"奇偶剪枝"与背包转移都要重新设计。

---

[← 返回目录](../../README.md)
