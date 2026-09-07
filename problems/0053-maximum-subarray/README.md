# 53. 最大子数组和

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/maximum-subarray/) ｜ [国际站](https://leetcode.com/problems/maximum-subarray/)
>
> 🟡 中等 ｜ 标签：`动态规划` `分治`

## 📝 题目描述

给定一个整数数组 `nums`，请找出其中具有**最大和**的连续子数组（子数组至少包含一个元素），返回其最大和。子数组是数组中的一个连续部分。

**示例 1：**

```
输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
输出：6
解释：连续子数组 [4,-1,2,1] 的和最大，为 6。
```

**示例 2：**

```
输入：nums = [1]
输出：1
```

**示例 3：**

```
输入：nums = [5,4,-1,7,8]
输出：23
解释：整个数组的和最大。
```

**提示：**

- `1 <= nums.length <= 10^5`
- `-10^4 <= nums[i] <= 10^4`

**进阶**：如果已经实现复杂度为 `O(n)` 的解法，请尝试使用更为精妙的**分治法**求解。

## 💡 题解

### 解法一：动态规划（dp 数组）

**思路**：设 `dp[i]` 表示**以 `nums[i]` 结尾**的最大子数组和。转移只有两种选择：把 `nums[i]` 接在上一段后面（`dp[i-1] + nums[i]`），或者抛弃前段、以 `nums[i]` 单独开头（`nums[i]`），取两者较大值。由于最优子数组一定以某个下标结尾，最终答案是所有 `dp[i]` 的最大值。

```cpp
#include <vector>

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = (int)nums.size();
        vector<int> dp(n);
        dp[0] = nums[0];
        int ans = dp[0];
        for (int i = 1; i < n; ++i) {
            dp[i] = max(dp[i - 1] + nums[i], nums[i]);
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`

### 解法二：分治（线段树式合并）

**思路**：对区间 `[l, r]` 取中点分成两半，递归求解后合并。每个区间维护四个量：区间总和 `sum`、必含左端点的最大前缀和 `pre`、必含右端点的最大后缀和 `suf`、区间内最大子数组和 `best`。合并时：`pre` 要么完全在左半、要么跨过中点（左半总和 + 右半前缀）；`best` 要么在左半、要么在右半、要么横跨中点（左半后缀 + 右半前缀）。根区间的 `best` 即为答案，这也是线段树维护区间最大子段和的标准信息合并方式。

```cpp
#include <vector>

class Solution {
    // sum：区间和  pre：最大前缀和  suf：最大后缀和  best：最大子数组和
    struct Node {
        int sum, pre, suf, best;
    };

    Node merge(const Node& a, const Node& b) {
        return {a.sum + b.sum,
                max(a.pre, a.sum + b.pre),
                max(b.suf, b.sum + a.suf),
                max(max(a.best, b.best), a.suf + b.pre)};
    }

    Node solve(vector<int>& nums, int l, int r) {
        if (l == r) {
            int v = nums[l];
            return {v, v, v, v};
        }
        int m = (l + r) / 2;
        return merge(solve(nums, l, m), solve(nums, m + 1, r));
    }

public:
    int maxSubArray(vector<int>& nums) {
        return solve(nums, 0, (int)nums.size() - 1).best;
    }
};
```

- ⏱️ 时间复杂度：`O(n log n)`
- 💾 空间复杂度：`O(log n)`（递归栈）

### 解法三：Kadane 算法——滚动变量（推荐）

**思路**：解法一中 `dp[i]` 只依赖 `dp[i-1]`，用一个滚动变量 `cur` 即可：`cur` 表示"以当前元素结尾的最大子数组和"。若此前的 `cur` 为负，它对后续只有负贡献，直接舍弃重新开段，等价于 `cur = max(cur + x, x)`；`ans` 随时记录全局最大值。这就是经典的 Kadane 算法。

```cpp
#include <climits>
#include <vector>

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int cur = 0, ans = INT_MIN;
        for (int x : nums) {
            cur = max(cur, 0) + x;  // 前缀贡献为负则舍弃，重新开段
            ans = max(ans, cur);
        }
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 子数组必须非空：`ans` 要初始化为 `INT_MIN`（或 `nums[0]`），不能初始化为 `0`，否则全负数组（如 `[-3,-1,-2]`）会错误地返回 `0`。
- `dp[i]` 的定义是"**以 i 结尾**"，而不是"前 i 个元素中的最优"，两者含义不同，转移方程也不同。
- 分治合并时不要漏掉"横跨中点"的情况（左半后缀 `suf` + 右半前缀 `pre`），只取左右两半的 `best` 会漏解。
- Kadane 中舍弃前缀的判断是 `cur < 0`；写成 `cur <= 0` 结果仍正确，但把 `ans` 更新放在 `cur` 更新之前/之后要理清楚（先更新 `cur` 再更新 `ans`）。

---

[← 返回目录](../../README.md)
