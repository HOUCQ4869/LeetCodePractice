# 189. 轮转数组

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/rotate-array/) ｜ [国际站](https://leetcode.com/problems/rotate-array/)
>
> 🟡 中等 ｜ 标签：`数组` `数学`

## 📝 题目描述

给定一个整数数组 `nums`，将数组中的元素向**右**轮转 `k` 个位置，其中 `k` 是非负数。

**示例 1：**

```
输入：nums = [1,2,3,4,5,6,7], k = 3
输出：[5,6,7,1,2,3,4]
解释：
向右轮转 1 步: [7,1,2,3,4,5,6]
向右轮转 2 步: [6,7,1,2,3,4,5]
向右轮转 3 步: [5,6,7,1,2,3,4]
```

**示例 2：**

```
输入：nums = [-1,-100,3,99], k = 2
输出：[3,99,-1,-100]
解释：
向右轮转 1 步: [99,-1,-100,3]
向右轮转 2 步: [3,99,-1,-100]
```

**提示：**

- `1 <= nums.length <= 2 * 10^5`
- `-2^31 <= nums[i] <= 2^31 - 1`
- `0 <= k <= 10^5`

**进阶**：

- 尽可能想出更多的解决方案，至少有 **三种** 不同的方法可以解决这个问题。
- 你可以使用空间复杂度为 `O(1)` 的**原地**算法解决这个问题吗？

## 💡 题解

### 解法一：辅助数组

**思路**：轮转 `k` 步后，原下标 `i` 的元素落在新数组的 `(i + k) % n` 处。开一个新数组按此放置，再整体拷回 `nums` 即可。思路最直白，但需要 `O(n)` 额外空间。

```cpp
#include <vector>

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = (int)nums.size();
        k %= n;
        vector<int> tmp(n);
        for (int i = 0; i < n; ++i) {
            tmp[(i + k) % n] = nums[i];
        }
        nums = move(tmp);
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`

### 解法二：环状替换

**思路**：从下标 `start` 出发，把 `nums[start]` 送到它的最终位置 `(start + k) % n`，被挤出来的值继续送到下一个位置……直到回到 `start`，这一圈（环）上的元素全部一次性就位。一个环恰好经过 `n / gcd(n, k)` 个位置，因此共有 `gcd(n, k)` 个环。外层用 `count` 统计已就位的元素总数，凑满 `n` 即结束，保证每个元素恰好被移动一次。

```cpp
#include <utility>
#include <vector>

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = (int)nums.size();
        k %= n;
        int count = 0;  // 已就位元素计数
        for (int start = 0; count < n; ++start) {
            int cur = start;
            int prev = nums[start];
            do {
                int nxt = (cur + k) % n;
                swap(prev, nums[nxt]);  // prev 送到 nxt，换回原占用者继续送
                cur = nxt;
                ++count;
            } while (cur != start);  // 回到起点，本环结束
        }
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(1)`

### 解法三：三次翻转（推荐）

**思路**：向右轮转 `k` 步等价于把末尾 `k` 个元素整体搬到开头。做法分三步：

1. 整体翻转数组，此时末尾 `k` 个元素已位于前 `k` 个位置（内部顺序相反）；
2. 翻转前 `k` 个元素，恢复其内部顺序；
3. 翻转后 `n - k` 个元素，恢复其内部顺序。

以 `nums = [1,2,3,4,5,6,7], k = 3` 为例：整体翻转变为 `[7,6,5,4,3,2,1]`，翻转前 3 个得 `[5,6,7,4,3,2,1]`，再翻转后 4 个得 `[5,6,7,1,2,3,4]`。全程原地、代码最短。

```cpp
#include <algorithm>
#include <vector>

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = (int)nums.size();
        k %= n;  // k 可能大于等于 n
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + k);
        reverse(nums.begin() + k, nums.end());
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- `k` 可能大于等于 `n`，必须先 `k %= n`；环状替换若不取模会陷入死循环（数组永远转不出终点）。
- 环状替换必须用 `count` 计数终止（一个环可能包含多个起点下标，逐个起点无脑出发会重复处理）；内层是 `do-while`，回到 `start` 时结束本环。
- 翻转法的两段长度分别是 `k` 与 `n - k`，加起来正好是整个数组；写成"翻转前 `k` 个与后 `k` 个"就错了。
- 方向是**向右**轮转：对应"整体翻转 → 前 `k` → 后 `n-k`"；向左轮转的顺序不同（`[0, n-k)` 与 `[n-k, n)` 分别翻转后再整体翻转），别记混。

---

[← 返回目录](../../README.md)
