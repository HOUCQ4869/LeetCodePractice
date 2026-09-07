# 300. 最长递增子序列

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/longest-increasing-subsequence/) ｜ [国际站](https://leetcode.com/problems/longest-increasing-subsequence/)
>
> 🟡 中等 ｜ 标签：`动态规划` `二分查找`

## 📝 题目描述

给定一个整数数组 `nums`，找出其中**最长严格递增子序列**（LIS）的长度。

子序列是通过删除数组中的部分（也可以不删）元素、且不改变剩余元素相对顺序得到的序列。例如 `[3,6,2,7]` 是数组 `[0,3,1,6,2,2,7]` 的子序列。

**示例 1：**

```
输入：nums = [10,9,2,5,3,7,101,18]
输出：4
解释：最长严格递增子序列是 [2,3,7,101]（或 [2,5,7,101] 等），长度为 4。
```

**示例 2：**

```
输入：nums = [0,1,0,3,2,3]
输出：4
解释：最长严格递增子序列是 [0,1,2,3]。
```

**示例 3：**

```
输入：nums = [7,7,7,7,7,7,7]
输出：1
解释：严格递增要求元素互不相同，最长只能取 1 个。
```

**提示：**

- `1 <= nums.length <= 2500`
- `-10^4 <= nums[i] <= 10^4`

## 💡 题解

### 解法一：动态规划

**思路**：设 `dp[i]` 为**以 `nums[i] 结尾`**（必须选中）的最长严格递增子序列长度。转移时在所有 `j < i` 且 `nums[j] < nums[i]` 的位置中取最大 `dp[j]` 再加一；若没有这样的 `j`，则 `dp[i] = 1`。答案是所有 `dp[i]` 的最大值。之所以要"以 i 结尾"，是因为递增关系只关心子序列的最后一个元素——只有固定结尾，转移才成立。

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = (int)nums.size();
        vector<int> dp(n, 1);  // 至少包含自身
        int best = 1;
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            best = max(best, dp[i]);
        }
        return best;
    }
};
```

- ⏱️ 时间复杂度：`O(n^2)`
- 💾 空间复杂度：`O(n)`

### 解法二：贪心 + 二分查找（推荐）

**思路**：维护数组 `tails`，其中 `tails[k]` 表示**所有长度为 `k + 1` 的递增子序列中，结尾元素的最小值**。结尾越小，后续越容易接上新元素，这就是贪心所在。逐个处理 `nums[i]`：

- 若 `nums[i] > tails.back()`，可以直接延长当前最长子序列，尾插；
- 否则用**二分查找**找到 `tails` 中第一个 `>= nums[i]` 的位置并替换之——替换不改变当前长度，但让同长度子序列的结尾更小，为未来留出更多机会。

`tails` 始终严格递增（归纳可证），最终其长度即 LIS 长度。注意 `tails` 本身**不一定是**某个合法的 LIS，但长度一定等于 LIS 长度。

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> tails;  // tails[k]：长度 k+1 的递增子序列的最小结尾
        for (int x : nums) {
            auto it = lower_bound(tails.begin(), tails.end(), x);
            if (it == tails.end()) {
                tails.push_back(x);   // 比所有结尾都大，LIS 变长
            } else {
                *it = x;              // 替换为更小的结尾，保持潜力
            }
        }
        return (int)tails.size();
    }
};
```

- ⏱️ 时间复杂度：`O(n log n)`
- 💾 空间复杂度：`O(n)`

## ⚠️ 易错点

- 本题要求**严格**递增，二分应使用 `lower_bound`（找第一个 `>= x`）；若允许相等元素（非严格递增），才用 `upper_bound`。混用会导致重复元素被错误计入。
- 解法一的 `dp[i]` 定义是"以 `i` 结尾"，答案是 `max(dp[i])` 而不是 `dp[n - 1]`。
- `tails` 是"各长度最小结尾"的抽象结构，不是原数组的一个真实子序列，不能直接输出它作为 LIS。
- 替换操作发生在 `it == tails.end()` 之外的所有分支，别把"找不到才替换"的方向写反。

---

[← 返回目录](../../README.md)
