# 41. 缺失的第一个正数

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/first-missing-positive/) ｜ [国际站](https://leetcode.com/problems/first-missing-positive/)
>
> 🔴 困难 ｜ 标签：`哈希表` `原地交换`

## 📝 题目描述

给定一个未排序的整数数组 `nums`，请找出其中没有出现的**最小正整数**。

请实现时间复杂度为 `O(n)` 并且只使用常数级别额外空间的解决方案。

**示例 1：**

```
输入：nums = [1,2,0]
输出：3
解释：范围 [1,2] 中的数字都在数组中。
```

**示例 2：**

```
输入：nums = [3,4,-1,1]
输出：2
解释：1 在数组中，但 2 没有。
```

**示例 3：**

```
输入：nums = [7,8,9,11,12]
输出：1
解释：最小的正数 1 没有出现。
```

**提示：**

- `1 <= nums.length <= 10^5`
- `-2^31 <= nums[i] <= 2^31 - 1`

## 💡 题解

**关键观察**：长度为 `n` 的数组中，答案一定落在 `[1, n + 1]` 内——若 `1..n` 全部出现，答案为 `n + 1`；否则答案就是 `1..n` 中第一个缺失者。因此值不在 `[1, n]` 范围内的元素与答案无关，可以忽略或改造。

### 解法一：哈希表

**思路**：把所有元素放入哈希集合，然后从 `1` 开始逐个询问是否在集合中，第一个不在集合里的数就是答案。枚举上界到 `n + 1` 即可，思路最简单，但用了 `O(n)` 额外空间。

```cpp
#include <unordered_set>
#include <vector>

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = (int)nums.size();
        unordered_set<int> seen(nums.begin(), nums.end());
        for (int x = 1; x <= n + 1; ++x) {
            if (!seen.count(x)) return x;
        }
        return n + 1;  // 逻辑上不可达，占位返回
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`

### 解法二：原地哈希——符号标记法

**思路**：把 `nums` 自身当哈希表用，用**正负号**记录"某个值出现过"。第一遍把所有 `<= 0` 的值改成 `n + 1`（它们与答案无关，同时避免与负号标记混淆）；第二遍对每个值 `v = |nums[i]|`，若 `v ∈ [1, n]`，就把下标 `v - 1` 处的元素标成负数，表示"`v` 出现过"；第三遍找第一个仍为正数的下标 `i`，说明 `i + 1` 没出现过，即为答案。

```cpp
#include <cstdlib>
#include <vector>

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = (int)nums.size();
        for (int& x : nums) {
            if (x <= 0) x = n + 1;  // 排除非正数的干扰
        }
        for (int i = 0; i < n; ++i) {
            int v = abs(nums[i]);  // 可能已被标成负数，取绝对值还原
            if (v >= 1 && v <= n) {
                nums[v - 1] = -abs(nums[v - 1]);  // 标记 v 出现过（幂等）
            }
        }
        for (int i = 0; i < n; ++i) {
            if (nums[i] > 0) return i + 1;  // i+1 未被标记
        }
        return n + 1;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(1)`

### 解法三：原地置换（推荐）

**思路**：目标状态是"值 `v ∈ [1, n]` 的元素恰好放在下标 `v - 1` 上"（即 `nums[i] == i + 1`）。遍历每个位置，只要当前元素 `nums[i] ∈ [1, n]` 且它还没在"自己的位置"上，就把它换到 `nums[i] - 1` 处；换回来的新值继续同样处理（所以用 `while` 而不是 `if`）。整理完成后，第一个满足 `nums[i] != i + 1` 的下标 `i` 给出答案 `i + 1`；全都满足则答案为 `n + 1`。条件 `nums[nums[i] - 1] != nums[i]` 天然处理了重复值——目标位置已放着相等元素时停止交换，避免死循环。

```cpp
#include <utility>
#include <vector>

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = (int)nums.size();
        for (int i = 0; i < n; ++i) {
            // 把 nums[i] 换到下标 nums[i]-1，直到当前值越界或已在位
            while (nums[i] >= 1 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (nums[i] != i + 1) return i + 1;
        }
        return n + 1;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`（每完成一次交换至少让一个元素永久就位，总交换次数不超过 `n`）
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 答案上界是 `n + 1`：`1..n` 全部出现时要返回 `n + 1`，枚举/判断边界别只写到 `n`。
- 置换法的 `while` 条件缺一不可：值不在 `[1, n]` 必须跳过；`nums[nums[i]-1] == nums[i]`（目标位置已是相等元素，即重复值）必须停，否则 `[1,1]` 这类输入会死循环。
- `swap` 之后**不要**立刻 `i++`，换回来的新元素可能还需要继续向它的位置安置。
- 符号标记法必须先把非正数改成 `n + 1` 之类的"无效值"，否则原始负数会和"负号标记"混淆，无法区分。

---

[← 返回目录](../../README.md)
