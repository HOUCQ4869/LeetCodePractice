# 295. 数据流的中位数

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/find-median-from-data-stream/) ｜ [国际站](https://leetcode.com/problems/find-median-from-data-stream/)
>
> 🔴 困难 ｜ 标签：`堆` `设计`

## 📝 题目描述

设计一个支持以下两种操作的数据结构：

- `addNum(num)`：从数据流中向结构里添加一个整数。
- `findMedian()`：返回目前所有整数的中位数。

中位数定义：若元素个数为奇数，返回正中间那个数；若为偶数，返回中间两个数的平均值。

**示例 1：**

```
输入：
["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
[[], [1], [2], [], [3], []]
输出：
[null, null, null, 1.5, null, 2.0]
解释：加入 1、2 后中位数为 (1 + 2) / 2 = 1.5；再加入 3 后中位数为 2。
```

**示例 2：**

```
输入：
["MedianFinder", "addNum", "findMedian"]
[[], [-1], []]
输出：
[null, null, -1.0]
```

**提示：**

- `-10^5 <= num <= 10^5`
- `findMedian` 最多调用 `5 * 10^4` 次
- 题目保证调用 `findMedian` 之前结构中至少有一个元素

## 💡 题解

### 解法一：有序数组 + 二分插入

**思路**：用数组维护当前所有数并保持有序。插入时二分找到插入位置（`lower_bound`），再挪动后半段把新数放进去；查询中位数直接取中间下标。插入需要 `O(n)` 挪动元素，调用次数多时较慢，但胜在简单直观。

```cpp
#include <vector>
#include <algorithm>

class MedianFinder {
public:
    MedianFinder() {}

    void addNum(int num) {
        auto it = lower_bound(arr.begin(), arr.end(), num);
        arr.insert(it, num);
    }

    double findMedian() {
        int n = (int)arr.size();
        if (n % 2 == 1) return arr[n / 2];
        return (arr[n / 2 - 1] + arr[n / 2]) / 2.0;
    }

private:
    vector<int> arr;  // 始终保持升序
};
```

- ⏱️ 时间复杂度：`addNum` 为 `O(n)`，`findMedian` 为 `O(1)`
- 💾 空间复杂度：`O(n)`

### 解法二：双堆（大顶堆 + 小顶堆）（推荐）

**思路**：把整个有序序列"劈"成两半：**左半较大的一半**放进大顶堆 `low`，**右半较小的一半**放进小顶堆 `high`，并约定两者大小相等或 `low` 恰好多一个。这样：

- 中位数 = `low` 的堆顶（奇数个）；或两堆顶的平均值（偶数个），`O(1)` 可得。
- 插入时先压入 `low` 再把 `low` 的堆顶"倒入" `high`，再把 `high` 的堆顶"倒回" `low`。两次倒腾保证了两个堆之间的**有序分割**（`low` 中所有数 ≤ `high` 中所有数），同时自动维持大小约定。

每个新数最多经过三次堆操作，代价 `O(log n)`。

```cpp
#include <queue>

class MedianFinder {
public:
    MedianFinder() {}

    void addNum(int num) {
        // 先入大顶堆，再把它当前的最大值移入小顶堆，保证 low <= high
        low.push(num);
        high.push(low.top());
        low.pop();
        // 平衡大小：low 与 high 相等，或 low 恰好多一个
        if (high.size() > low.size()) {
            low.push(high.top());
            high.pop();
        }
    }

    double findMedian() {
        if (low.size() > high.size()) return low.top();
        return (low.top() + high.top()) / 2.0;
    }

private:
    priority_queue<int> low;  // 大顶堆：较小的一半（含中位数候选）
    priority_queue<int, vector<int>, greater<int>> high;  // 小顶堆：较大的一半
};
```

- ⏱️ 时间复杂度：`addNum` 为 `O(log n)`，`findMedian` 为 `O(1)`
- 💾 空间复杂度：`O(n)`

## ⚠️ 易错点

- 方向别记反：**较小的一半用大顶堆**（要快速取到左半最大值），较大的一半用小顶堆。
- 必须维护大小约定（相差不超过 1 且 `low` 多的至多一个），否则 `findMedian` 无法 `O(1)` 判断。
- 中位数为两堆顶之和**除以 2.0**，写成整数除法会丢精度。
- 偶数个时中位数是 `low.top()` 与 `high.top()` 的平均，别错取成同一个堆的两个数。
- 调用 `top()` 前必须保证堆非空，本题题目保证至少一个元素，但仍要留意大小平衡逻辑写对。

---

[← 返回目录](../../README.md)
