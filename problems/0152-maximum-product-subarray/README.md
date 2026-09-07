# 152. 乘积最大子数组

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/maximum-product-subarray/) ｜ [国际站](https://leetcode.com/problems/maximum-product-subarray/)
>
> 🟡 中等 ｜ 标签：`动态规划`

## 📝 题目描述

给定一个整数数组 `nums`，找出其中乘积最大的**非空连续子数组**（子数组是数组中连续的一段），返回该子数组对应的乘积。

题目保证任意子数组的乘积都**不会超过** `2^31 - 1`，即结果在 32 位有符号整数范围内。

**示例 1：**

```
输入：nums = [2,3,-2,4]
输出：6
解释：乘积最大的连续子数组是 [2,3]，乘积为 6。
```

**示例 2：**

```
输入：nums = [-2,0,-1]
输出：0
解释：不能选 [-2,-1]（不连续），任何含 -2 或 -1 的连续子数组乘积
     都不超过 0，最大乘积是 0（子数组 [0]）。
```

**提示：**

- `1 <= nums.length <= 2 * 10^4`
- `-10 <= nums[i] <= 10`
- 任意子数组的乘积都保证是 32 位整数范围内的值

## 💡 题解

### 解法一：正反两次扫描

**思路**：观察乘积的符号翻转规律：子数组乘积为负当且仅当其中含**奇数个负数**。去掉一个"最靠边的负数"之后，剩下的部分乘积必为正。于是：

- **从左往右**累乘一遍，每步更新答案，遇到 `0` 就把乘积重置为 1（新子数组开头）；
- **从右往左**再做同样一遍。

两个方向的扫描分别覆盖了"去掉最右侧负数"与"去掉最左侧负数"两种情况，取两者最大即为答案。实现极简、不需要维护额外状态，但正确性论证不如解法二直观。

```cpp
#include <vector>
#include <algorithm>
#include <climits>

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = (int)nums.size();
        long long best = LLONG_MIN;
        long long prod = 1;
        for (int i = 0; i < n; ++i) {  // 从左到右
            prod *= nums[i];
            best = max(best, prod);
            if (prod == 0) prod = 1;  // 遇 0 重开子数组
        }
        prod = 1;
        for (int i = n - 1; i >= 0; --i) {  // 从右到左
            prod *= nums[i];
            best = max(best, prod);
            if (prod == 0) prod = 1;
        }
        return (int)best;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(1)`

### 解法二：动态规划——同时维护最大与最小乘积（推荐）

**思路**：与"最大子数组和"不同，乘积存在一个关键特性：**负数会把最大值翻转成最小值，最小值翻转成最大值**。因此以 `i` 结尾的状态必须同时记录最大乘积 `maxP` 与最小乘积 `minP`。转移时对三种候选取最大/最小：

- 接在以 `i - 1` 结尾的子数组后：`maxP * nums[i]` 与 `minP * nums[i]`；
- 以 `nums[i]` 重新开头（前面的乘积不划算）：`nums[i]` 本身。

若 `nums[i] < 0`，可以先交换 `maxP` 与 `minP`，让统一的转移式同时覆盖两种角色。滚动更新两个变量即可，无需数组。这一"状态成对维护"的技巧可推广到环形子数组（918 题）等变体，是更系统、更通用的解法。

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        long long maxP = nums[0], minP = nums[0];  // 以 i 结尾的最大/最小乘积
        long long best = nums[0];
        for (int i = 1; i < (int)nums.size(); ++i) {
            int x = nums[i];
            if (x < 0) swap(maxP, minP);               // 负数交换大小角色
            maxP = max((long long)x, maxP * x);        // 延续或重新开头
            minP = min((long long)x, minP * x);
            best = max(best, maxP);
        }
        return (int)best;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 只维护"最大乘积"不够：一个很小的负数乘上负元素会变成很大的正数，必须**同时维护最小乘积**。
- `0` 会把任何乘积截断，转移里"以 `nums[i]` 重新开头"这一候选不可省略。
- 用 `int` 累乘可能溢出（连乘中间量可能超出 `int`，尽管最终答案在范围内），中间量用 `long long` 更稳妥。
- 答案初值应取 `nums[0]`（或第一轮扫描中覆盖），不能取 0——数组可能全为负数，如 `[-2]` 的答案是 -2。
- 子数组必须**连续**，别把它当成可跳跃选取的子序列。

---

[← 返回目录](../../README.md)
