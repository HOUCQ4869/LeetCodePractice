# 84. 柱状图中最大的矩形

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/largest-rectangle-in-histogram/) ｜ [国际站](https://leetcode.com/problems/largest-rectangle-in-histogram/)
>
> 🔴 困难 ｜ 标签：`单调栈`

## 📝 题目描述

给定 `n` 个非负整数，表示柱状图中 `n` 根宽度为 `1` 的柱子的高度，每个数在平面直角坐标系中按顺序相邻排列。求在该柱状图中，能勾勒出来的**矩形的最大面积**（矩形必须完全包含在柱状图内，底边与 x 轴重合）。

**示例 1：**

```text
输入：heights = [2,1,5,6,2,3]
输出：10
解释：取高度为 5 和 6 的两根相邻柱子（下标 2、3），
     以 5 为高、2 为宽的矩形面积最大，为 10。
```

**示例 2：**

```text
输入：heights = [2,4]
输出：4
解释：以 4 为高、1 为宽，或以 2 为高、2 为宽，最大面积均为 4。
```

**提示：**

- `1 <= heights.length <= 10^5`
- `0 <= heights[i] <= 10^4`

## 💡 题解

### 解法一：枚举每根柱子，向两侧扩展

**思路**：最大矩形必然以某根柱子的高度为高，且左右边界延伸到**第一根更矮的柱子**为止（含等高柱子）。枚举每根柱子 `i` 作为高度，向左、向右扩展到第一根严格更矮的柱子，宽度 `right - left + 1`，取所有方案的最大值。正确性直观，但最坏 `O(n^2)`（如全体等高），`n` 达 `10^5` 时会超时，仅作对照。

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            // 以 heights[i] 为矩形高度，向两侧扩展到第一根更矮的柱子
            int left = i;
            while (left - 1 >= 0 && heights[left - 1] >= heights[i]) left--;
            int right = i;
            while (right + 1 < n && heights[right + 1] >= heights[i]) right++;
            ans = max(ans, heights[i] * (right - left + 1));
        }
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n^2)`
- 💾 空间复杂度：`O(1)`

### 解法二：单调栈 + 哨兵（推荐）

**思路**：解法一的瓶颈在于向两侧扩展是线性的，而"每根柱子左右第一根更矮的柱子"可以用单调栈一次性求出。维护一个**存下标**的栈，对应高度从栈底到栈顶**单调递增**（相等不弹）：

- 遍历到第 `i` 根柱子时，若 `heights[i]` 比栈顶柱子**矮**，说明栈顶柱子的右边界已确定（就是 `i`），弹出并结算：矩形高为弹出柱的高度 `h`，左边界为弹出后的**新栈顶**（第一根更矮的柱子），宽度为 `i - left - 1`；反复弹到栈顶不高于当前柱后，`i` 入栈。
- 为把循环结束后残留在栈里的柱子全部结算，遍历范围延伸到 `i == n`，用高度 `0` 的**哨兵**充当右边界，强制清空整栈；栈底的"左边界"用 `-1`（虚拟哨兵）处理栈空情形。

等高柱子（如 `[2,2]`）虽不互相弹栈，但最终会由最后一根等高柱以完整宽度结算，答案不遗漏。每个下标至多入栈、出栈一次，总代价 `O(n)`。

```cpp
#include <vector>
#include <stack>
#include <algorithm>

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        stack<int> stk;  // 存下标，对应高度从栈底到栈顶单调递增
        int ans = 0;
        // i == n 时用高度 0 作哨兵，强制清空栈内所有柱子
        for (int i = 0; i <= n; i++) {
            int cur = (i == n) ? 0 : heights[i];
            while (!stk.empty() && cur < heights[stk.top()]) {
                int h = heights[stk.top()];
                stk.pop();
                // 左边界为弹出后新栈顶（不含），栈空则延伸到最左端 -1
                int left = stk.empty() ? -1 : stk.top();
                ans = max(ans, h * (i - left - 1));
            }
            stk.push(i);
        }
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`（每个下标至多入栈、出栈一次）
- 💾 空间复杂度：`O(n)`

## ⚠️ 易错点

- 宽度计算是本题最易错处：弹出柱子的矩形**左边界是弹出后的新栈顶（开边界）**、右边界是当前 `i`（开边界），宽为 `i - left - 1`；栈空时左边界为 `-1`，否则会漏掉延伸到最左端的矩形。
- **末尾哨兵不可省**：若只遍历到 `n - 1`，循环结束后栈内残留的柱子（右侧一路递增的情况）永远不会被结算，少算答案。
- 栈里存**下标**而不是高度：结算时既要取高度又要算宽度，存高度拿不到位置。
- 弹栈条件用严格小于 `cur < heights[stk.top()]`（等高不弹）：与"由最后一根等高柱结算完整宽度"的宽度计算配套，两种约定混用会重复或漏算。

---

[← 返回目录](../../README.md)
