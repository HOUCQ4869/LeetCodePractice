# 215. 数组中的第K个最大元素

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/kth-largest-element-in-an-array/) ｜ [国际站](https://leetcode.com/problems/kth-largest-element-in-an-array/)
>
> 🟡 中等 ｜ 标签：`堆` `快速选择`

## 📝 题目描述

给定一个整数数组 `nums` 和一个整数 `k`，要求返回数组中第 `k` 个**最大**的元素。

注意：是排序后的第 `k` 个最大元素，而不是第 `k` 个**不同的**元素。例如 `[3,2,3,1,2,4,5,5,6]` 中第 4 大的元素是 `4`（重复元素按出现次数计入）。

**示例 1：**

```
输入：nums = [3,2,1,5,6,4], k = 2
输出：5
解释：排序后为 [1,2,3,4,5,6]，第 2 大的元素是 5。
```

**示例 2：**

```
输入：nums = [3,2,3,1,2,4,5,5,6], k = 4
输出：4
解释：排序后为 [1,2,2,3,3,4,5,5,6]，第 4 大的元素是 4。
```

**提示：**

- `1 <= k <= nums.length <= 10^5`
- `-10^4 <= nums[i] <= 10^4`

## 💡 题解

### 解法一：排序

**思路**：最直接的做法——将数组从大到小（或从小到大）排序，第 `k` 大的元素就落在固定下标上。整个数组有序显然是"信息过剩"的，但实现简单、常数小，实际运行速度往往不差。

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end(), greater<int>());
        return nums[k - 1];
    }
};
```

- ⏱️ 时间复杂度：`O(n log n)`
- 💾 空间复杂度：`O(log n)`（排序递归栈）

### 解法二：小顶堆（维护大小为 k 的堆）

**思路**：用一个小顶堆维护"当前最大的 `k` 个数"。先放入前 `k` 个元素，之后每来一个新元素，若比堆顶大则弹出堆顶、放入新元素。遍历结束后堆顶恰是第 `k` 大的元素。堆的大小始终不超过 `k`，适合 `n` 很大、`k` 较小的场景（如数据流）。C++ 的 `priority_queue` 默认是大顶堆，需改用 `greater<int>` 作比较器。

```cpp
#include <vector>
#include <queue>

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // 小顶堆：堆顶是当前 k 个数中的最小值
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int x : nums) {
            if ((int)pq.size() < k) {
                pq.push(x);
            } else if (x > pq.top()) {
                pq.pop();
                pq.push(x);
            }
        }
        return pq.top();
    }
};
```

- ⏱️ 时间复杂度：`O(n log k)`
- 💾 空间复杂度：`O(k)`

### 解法三：快速选择（推荐）

**思路**：借鉴快排的 `partition`：随机选一个基准值，把大于基准的换到左侧、小于基准的换到右侧，一趟下来基准就落在它排序后的最终位置 `p`（按"从大到小"排）。若 `p == k - 1`，基准即为答案；否则只需递归处理包含第 `k` 大元素的那**一侧**，另一侧整体舍弃。由于每次只探一侧，期望比较次数为 `n + n/2 + n/4 + ... = 2n`。随机化基准可避免有序输入退化为 `O(n^2)`。

```cpp
#include <vector>
#include <random>

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // [l, r] 内查找第 k 大，目标最终下标为 k - 1（从大到小排）
        int l = 0, r = (int)nums.size() - 1, target = k - 1;
        mt19937 rng(random_device{}());
        while (true) {
            int p = partition(nums, l, r, rng);
            if (p == target) return nums[p];
            if (p < target) {
                l = p + 1;   // 答案在右侧
            } else {
                r = p - 1;   // 答案在左侧
            }
        }
    }

private:
    // 随机选基准并三路划分，返回基准最终下标；大于基准的在左，小于基准的在右
    int partition(vector<int>& nums, int l, int r, mt19937& rng) {
        swap(nums[l], nums[l + (int)(rng() % (r - l + 1))]);
        int pivot = nums[l];
        int i = l + 1, j = r;
        while (i <= j) {
            while (i <= j && nums[i] > pivot) ++i;
            while (i <= j && nums[j] < pivot) --j;
            if (i <= j) {
                swap(nums[i], nums[j]);
                ++i;
                --j;
            }
        }
        swap(nums[l], nums[j]);
        return j;
    }
};
```

- ⏱️ 时间复杂度：期望 `O(n)`，最坏 `O(n^2)`（随机化后概率极低）
- 💾 空间复杂度：`O(1)`（迭代实现）

## ⚠️ 易错点

- 题目求的是第 `k` 大而不是第 `k` 小，用小顶堆或"从大到小 partition"时不要把方向搞反。
- 快速选择若固定取首元素做基准，遇到已排序数组会退化到 `O(n^2)`，务必随机化（或三数取中）。
- 堆解法中判断条件是 `x > pq.top()` 才替换，等于堆顶时无需操作。
- `partition` 里边界 `i <= j` 的判断遗漏会导致死循环或数组越界。

---

[← 返回目录](../../README.md)
