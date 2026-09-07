# 239. 滑动窗口最大值

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/sliding-window-maximum/) ｜ [国际站](https://leetcode.com/problems/sliding-window-maximum/)
>
> 🔴 困难 ｜ 标签：`单调队列` `滑动窗口`

## 📝 题目描述

给你一个整数数组 `nums` 和一个滑动窗口的大小 `k`。窗口从数组最左侧移动到最右侧，每次向右移动一位，只能看到 `k` 个数字，窗口每次移动后得到一个新的窗口最大值。

返回**每个窗口位置的最大值**构成的数组。

**示例 1：**

```
输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
输出：[3,3,5,5,6,7]

窗口位置                  最大值
[1  3  -1]                3
 1 [3  -1  -3]            3
 1  3 [-1  -3   5]        5
 1  3 -1 [-3   5   3]     5
 1  3 -1 -3  [5   3   6]  6
 1  3 -1 -3   5 [3   6  7] 7
```

**示例 2：**

```
输入：nums = [1], k = 1
输出：[1]
```

**提示：**

- `1 <= nums.length <= 10^5`
- `-10^4 <= nums[i] <= 10^4`
- `1 <= k <= nums.length`

## 💡 题解

### 解法一：暴力取最大

**思路**：对每个窗口线性扫描求最大值。`n - k + 1` 个窗口、每个 `O(k)`，总量 `O(n * k)`，`n = 10^5` 时会超时，仅作参照。

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ans;
        for (int i = 0; i + k <= n; ++i) {
            ans.push_back(*max_element(nums.begin() + i, nums.begin() + i + k));
        }
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n * k)`
- 💾 空间复杂度：`O(1)`（不计输出）

### 解法二：大顶堆（懒删除）

**思路**：堆中存放 `(值, 下标)` 对。右端每前进一位就压入新元素；取答案前先把**堆顶下标已滑出窗口**的元素弹出（懒删除，过期的较小元素留在堆里无害）。每个元素进出堆至多一次，`O(n log n)`。

```cpp
#include <vector>
#include <queue>
#include <utility>

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        priority_queue<pair<int, int>> pq;  // (值, 下标) 大顶堆
        vector<int> ans;
        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            pq.emplace(nums[i], i);
            if (i >= k - 1) {
                while (pq.top().second <= i - k) {
                    pq.pop();  // 堆顶已过期，弹出
                }
                ans.push_back(pq.top().first);
            }
        }
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n log n)`
- 💾 空间复杂度：`O(n)`

### 解法三：单调队列（推荐）

**思路**：用双端队列维护**下标**，使其对应的值从队头到队尾**单调递减**，队头始终是当前窗口最大值。右端进入下标 `i` 前先从队尾弹出所有值不超过 `nums[i]` 的旧下标——它们比新元素又旧又小，不可能再成为任何后续窗口的最大值；若队头下标已滑出窗口（`<= i - k`）则从队头弹出。每个下标至多入队、出队一次，均摊 `O(n)`。

```cpp
#include <vector>
#include <deque>

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> ans;
        deque<int> dq;  // 存下标，对应值从队头到队尾单调递减
        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            if (!dq.empty() && dq.front() <= i - k) {
                dq.pop_front();  // 队头已滑出窗口
            }
            while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();  // 不大于新元素的旧元素不可能成为后续窗口的最大值
            }
            dq.push_back(i);
            if (i >= k - 1) {
                ans.push_back(nums[dq.front()]);
            }
        }
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(k)`

## ⚠️ 易错点

- 队列里必须存**下标**而非值，否则无法判断队头是否已滑出窗口。
- 过期判断是 `dq.front() <= i - k`（窗口为 `[i - k + 1, i]`），边界差一容易写错。
- 从队尾弹出旧元素时，比较的是 `nums[dq.back()]` 与 `nums[i]`（**值**），别误比下标本身。
- `i >= k - 1` 之后才开始记录答案，且要先维护队列（去过期、入队）再取队头。

---

[← 返回目录](../../README.md)
