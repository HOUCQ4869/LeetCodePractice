# 169. 多数元素

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/majority-element/) ｜ [国际站](https://leetcode.com/problems/majority-element/)
>
> 🟢 简单 ｜ 标签：`哈希表` `摩尔投票`

## 📝 题目描述

给定一个大小为 `n` 的数组 `nums`，返回其中的**多数元素**。多数元素是指在数组中出现次数**大于** `⌊ n/2 ⌋` 的元素。

可以假设数组是非空的，并且给定的数组中总是存在多数元素。

**进阶**：尝试设计时间复杂度为 `O(n)`、空间复杂度为 `O(1)` 的算法解决此问题。

**示例 1：**

```
输入：nums = [3,2,3]
输出：3
```

**示例 2：**

```
输入：nums = [2,2,1,1,1,2,2]
输出：2
```

**提示：**

- `n == nums.length`
- `1 <= n <= 5 * 10^4`
- `-10^9 <= nums[i] <= 10^9`

## 💡 题解

**关键观察**：多数元素出现次数超过总数的一半，这意味着它比"其余所有元素加起来"还多——这是摩尔投票法和排序法能奏效的根本原因。

### 解法一：哈希表计数

**思路**：遍历数组，用哈希表统计每个元素出现的次数；一旦某元素计数超过 `⌊ n/2 ⌋`（代码里写成 `> n / 2`），立即返回。多数元素必然存在，所以一定会在遍历中或遍历结束时被找到。

```cpp
#include <unordered_map>
#include <vector>

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n = (int)nums.size();
        unordered_map<int, int> cnt;
        for (int x : nums) {
            if (++cnt[x] > n / 2) {
                return x;  // 计数过半，提前返回
            }
        }
        return 0;  // 题目保证存在多数元素，逻辑上不可达
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`

### 解法二：排序

**思路**：将数组排序后，多数元素占据了超过一半的位置，因此下标 `n/2` 处（无论向上还是向下取整）必然是多数元素。例如 `n = 7` 时多数元素至少出现 4 次，区间 `[0, 3]`、`[3, 6]` 等任何跨过中点的窗口都躲不开它。代价是排序需要 `O(n log n)` 时间。

```cpp
#include <algorithm>
#include <vector>

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() / 2];  // 中位数位置必是多数元素
    }
};
```

- ⏱️ 时间复杂度：`O(n log n)`
- 💾 空间复杂度：`O(log n)`（快排递归栈；库实现可能用 `O(n)` 辅助空间）

### 解法三：摩尔投票（推荐）

**思路**：把找多数元素想象成"阵营对战"：维护候选人 `candidate` 和票数 `count`。遇到与候选人相同的元素则 `count + 1`（己方增援），不同则 `count - 1`（消耗一票对拼掉一个敌人）；`count` 归零时换当前元素当新候选人。由于多数元素的数量**严格超过**其余所有元素之和，它无论怎样被消耗，最终一定能"活到最后"成为候选人。遍历结束时的 `candidate` 即答案。

```cpp
#include <vector>

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int candidate = 0;  // 候选人
        int count = 0;      // 候选人票数
        for (int x : nums) {
            if (count == 0) {
                candidate = x;  // 票数耗尽，更换候选人
            }
            count += (x == candidate) ? 1 : -1;  // 同阵营 +1，异阵营对拼 -1
        }
        return candidate;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 摩尔投票的前提是**多数元素一定存在**（出现次数 `> n/2`）；若不能保证，投票结束后还需再遍历一次验证 `candidate` 的真实出现次数。
- 判断条件是**严格大于** `n/2`：`n = 4` 时多数元素至少出现 3 次，哈希计数里写 `>= n/2` 会把只出现 2 次的元素误判为多数。
- 排序法取 `nums[n/2]` 依赖"超过一半"这一性质，若改为"超过 `n/3`"（229 题）就不能只看中点了。
- 摩尔投票中 `count == 0` 时要先更换候选人再计票，顺序颠倒会导致计数错误。

---

[← 返回目录](../../README.md)
