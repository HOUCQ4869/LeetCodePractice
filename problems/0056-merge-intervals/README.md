# 56. 合并区间

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/merge-intervals/) ｜ [国际站](https://leetcode.com/problems/merge-intervals/)
>
> 🟡 中等 ｜ 标签：`排序` `数组`

## 📝 题目描述

以数组 `intervals` 表示若干个区间的集合，其中单个区间为 `intervals[i] = [start_i, end_i]`。请合并所有重叠的区间，并返回一个**不重叠**的区间数组，该数组需恰好覆盖输入中的所有区间。注意端点相接（如 `[1,4]` 与 `[4,5]`）也视为重叠。

**示例 1：**

```
输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
输出：[[1,6],[8,10],[15,18]]
解释：区间 [1,3] 和 [2,6] 重叠，将它们合并为 [1,6]。
```

**示例 2：**

```
输入：intervals = [[1,4],[4,5]]
输出：[[1,5]]
解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。
```

**示例 3：**

```
输入：intervals = [[4,7],[1,4]]
输出：[[1,7]]
解释：区间 [1,4] 和 [4,7] 可被视为重叠区间。
```

**提示：**

- `1 <= intervals.length <= 10^4`
- `intervals[i].length == 2`
- `0 <= start_i <= end_i <= 10^4`

## 💡 题解

### 解法一：排序 + 结果数组扫描合并

**思路**：先按左端点从小到大排序。排序后，能与某个区间重叠的区间必然集中出现，因此只需一趟扫描：维护结果数组 `merged`，对每个当前区间 `cur`，若它非空且 `cur` 的左端点不超过 `merged` 中最后一个区间的右端点，说明重叠，把最后一个区间的右端点扩展为两者的较大值；否则 `cur` 与之前所有区间都不重叠，直接追加。

```cpp
#include <algorithm>
#include <vector>

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> merged;
        for (auto& cur : intervals) {
            if (!merged.empty() && cur[0] <= merged.back()[1]) {
                merged.back()[1] = max(merged.back()[1], cur[1]);  // 重叠：扩展右端点
            } else {
                merged.push_back(cur);  // 与之前的区间无重叠
            }
        }
        return merged;
    }
};
```

- ⏱️ 时间复杂度：`O(n log n)`（排序为主）
- 💾 空间复杂度：`O(n)`（结果数组；不计返回值时为排序的 `O(log n)`）

### 解法二：排序 + 原地合并（推荐）

**思路**：与解法一逻辑相同，但不借助额外数组：把排序后的 `intervals` 自身当作输出缓冲，用写指针 `k` 指向"已合并的最后一个区间"。每个 `intervals[i]` 与 `intervals[k]` 比较：能重叠就原地扩展 `intervals[k][1]`；否则 `++k` 并把 `intervals[i]` 复制过去。由于 `i > k` 恒成立，写入不会覆盖未处理的数据。最后 `resize(k + 1)` 截断返回。

```cpp
#include <algorithm>
#include <vector>

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        int k = 0;  // 写指针：已合并区间的最后位置
        for (int i = 1; i < (int)intervals.size(); ++i) {
            if (intervals[i][0] <= intervals[k][1]) {
                intervals[k][1] = max(intervals[k][1], intervals[i][1]);
            } else {
                intervals[++k] = intervals[i];
            }
        }
        intervals.resize(k + 1);
        return intervals;
    }
};
```

- ⏱️ 时间复杂度：`O(n log n)`
- 💾 空间复杂度：`O(1)`（不计返回值与排序栈）

## ⚠️ 易错点

- 合并条件是 `cur[0] <= last[1]`（端点相等也算重叠），写成 `<` 会漏掉 `[1,4]` 与 `[4,5]` 这种相邻区间。
- 扩展右端点必须取 `max`：后面的区间可能被完全包含（如 `[1,10]` 之后来一个 `[2,3]`），直接覆盖成 `3` 就把区间缩小了。
- 比较对象是**结果中的最后一个区间**，不是排序后数组中的前一个区间——已被吸收的区间不再参与比较，否则连续链状重叠（`[1,3],[2,5],[4,8]`）会合并不完整。
- 原地写法中 `intervals[++k] = intervals[i]` 必须先自增再赋值，且依赖 `i > k` 恒成立这一事实（首个区间天然就位，`k` 从 `0` 起步）。

---

[← 返回目录](../../README.md)
