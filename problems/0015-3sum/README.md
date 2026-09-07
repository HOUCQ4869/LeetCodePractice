# 15. 三数之和

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/3sum/) ｜ [国际站](https://leetcode.com/problems/3sum/)
>
> 🟡 中等 ｜ 标签：`双指针` `排序`

## 📝 题目描述

给定一个整数数组 `nums`，判断是否存在三元组 `[nums[i], nums[j], nums[k]]` 满足 `i`、`j`、`k` **互不相同**且 `nums[i] + nums[j] + nums[k] == 0`。

返回**所有**和为 `0` 且**不重复**的三元组。同一个三元组在答案中只能出现一次，顺序不作要求。

**示例 1：**

```
输入：nums = [-1,0,1,2,-1,-4]
输出：[[-1,-1,2],[-1,0,1]]
解释：不同的三元组 [-1,0,1] 和 [-1,-1,2] 之和都为 0；
     注意 [0,1,-1] 与 [-1,0,1] 是同一组，不能重复输出。
```

**示例 2：**

```
输入：nums = [0,1,1]
输出：[]
解释：不存在和为 0 的三元组。
```

**示例 3：**

```
输入：nums = [0,0,0]
输出：[[0,0,0]]
```

**提示：**

- `3 <= nums.length <= 3000`
- `-10^5 <= nums[i] <= 10^5`

## 💡 题解

### 解法一：暴力枚举 + 集合去重

**思路**：三重循环枚举所有互不相同的下标组合，把和为 0 的三元组排序后插入有序集合去重，最后输出。`n = 3000` 时约 `4.5 * 10^9` 次运算，会超时，仅用于理解题意。

```cpp
#include <vector>
#include <algorithm>
#include <set>

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        set<vector<int>> uniq;  // 用有序集合去重
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                for (int k = j + 1; k < n; ++k) {
                    if (nums[i] + nums[j] + nums[k] == 0) {
                        vector<int> t = {nums[i], nums[j], nums[k]};
                        sort(t.begin(), t.end());
                        uniq.insert(t);
                    }
                }
            }
        }
        return vector<vector<int>>(uniq.begin(), uniq.end());
    }
};
```

- ⏱️ 时间复杂度：`O(n^3 log n)`
- 💾 空间复杂度：`O(n^3)`（去重集合）

### 解法二：排序 + 固定首数 + 双指针（推荐）

**思路**：先排序。枚举排序后的第一个数 `nums[i]`（`i` 从 0 到 `n-3`），问题化为在 `i` 之后的**有序区间**内找两数之和等于 `-nums[i]`——用左右双指针 `l`、`r`：和偏小则 `++l`，偏大则 `--r`，相等则记录答案并双双跳过重复值。去重分三层：`i` 与前一个首数相同则跳过；命中后 `l`、`r` 分别跳过与当前值相同的元素。另可用 `nums[i] > 0` 剪枝（最小数为正则三数之和必为正）。

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());
        int n = static_cast<int>(nums.size());
        for (int i = 0; i < n - 2; ++i) {
            if (nums[i] > 0) break;                         // 最小数已为正，不可能凑出 0
            if (i > 0 && nums[i] == nums[i - 1]) continue;  // 首数去重
            int l = i + 1, r = n - 1;
            while (l < r) {
                int sum = nums[i] + nums[l] + nums[r];
                if (sum < 0) {
                    ++l;
                } else if (sum > 0) {
                    --r;
                } else {
                    ans.push_back({nums[i], nums[l], nums[r]});
                    while (l < r && nums[l] == nums[l + 1]) ++l;  // 第二数去重
                    while (l < r && nums[r] == nums[r - 1]) --r;  // 第三数去重
                    ++l;
                    --r;
                }
            }
        }
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n^2)`（排序 `O(n log n)` 被主循环覆盖）
- 💾 空间复杂度：`O(log n)`，排序递归栈开销

## ⚠️ 易错点

- 去重是最大坑：只对首数去重、不对 `l`/`r` 去重（或反之）都会产生重复三元组；首数去重条件是 `i > 0 && nums[i] == nums[i-1]`。
- 命中一组答案后 `l`、`r` 在跳过重复值后必须**再各移动一步**，否则死循环。
- `i` 的枚举上界是 `n - 3`（保证后面还有两个数），写成 `n - 2` 也可但会多做无效轮次。
- 不排序直接用哈希表也能做，但去重逻辑复杂易错，排序 + 双指针是更稳的标准做法。

---

[← 返回目录](../../README.md)
