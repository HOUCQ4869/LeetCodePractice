# 198. 打家劫舍

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/house-robber/) ｜ [国际站](https://leetcode.com/problems/house-robber/)
>
> 🟡 中等 ｜ 标签：`动态规划`

## 📝 题目描述

你是一个专业的小偷，计划偷窃沿街的房屋。每间房内藏有一定的现金，影响你偷窃的唯一制约因素是：**相邻的两间房屋不能同时被偷**——它们装有相互连通的防盗系统，一旦两间相邻的房屋同一晚被闯入，系统会自动报警。

给定一个代表每间房屋存放金额的非负整数数组 `nums`，计算**不触动警报**的情况下，一夜之内能够偷窃到的最高金额。

**示例 1：**

```
输入：nums = [1,2,3,1]
输出：4
解释：偷窃第 1 间（金额 1）和第 3 间（金额 1），不相邻，总金额 4。
```

**示例 2：**

```
输入：nums = [2,7,9,3,1]
输出：12
解释：偷第 1、3、5 间（2 + 9 + 1 = 12）是最优方案。
```

**提示：**

- `1 <= nums.length <= 100`
- `0 <= nums[i] <= 400`

## 💡 题解

### 解法一：动态规划（数组）

**思路**：设 `dp[i]` 为考虑前 `i + 1` 间房屋（下标 `0..i`）能偷到的最高金额。对第 `i` 间房只有两种选择：

- **偷**：前一夜必须不偷第 `i - 1` 间，金额为 `dp[i - 2] + nums[i]`；
- **不偷**：金额为 `dp[i - 1]`。

两者取较大值：`dp[i] = max(dp[i - 1], dp[i - 2] + nums[i])`。边界 `dp[0] = nums[0]`、`dp[1] = max(nums[0], nums[1])`。

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = (int)nums.size();
        if (n == 1) return nums[0];
        vector<int> dp(n);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < n; ++i) {
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }
        return dp[n - 1];
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`

### 解法二：滚动变量（推荐）

**思路**：转移只依赖前两个状态，用 `prev`（对应 `dp[i - 2]`）和 `curr`（对应 `dp[i - 1]`）滚动推进，空间降到 `O(1)`。统一从"前两间收益均为 0"的虚拟边界出发，可省去对 `n == 1` 的特判。

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int rob(vector<int>& nums) {
        int prev = 0, curr = 0;  // dp[i-2], dp[i-1]
        for (int x : nums) {
            int next = max(curr, prev + x);  // 不偷 i 或 偷 i
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

- "偷 `i`"的收益是 `dp[i - 2] + nums[i]`，不要误加成 `dp[i - 1] + nums[i]`（相邻不能同偷）。
- `n == 1` 时数组解法直接访问 `dp[1]` 会越界，需特判或采用滚动写法。
- 金额非负但不保证"偷越多间越优"，最优解可能跳过金额小的连续多间房。
- 进阶版 213 题是**环形**排列，需要拆成两条链分别 DP 后取较大值，不能直接套用本解法。

---

[← 返回目录](../../README.md)
