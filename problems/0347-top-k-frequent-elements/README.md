# 347. 前 K 个高频元素

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/top-k-frequent-elements/) ｜ [国际站](https://leetcode.com/problems/top-k-frequent-elements/)
>
> 🟡 中等 ｜ 标签：`堆` `哈希表`

## 📝 题目描述

给定一个整数数组 `nums` 和一个整数 `k`，返回其中出现频率前 `k` 高的元素。可以按**任意顺序**返回答案。

**示例 1：**

```
输入：nums = [1,1,1,2,2,3], k = 2
输出：[1,2]
解释：1 出现 3 次，2 出现 2 次，3 出现 1 次，频率前 2 高的是 1 和 2。
```

**示例 2：**

```
输入：nums = [1], k = 1
输出：[1]
```

**提示：**

- `1 <= nums.length <= 10^5`
- `k` 的取值范围是 `[1, 数组中互不相同的元素个数]`
- `-10^4 <= nums[i] <= 10^4`
- 题目数据保证答案唯一，无需考虑输出顺序

## 💡 题解

### 解法一：哈希计数 + 排序

**思路**：先用哈希表统计每个元素的出现次数，再把 `(元素, 频次)` 对按频次从大到小排序，取前 `k` 个。思路最直白，瓶颈在排序的 `O(m log m)`（`m` 为不同元素个数）。

```cpp
#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> cnt;
        for (int x : nums) ++cnt[x];

        vector<pair<int, int>> freq(cnt.begin(), cnt.end());
        sort(freq.begin(), freq.end(),
             [](const auto& a, const auto& b) { return a.second > b.second; });

        vector<int> res;
        for (int i = 0; i < k; ++i) res.push_back(freq[i].first);
        return res;
    }
};
```

- ⏱️ 时间复杂度：`O(n + m log m)`，最坏 `O(n log n)`
- 💾 空间复杂度：`O(m)`

### 解法二：小顶堆

**思路**：哈希计数后，维护一个大小为 `k` 的小顶堆（按频次比较），堆里保存"当前频次最高的 `k` 个元素"。新元素频次大于堆顶时替换。这样每步只花 `O(log k)` 而不是 `O(log m)`，当 `k` 远小于 `m` 时更划算。注意比较器写法和 215 题类似：`priority_queue` 默认大顶堆，此处需按频次小顶堆。

```cpp
#include <vector>
#include <unordered_map>
#include <queue>

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> cnt;
        for (int x : nums) ++cnt[x];

        // 小顶堆：堆顶是堆中频次最小的元素
        using P = pair<int, int>;  // (频次, 元素)
        priority_queue<P, vector<P>, greater<P>> pq;
        for (auto& [x, c] : cnt) {
            if ((int)pq.size() < k) {
                pq.emplace(c, x);
            } else if (c > pq.top().first) {
                pq.pop();
                pq.emplace(c, x);
            }
        }

        vector<int> res;
        while (!pq.empty()) {
            res.push_back(pq.top().second);
            pq.pop();
        }
        return res;
    }
};
```

- ⏱️ 时间复杂度：`O(n log k)`
- 💾 空间复杂度：`O(m + k)`

### 解法三：桶排序（推荐）

**思路**：频次的取值范围天然有限——一个元素最多出现 `n` 次。于是可以建 `n + 1` 个桶，下标 `i` 的桶存放恰好出现 `i` 次的元素，然后**从高频桶往低频桶**依次收集元素直到取满 `k` 个。整个过程没有任何比较排序，统计之后是线性扫描。

```cpp
#include <vector>
#include <unordered_map>

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int n = (int)nums.size();
        unordered_map<int, int> cnt;
        for (int x : nums) ++cnt[x];

        // buckets[i] 存放出现次数恰为 i 的所有元素
        vector<vector<int>> buckets(n + 1);
        for (auto& [x, c] : cnt) buckets[c].push_back(x);

        vector<int> res;
        for (int i = n; i >= 1 && (int)res.size() < k; --i) {
            for (int x : buckets[i]) {
                res.push_back(x);
                if ((int)res.size() == k) break;
            }
        }
        return res;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`

## ⚠️ 易错点

- 桶的数量要开 `n + 1`：某元素可能独占整个数组，频次为 `n`。
- 堆解法中比较对象是**频次**而不是元素值，`pair` 里把频次放前面可直接复用默认比较。
- `priority_queue` 默认是大顶堆，求"前 k 大"反而要配 `greater` 构造**小**顶堆。
- 收集桶时内层循环取满 `k` 个后要及时退出，避免多余遍历。

---

[← 返回目录](../../README.md)
