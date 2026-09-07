# 560. 和为 K 的子数组

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/subarray-sum-equals-k/) ｜ [国际站](https://leetcode.com/problems/subarray-sum-equals-k/)
>
> 🟡 中等 ｜ 标签：`前缀和` `哈希表`

## 📝 题目描述

给你一个整数数组 `nums` 和一个整数 `k`，请统计并返回该数组中**和恰好为 `k` 的连续子数组**的个数。

**示例 1：**

```
输入：nums = [1,1,1], k = 2
输出：2
解释：子数组 [1,1] 出现了两次（分别位于下标 (0,1) 与 (1,2)），位置不同即视为不同子数组。
```

**示例 2：**

```
输入：nums = [1,2,3], k = 3
输出：2
解释：子数组 [1,2] 与 [3] 的和均为 3。
```

**提示：**

- `1 <= nums.length <= 2 * 10^4`
- `-1000 <= nums[i] <= 1000`
- `-10^7 <= k <= 10^7`

## 💡 题解

### 解法一：暴力枚举区间

**思路**：枚举每个左端点 `i`，向右累加并随时判断当前区间和是否等于 `k`。区间和边扫边算，无需前缀数组，空间 `O(1)`；但 `n = 2 * 10^4` 时约 `2 * 10^8` 次加法，偏慢且大数据下可能超时。

```cpp
#include <vector>

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size(), ans = 0;
        for (int i = 0; i < n; ++i) {
            int sum = 0;
            for (int j = i; j < n; ++j) {
                sum += nums[j];
                if (sum == k) ++ans;  // 以 j 结尾、以 i 开头的子数组
            }
        }
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n^2)`
- 💾 空间复杂度：`O(1)`

### 解法二：前缀和 + 哈希表（推荐）

**思路**：记前缀和 `pre[j]` 为前 `j` 个数之和，则子数组 `(i, j]` 的和为 `pre[j] - pre[i]`。要求其等于 `k`，即找满足 `pre[i] = pre[j] - k` 的更早前缀。从左往右扫，用哈希表记录**每个前缀和出现的次数**；扫到位置 `j` 时查询 `pre[j] - k` 出现过几次，就有几个满足条件的子数组。初始化 `cnt[0] = 1` 以统计从下标 0 开始的子数组。注意数组含负数，前缀和不单调，**不能**套用滑动窗口。

```cpp
#include <vector>
#include <unordered_map>

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> cnt;  // 前缀和 -> 出现次数
        cnt[0] = 1;                   // 空前缀，用于统计从下标 0 开始的子数组
        int pre = 0, ans = 0;
        for (int x : nums) {
            pre += x;
            auto it = cnt.find(pre - k);
            if (it != cnt.end()) {
                ans += it->second;  // 这些前缀结束位置的下一格，都能构成和为 k 的子数组
            }
            ++cnt[pre];  // 先查询、后插入，避免把空子数组统计进去
        }
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`

## ⚠️ 易错点

- 忘记 `cnt[0] = 1`，会漏掉「从下标 0 开始」的子数组（例如 `[3], k = 3` 应得 1）。
- 先插入后查询会把长度为 0 的空子数组也算进去（`k = 0` 时结果偏大）；正确顺序是**先查询、后插入**。
- 数组含负数，前缀和并不单调，不能用双指针/滑动窗口求解。
- 前缀和的量级约 `±2 * 10^7`，`int` 足够；用 `unordered_map` 而非 `map`，避免多余的 `log` 因子。

---

[← 返回目录](../../README.md)
