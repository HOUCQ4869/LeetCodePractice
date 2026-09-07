# 11. 盛最多水的容器

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/container-with-most-water/) ｜ [国际站](https://leetcode.com/problems/container-with-most-water/)
>
> 🟡 中等 ｜ 标签：`双指针` `贪心`

## 📝 题目描述

给定一个长度为 `n` 的数组 `height`，第 `i` 条垂线的高度为 `height[i]`（下标从 0 开始）。从中选择两条线，与横轴共同构成一个容器，容器的容水量由两条线中**较短的一条**与两条线之间的**距离**决定：

```
容量 = min(height[i], height[j]) * (j - i)
```

求容器能容纳的最大水量。

**示例 1：**

```
输入：height = [1,8,6,2,5,4,8,3,7]
输出：49
解释：选择下标 1 和 8 的两条线，min(8, 7) * (8 - 1) = 7 * 7 = 49。
```

**示例 2：**

```
输入：height = [1,1]
输出：1
```

**提示：**

- `2 <= height.length <= 10^5`
- `0 <= height[i] <= 10^4`

## 💡 题解

### 解法一：暴力枚举

**思路**：枚举所有下标对 `(i, j)`，按公式计算面积取最大值。共 `O(n^2)` 个组合，`n = 10^5` 时约 `5 * 10^9` 次运算，会超时，仅用于理解题意与验证小数据。

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        int best = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                best = max(best, (j - i) * min(height[i], height[j]));
            }
        }
        return best;
    }
};
```

- ⏱️ 时间复杂度：`O(n^2)`
- 💾 空间复杂度：`O(1)`

### 解法二：双指针 + 贪心收缩（推荐）

**思路**：左右指针从数组两端出发，每轮先计算当前面积，然后**移动较短的一侧**。正确性：面积受短板限制；随着指针移动，宽度只会变小，此时若保留短板而移动较高的一侧，新容器的高度仍不超过短板、宽度更小，面积不可能超过当前值——即短板一方已不可能出现在更优解中，可安全舍弃。两指针各单向移动，合计至多 `n` 步。

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int maxArea(vector<int>& height) {
        int best = 0;
        int l = 0, r = static_cast<int>(height.size()) - 1;
        while (l < r) {
            // 面积 = 宽度 * 短板高度
            int area = (r - l) * min(height[l], height[r]);
            best = max(best, area);
            if (height[l] < height[r]) {
                ++l;  // 短板一侧不可能再参与更优解，安全舍弃
            } else {
                --r;
            }
        }
        return best;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 移动规则是「移动**较短**的一侧」；移动较长一侧会错过最优解。
- 两侧等高（`height[l] == height[r]`）时移动哪边都可以，不影响正确性，不必特判。
- 宽度是两线下标之差 `j - i`，别误写成 `j - i - 1`。
- 先算面积再移动指针，顺序颠倒会漏掉初始两端状态。
- 与「42. 接雨水」区分：本题只有两条边参与构成容器，不是逐列累加积水。

---

[← 返回目录](../../README.md)
