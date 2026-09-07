# 283. 移动零

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/move-zeroes/) ｜ [国际站](https://leetcode.com/problems/move-zeroes/)
>
> 🟢 简单 ｜ 标签：`双指针`

## 📝 题目描述

给定一个整数数组 `nums`，将所有 `0` 移动到数组的**末尾**，同时保持非零元素的**相对顺序**不变。

要求：必须**原地**操作，不能复制数组；尽量减少操作次数。

**示例 1：**

```
输入：nums = [0,1,0,3,12]
输出：[1,3,12,0,0]
```

**示例 2：**

```
输入：nums = [0]
输出：[0]
```

**提示：**

- `1 <= nums.length <= 10^4`
- `-2^31 <= nums[i] <= 2^31 - 1`

## 💡 题解

### 解法一：快慢指针覆盖 + 尾部补零

**思路**：维护写指针 `slow`，遍历数组，遇到非零元素就把它写到 `slow` 位置并前移 `slow`。遍历结束后，区间 `[0, slow)` 恰好是所有非零元素且相对顺序不变，再把尾部 `[slow, n)` 全部填 0 即可。两趟完成，逻辑直白。

```cpp
#include <vector>

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size();
        int slow = 0;
        for (int fast = 0; fast < n; ++fast) {
            if (nums[fast] != 0) {
                nums[slow++] = nums[fast];  // 非零元素前移覆盖
            }
        }
        for (; slow < n; ++slow) {
            nums[slow] = 0;  // 尾部统一补零
        }
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(1)`

### 解法二：双指针交换（推荐）

**思路**：同样让 `slow` 指向「下一个非零元素应放的位置」，`[0, slow)` 始终是已就位的非零前缀。遍历中遇到非零元素就与 `slow` 位置的元素交换再前移 `slow`——被换到 `fast` 位置的必然是 0（或恰好是自身），因此非零元素的相对顺序不会被破坏，且一趟扫描完成，无需第二趟补零；非零元素越靠前聚集，写入次数越少。

```cpp
#include <vector>
#include <utility>

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        for (int slow = 0, fast = 0; fast < static_cast<int>(nums.size()); ++fast) {
            if (nums[fast] != 0) {
                swap(nums[slow], nums[fast]);  // slow 处必为 0（或即自身）
                ++slow;
            }
        }
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 覆盖写法容易忘记第二趟把尾部清零，导致末尾残留旧值。
- `slow` 的前移时机：交换写法中必须**交换之后**再自增（或写成 `swap(nums[slow++], nums[fast])`），先自增会把元素放错一格。
- 不能对数组整体 `sort`：会打乱非零元素的相对顺序。
- 必须原地修改，另开数组暂存再拷回虽然能过，但违背题意（`O(n)` 额外空间）。

---

[← 返回目录](../../README.md)
