# 739. 每日温度

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/daily-temperatures/) ｜ [国际站](https://leetcode.com/problems/daily-temperatures/)
>
> 🟡 中等 ｜ 标签：`单调栈`

## 📝 题目描述

给定一个整数数组 `temperatures` 表示每天的气温，返回一个数组 `answer`，其中 `answer[i]` 表示对于第 `i` 天，还要等多少天才能等到一个**更高**的气温；如果之后都不会升温，则 `answer[i] = 0`。

**示例 1：**

```text
输入：temperatures = [73,74,75,71,69,72,76,73]
输出：[1,1,4,2,1,1,0,0]
解释：第 0 天 73 度，第 1 天 74 度更高，等 1 天；第 2 天 75 度，
     要到第 6 天的 76 度才更高，等 4 天；最后两天之后没有更高温度，为 0。
```

**示例 2：**

```text
输入：temperatures = [30,40,50,60]
输出：[1,1,1,0]
```

**示例 3：**

```text
输入：temperatures = [30,60,90]
输出：[1,1,0]
```

**提示：**

- `1 <= temperatures.length <= 10^5`
- `30 <= temperatures[i] <= 100`

## 💡 题解

### 解法一：暴力向后扫描

**思路**：对每一天，向后找第一个更高温度的下标，差值即答案。写法最直接，但最坏情况（温度单调不增）为 `O(n^2)`，`n` 达 `10^5` 时会超时，仅作对照。

```cpp
#include <vector>

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> ans(n, 0);
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (temperatures[j] > temperatures[i]) {
                    ans[i] = j - i;
                    break;
                }
            }
        }
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n^2)`
- 💾 空间复杂度：`O(1)`（不含返回数组）

### 解法二：单调栈（推荐）

**思路**：转换视角——不是问"每一天向右找更高温"，而是问"每一天**终结**了之前哪些天"。维护一个**存下标**的栈，从栈底到栈顶对应温度**单调递减**：遍历到第 `i` 天时，只要当前温度比栈顶那天的温度高，说明第 `i` 天就是栈顶那天等待的"更高温度"，弹出并结算 `ans[j] = i - j`；反复弹到栈顶不低于当前温度（或栈空）后，把 `i` 入栈。每个下标至多入栈、出栈一次，总代价 `O(n)`；留在栈里的下标之后没有更暖的一天，答案保持初始化的 0。

```cpp
#include <vector>
#include <stack>

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> ans(n, 0);
        stack<int> stk;  // 存下标，对应温度从栈底到栈顶单调递减
        for (int i = 0; i < n; i++) {
            // 当前温度比栈顶高：栈顶那一天找到了"下一个更高温度"
            while (!stk.empty() && temperatures[i] > temperatures[stk.top()]) {
                int j = stk.top();
                stk.pop();
                ans[j] = i - j;
            }
            stk.push(i);
        }
        // 循环结束后仍在栈中的下标没有更暖的一天，答案保持 0
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`（每个下标至多入栈、出栈一次）
- 💾 空间复杂度：`O(n)`

## ⚠️ 易错点

- 栈里要存**下标**而不是温度值：答案依赖下标之差，存值会丢失位置信息。
- 弹栈要用 `while` 而不是 `if`：一天的温度可能一次性"终结"栈中多天（如温度骤升）。
- 维护的是**严格递减**栈：相等温度不能弹（题目要求"更高"，等温不算），判断条件写 `temperatures[i] > temperatures[stk.top()]`。
- 末尾留在栈中的下标答案为 0，靠 `ans` 初始化为 0 自然成立，不需要再补一轮处理。

---

[← 返回目录](../../README.md)
