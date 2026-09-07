# 1. 两数之和

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/two-sum/) ｜ [国际站](https://leetcode.com/problems/two-sum/)
>
> 🟢 简单 ｜ 标签：`哈希表`

## 📝 题目描述

给定一个整数数组 `nums` 和一个整数目标值 `target`，请找出数组中相加之和等于 `target` 的两个整数，返回它们的数组下标。

- 同一个元素不能重复使用，即返回的两个下标必须不同；
- 题目保证**恰好存在一组**有效答案，两个下标的返回顺序不限。

**示例 1：**

```
输入：nums = [2,7,11,15], target = 9
输出：[0,1]
解释：nums[0] + nums[1] = 2 + 7 = 9，因此返回 [0, 1]。
```

**示例 2：**

```
输入：nums = [3,2,4], target = 6
输出：[1,2]
解释：不能选两个 3（同一个元素不能用两次），3 + 2 不等于 6，2 + 4 = 6。
```

**示例 3：**

```
输入：nums = [3,3], target = 6
输出：[0,1]
```

**提示：**

- `2 <= nums.length <= 10^4`
- `-10^9 <= nums[i] <= 10^9`
- `-10^9 <= target <= 10^9`
- 只会存在一个有效答案

## 💡 题解

### 解法一：暴力枚举

**思路**：用双重循环枚举所有下标对 `(i, j)`（`j` 从 `i + 1` 开始），逐一检查 `nums[i] + nums[j]` 是否等于 `target`。`j > i` 的写法天然保证两个下标不同，也不会重复枚举对称组合。实现最直接，但平方级复杂度在 `n = 10^4` 时约需 `10^8` 次比较，偏慢。

```cpp
#include <vector>

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
        return {};  // 题目保证有解，不会到达
    }
};
```

- ⏱️ 时间复杂度：`O(n^2)`
- 💾 空间复杂度：`O(1)`

### 解法二：哈希表（推荐）

**思路**：把「找配对」变成「查表」。遍历数组，用哈希表维护「数值 → 下标」映射；遍历到 `nums[i]` 时，先查 `target - nums[i]` 是否已在表中——在就直接返回，不在才把 `nums[i]` 存入。**先查后存**保证不会把当前元素和自己配对（例如 `target = 8`、当前元素为 `4` 时不会误匹配到自身下标）。每个元素只访问一次，查表均摊 `O(1)`。

```cpp
#include <vector>
#include <unordered_map>

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> pos;  // 数值 -> 下标
        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            auto it = pos.find(target - nums[i]);
            if (it != pos.end()) {
                return {it->second, i};  // 旧下标在前，保证两下标不同
            }
            pos[nums[i]] = i;  // 先查找、后插入，避免匹配到自身
        }
        return {};
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`

## ⚠️ 易错点

- 先把当前元素插入哈希表再查找，当 `target` 恰为某元素的两倍时会错误地匹配到自身；正确顺序是**先查找、后插入**。
- 返回的是下标而不是数值，别把 `{nums[i], nums[j]}` 当作答案。
- 用有序 `map` 也能通过，但会多一个 `log n` 因子；本题不需要有序性，应选 `unordered_map`。
- 数组中可能有重复元素，哈希表只记录每个数最后一次出现的下标即可（题目保证唯一解，不影响正确性）。

---

[← 返回目录](../../README.md)
