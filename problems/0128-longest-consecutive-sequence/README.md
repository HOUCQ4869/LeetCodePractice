# 128. 最长连续序列

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/longest-consecutive-sequence/) ｜ [国际站](https://leetcode.com/problems/longest-consecutive-sequence/)
>
> 🟡 中等 ｜ 标签：`哈希表` `并查集`

## 📝 题目描述

给定一个未排序的整数数组 `nums`，找出数字连续的最长序列（即 `x, x+1, x+2, ...` 这样的序列）的长度。

要求：序列中的元素在原数组中**不需要相邻**；算法时间复杂度需达到 `O(n)`。

**示例 1：**

```
输入：nums = [100,4,200,1,3,2]
输出：4
解释：最长数字连续序列是 [1, 2, 3, 4]，长度为 4。
```

**示例 2：**

```
输入：nums = [0,3,7,2,5,8,4,6,0,1]
输出：9
解释：最长数字连续序列是 [0, 1, 2, 3, 4, 5, 6, 7, 8]，长度为 9。
```

**提示：**

- `0 <= nums.length <= 10^5`
- `-10^9 <= nums[i] <= 10^9`

## 💡 题解

### 解法一：排序后线性扫描

**思路**：排序后连续的数必然相邻。一次遍历比较相邻元素：相等（重复元素）直接跳过；差为 1 则当前段长度加一；否则说明连续段断开，把段长重置为 1。过程中维护全局最大值。简单可靠，但复杂度由排序决定，为 `O(n log n)`，不满足进阶要求。

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) return 0;
        sort(nums.begin(), nums.end());
        int best = 1, cur = 1;
        for (int i = 1; i < static_cast<int>(nums.size()); ++i) {
            if (nums[i] == nums[i - 1]) continue;      // 跳过重复元素
            if (nums[i] == nums[i - 1] + 1) ++cur;     // 连续，段长加一
            else cur = 1;                              // 断开，重新开段
            best = max(best, cur);
        }
        return best;
    }
};
```

- ⏱️ 时间复杂度：`O(n log n)`
- 💾 空间复杂度：`O(log n)`，排序栈开销

### 解法二：哈希集合 + 只从起点扩展（推荐）

**思路**：把所有数放进 `unordered_set`。枚举集合中的每个数 `x`，只有当 `x - 1` **不在**集合中时，`x` 才可能是某个连续段的起点，此时从 `x` 出发不断探测 `x + 1`、`x + 2`……直到不在集合中，得到该段长度。非起点的数全部被跳过，因此每个数最多被访问常数次（一次判断是否起点、至多一次被某段扩展到），整体严格 `O(n)`。

```cpp
#include <vector>
#include <algorithm>
#include <unordered_set>

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> S(nums.begin(), nums.end());
        int best = 0;
        for (int x : S) {
            if (S.count(x - 1)) continue;  // x 不是段的起点，跳过，避免 O(n^2) 重复扫描
            int len = 1;
            while (S.count(x + len)) {     // 沿连续段向右探测
                ++len;
            }
            best = max(best, len);
        }
        return best;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`

## ⚠️ 易错点

- 数组含重复元素，排序解法必须显式跳过相等的相邻值，否则段长会被重复元素多算。
- 哈希解法若对**每个**数都向 `+1` 方向扩展，遇到 `1..n` 这类数据会退化到 `O(n^2)`；必须用「`x - 1` 不存在」保证只从段起点出发。
- 数组可能为空，此时应返回 0。
- 用红黑树实现的 `set` 整体是 `O(n log n)`，不满足题目要求，应使用 `unordered_set`。

---

[← 返回目录](../../README.md)
