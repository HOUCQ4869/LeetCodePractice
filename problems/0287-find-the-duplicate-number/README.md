# 287. 寻找重复数

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/find-the-duplicate-number/) ｜ [国际站](https://leetcode.com/problems/find-the-duplicate-number/)
>
> 🟡 中等 ｜ 标签：`二分查找` `快慢指针`

## 📝 题目描述

给定一个包含 `n + 1` 个整数的数组 `nums`，其数字都在 `[1, n]` 的范围内（含 `1` 和 `n`）。由鸽巢原理可知**至少存在一个**重复的整数。

假设 `nums` 中**只有一个**重复的整数，请找出这个重复的数。

设计的解决方案必须**不修改**数组 `nums`（数组只读），且只使用 `O(1)` 的额外空间，时间复杂度不超过 `O(n²)`（理想为 `O(n log n)` 或更优）。

**示例 1：**

```
输入：nums = [1,3,4,2,2]
输出：2
```

**示例 2：**

```
输入：nums = [3,1,3,4,2]
输出：3
```

**示例 3：**

```
输入：nums = [1,1]
输出：1
```

**提示：**

- `1 <= n <= 10^5`
- `nums.length == n + 1`
- `1 <= nums[i] <= n`
- `nums` 中只有一个整数出现**两次或多次**，其余整数只出现一次

## 💡 题解

**关键观察**：`n + 1` 个数装进值域 `[1, n]` 中，必有重复。若把下标与值看成"从 `i` 走向 `nums[i]`"的函数，重复值意味着**两个不同下标指向同一个位置**——这正构成一个有环链表，环的入口就是重复数。

### 解法一：二分答案

**思路**：不对数组排序，而是对**值域** `[1, n]` 二分。统计 `nums` 中不超过 `mid` 的元素个数 `cnt`：若没有重复，`[1, mid]` 内最多容纳 `mid` 个数；当 `cnt > mid` 时，说明有"多余"的数挤在 `[1, mid]` 里，重复数落在左半区间，否则落在右半区间。每轮统计是 `O(n)`，总共 `O(log n)` 轮。注意该解法不修改数组，但 `cnt` 逐个计数满足只读要求。

```cpp
#include <vector>

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int lo = 1, hi = (int)nums.size() - 1;  // 值域 [1, n]
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            int cnt = 0;
            for (int x : nums) {
                if (x <= mid) ++cnt;  // 统计落在 [1,mid] 内的个数
            }
            if (cnt > mid) {
                hi = mid;  // [1,mid] 挤入了多余的数，重复数在左半
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }
};
```

- ⏱️ 时间复杂度：`O(n log n)`
- 💾 空间复杂度：`O(1)`

### 解法二：位运算

**思路**：逐位考虑。对第 `k` 位，统计数组中该位为 `1` 的元素个数 `c`，再统计无重复参照序列 `1..n` 中该位为 `1` 的个数 `base`。若 `c > base`，说明重复数（比参照多出现的那份）在该位上是 `1`，把答案的这一位置 `1`。所有位拼起来即为重复数。只读不改、常数空间，但要扫 32 遍。

```cpp
#include <vector>

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = (int)nums.size() - 1;
        int ans = 0;
        for (int k = 0; k < 32; ++k) {
            int c = 0, base = 0;
            for (int i = 0; i <= n; ++i) {
                if (nums[i] >> k & 1) ++c;        // 数组中第 k 位为 1 的个数
                if (i >> k & 1) ++base;            // 1..n 中第 k 位为 1 的个数
            }
            if (c > base) ans |= 1 << k;  // 多出来的 1 来自重复数
        }
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n log C)`（`C` 为值域上界，32 位即 32 遍扫描）
- 💾 空间复杂度：`O(1)`

### 解法三：快慢指针判环（推荐）

**思路**：把 `nums` 视为链表——下标 `i` 的"下一个节点"是下标 `nums[i]`，即 `i -> nums[i]`。由于值域 `[1, n]` 而下标从 `0` 开始，从 `0` 出发永远回不到 `0`，构成的链表**必有环**（重复值被两个下标指向，正是成环的交叉点）。

- 第一阶段：`slow` 每次走一步（`slow = nums[slow]`），`fast` 每次走两步（`fast = nums[nums[fast]]`），两者必在环内某点相遇；
- 第二阶段：把 `slow` 放回起点 `0`，`slow`、`fast` 改为**同速**各走一步，再次相遇的位置就是**环的入口**——由经典推导，环入口的编号恰好等于重复数，因此返回相遇时的下标即可。

全程只做读取，不修改数组，一遍定位。

```cpp
#include <vector>

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        // 第一阶段：快慢指针在环内相遇
        int slow = 0, fast = 0;
        do {
            slow = nums[slow];            // 慢指针走一步
            fast = nums[nums[fast]];      // 快指针走两步
        } while (slow != fast);
        // 第二阶段：同速前进找环入口
        slow = 0;
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;  // 相遇点的下标恰为重复数（环入口编号即重复值）
    }
};
```

- ⏱️ 时间复杂度：`O(n)`（Floyd 判圈，相遇前走的步数不超过环长与入口距离的线性组合）
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 题目要求数组**只读**：常见的"符号标记法"（如 448、442 题的取负技巧）和"原地交换/排序"在这里都被禁止。
- 快慢指针的起点必须选 `0`：下标 `0` 没有任何值指向它（值域从 `1` 开始），从 `0` 出发才能保证走到环上且入口推导成立。
- 第一阶段要用 `do-while`：起点处 `slow == fast == 0`，用 `while` 会在第一次判断时直接退出。
- 二分答案是对**值域**而非下标二分，且不能对数组排序（只读约束）；`mid` 要用 `lo + (hi - lo) / 2` 防溢出（本题值域小，但保持习惯）。
- 位运算法中"多出来的 1"判据是 `c > base`：相等不能算，因为缺失的数可能恰好抵消掉非重复数的贡献。

---

[← 返回目录](../../README.md)
