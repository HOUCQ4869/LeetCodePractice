# 238. 除自身以外数组的乘积

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/product-of-array-except-self/) ｜ [国际站](https://leetcode.com/problems/product-of-array-except-self/)
>
> 🟡 中等 ｜ 标签：`数组` `前缀和`

## 📝 题目描述

给定一个整数数组 `nums`，返回数组 `answer`，其中 `answer[i]` 等于 `nums` 中除 `nums[i]` 之外其余各元素的乘积。

题目数据保证数组 `nums` 中任意元素的全部前缀元素和后缀的乘积都在 **32 位整数**范围内。请**不要使用除法**，并在 `O(n)` 时间复杂度内完成此题。

**示例 1：**

```
输入：nums = [1,2,3,4]
输出：[24,12,8,6]
```

**示例 2：**

```
输入：nums = [-1,1,0,-3,3]
输出：[0,0,9,0,0]
```

**提示：**

- `2 <= nums.length <= 10^5`
- `-30 <= nums[i] <= 30`
- 输入保证数组 `answer[i]` 在 32 位整数范围内

**进阶**：你可以在 `O(1)` 的额外空间复杂度内完成这个题目吗？（出于空间复杂度分析的目的，**输出数组不被视为**额外空间。）

## 💡 题解

### 解法一：前缀积 × 后缀积

**思路**：除 `nums[i]` 以外的乘积 = 它**左边**所有数之积 × 它**右边**所有数之积。预处理两个数组：`pre[i]` 表示 `nums[0..i-1]` 的乘积（`pre[0] = 1`，左边没有元素），`suf[i]` 表示 `nums[i+1..n-1]` 的乘积（`suf[n-1] = 1`）。则 `answer[i] = pre[i] * suf[i]`，三次线性扫描完成。

```cpp
#include <vector>

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = (int)nums.size();
        vector<int> pre(n, 1), suf(n, 1);
        for (int i = 1; i < n; ++i) pre[i] = pre[i - 1] * nums[i - 1];
        for (int i = n - 2; i >= 0; --i) suf[i] = suf[i + 1] * nums[i + 1];
        vector<int> ans(n);
        for (int i = 0; i < n; ++i) ans[i] = pre[i] * suf[i];
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`

### 解法二：输出数组复用 + 滚动后缀（推荐）

**思路**：第一遍正向扫描，把前缀积直接写进输出数组 `ans`（`ans[i]` 暂存 `nums[0..i-1]` 之积）；第二遍反向扫描，用**一个滚动变量** `suf` 累积后缀积，边走边乘进 `ans[i]`。这样除返回值外只用了常数个变量，满足进阶要求。注意第二遍中必须**先乘后更新** `suf`，否则会把 `nums[i]` 自己也乘进去。

```cpp
#include <vector>

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = (int)nums.size();
        vector<int> ans(n);
        ans[0] = 1;
        for (int i = 1; i < n; ++i) {
            ans[i] = ans[i - 1] * nums[i - 1];  // 暂存前缀积
        }
        int suf = 1;  // 滚动后缀积
        for (int i = n - 1; i >= 0; --i) {
            ans[i] *= suf;   // 乘上右边所有数之积
            suf *= nums[i];  // 更新后缀，供更左边的位置使用
        }
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(1)`（输出数组不计入）

## ⚠️ 易错点

- 想用"总乘积 ÷ nums[i]"：数组含 `0` 时除法直接失效（除零），且题目明确禁止除法；即使分组统计零的个数也很绕，不必要。
- 前缀积的边界：`pre[0] = 1`（`i` 左边没有元素），后缀同理 `suf[n-1] = 1`，别把 `nums[0]` 自己乘进去。
- `O(1)` 写法中第二趟的顺序是"先用后更新"：`ans[i] *= suf` 必须在 `suf *= nums[i]` 之前，反了就会把 `nums[i]` 算进自己的答案。
- "任意前缀/后缀乘积在 32 位内"只保证**分侧**累乘安全，不代表全体元素之积不溢出，因此不能依赖先算总积再拆分的做法。

---

[← 返回目录](../../README.md)
