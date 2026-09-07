# 42. 接雨水

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/trapping-rain-water/) ｜ [国际站](https://leetcode.com/problems/trapping-rain-water/)
>
> 🔴 困难 ｜ 标签：`双指针` `动态规划` `单调栈`

## 📝 题目描述

给定 `n` 个非负整数表示每根宽度为 `1` 的柱子的高度图，计算按此排列的柱子下雨之后能接多少雨水。

**示例 1：**

```
输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
输出：6
```

**示例 2：**

```
输入：height = [4,2,0,3,2,5]
输出：9
```

**提示：**

- `1 <= height.length <= 2 * 10^4`
- `0 <= height[i] <= 10^5`

## 💡 题解

### 解法一：动态规划（预处理左右最大高度）

**思路**：按列分析，位置 `i` 的水位由「左侧最高柱」与「右侧最高柱」的较小者决定，能存的水量为 `min(leftMax[i], rightMax[i]) - height[i]`（不为负）。预先两次扫描求出每个位置的 `leftMax[i]` 与 `rightMax[i]`，再一趟累加即可。把逐位置的重复搜索降为查表。

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n < 3) return 0;
        vector<int> leftMax(n), rightMax(n);
        leftMax[0] = height[0];
        for (int i = 1; i < n; ++i) leftMax[i] = max(leftMax[i - 1], height[i]);
        rightMax[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; --i) rightMax[i] = max(rightMax[i + 1], height[i]);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans += min(leftMax[i], rightMax[i]) - height[i];
        }
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`

### 解法二：单调栈

**思路**：维护一个高度**单调递减**的栈（存下标）。当当前柱子高于栈顶柱时，栈顶成为「坑底」：弹出它，以新栈顶为左边界、当前柱为右边界，结算这一**横层**的水量——宽为 `i - left - 1`，高为 `min(height[left], height[i]) - height[bottom]`，逐层累加。与解法一的「按列」视角互补，这是「按层」视角。

```cpp
#include <vector>
#include <stack>
#include <algorithm>

class Solution {
public:
    int trap(vector<int>& height) {
        stack<int> st;  // 存下标，对应高度从栈底到栈顶单调递减
        int ans = 0;
        for (int i = 0; i < static_cast<int>(height.size()); ++i) {
            while (!st.empty() && height[i] > height[st.top()]) {
                int bottom = st.top();
                st.pop();             // 弹出的是坑底
                if (st.empty()) break;  // 左侧没有挡板，接不了水
                int left = st.top();
                int w = i - left - 1;                       // 横层宽度
                int h = min(height[left], height[i]) - height[bottom];
                ans += w * h;
            }
            st.push(i);
        }
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`，每个下标至多入栈、出栈一次
- 💾 空间复杂度：`O(n)`

### 解法三：双指针（推荐）

**思路**：解法一的两个数组其实可以省掉。用 `l`、`r` 双指针从两端向中间收拢，实时维护 `lMax`、`rMax`。**哪侧的最大值更小，哪侧的结果就已确定**——因为另一侧必然存在一根不低于它的柱子，该位置的水位只取决于自身一侧的最大值，可立即结算 `max - height` 并移动指针。一趟扫描、常数空间。

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int trap(vector<int>& height) {
        int n = static_cast<int>(height.size());
        if (n < 3) return 0;  // 少于三根柱子无法积水
        int l = 0, r = n - 1;
        int lMax = 0, rMax = 0, ans = 0;
        while (l < r) {
            lMax = max(lMax, height[l]);
            rMax = max(rMax, height[r]);
            if (lMax < rMax) {
                ans += lMax - height[l];  // 右侧必有更高的柱，左侧水位由 lMax 决定
                ++l;
            } else {
                ans += rMax - height[r];  // 左侧必有不低于 lMax 的柱，右侧水位由 rMax 决定
                --r;
            }
        }
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 每个位置的水量按列计算是 `min(左max, 右max) - 当前高度`，且需保证非负；别把「相邻两柱之差」当水量。
- 单调栈解法弹出栈顶后若栈已空要立即停止：左边没有挡板，这一层接不了水。
- 双指针解法中 `lMax`、`rMax` 要**包含当前位置自身**，保证 `max - height` 非负、边界位置不漏算。
- 别与「11. 盛最多水的容器」混淆：本题是所有柱子共同围出的凹槽逐格累加，不是只选两条边。

---

[← 返回目录](../../README.md)
