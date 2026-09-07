# 23. 合并 K 个升序链表

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/merge-k-sorted-lists/) ｜ [国际站](https://leetcode.com/problems/merge-k-sorted-lists/)
>
> 🔴 困难 ｜ 标签：`链表` `堆` `分治`

## 📝 题目描述

给定一个链表数组 `lists`，其中每个元素都是一条**升序**排列的链表。请将所有链表合并成一条**升序**链表，并返回合并后的链表头结点。

**示例 1：**

```
输入：lists = [[1,4,5],[1,3,4],[2,6]]
输出：[1,1,2,3,4,4,5,6]
解释：三条链表的元素交错取出较小者，依次拼接。
```

**示例 2：**

```
输入：lists = []
输出：[]
解释：链表数组本身为空，合并结果为空链表。
```

**示例 3：**

```
输入：lists = [[]]
输出：[]
解释：只有一条空链表，结果仍为空。
```

**提示：**

- `k == lists.length`，`0 <= k <= 10^4`
- `0 <= lists[i].length <= 500`，所有链表长度之和不超过 `10^4`
- `-10^4 <= lists[i][j] <= 10^4`
- `lists[i]` 按**升序**排列

## 💡 题解

### 解法一：逐一两两合并

**思路**：维护一个结果链，把 `k` 条链依次合并进来，每次都复用 21 题"合并两个有序链表"。写法最直接，但每条链的结点几乎每次合并都要被重扫一遍：链均长 `n` 时总代价约 `n·(1 + 2 + … + k) = O(k²n)`，即 `O(kN)`（`N` 为总结点数）。在 `k` 与链长都大的场合（本题 `k` 可达 `10^4`）有超时风险，仅作对比基线。

```cpp
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* merged = nullptr;
        for (ListNode* lst : lists) {
            merged = mergeTwo(merged, lst);  // 结果链与下一条合并
        }
        return merged;
    }

private:
    ListNode* mergeTwo(ListNode* a, ListNode* b) {
        ListNode dummy(0);
        ListNode* tail = &dummy;
        while (a != nullptr && b != nullptr) {
            if (a->val <= b->val) {
                tail->next = a;
                a = a->next;
            } else {
                tail->next = b;
                b = b->next;
            }
            tail = tail->next;
        }
        tail->next = (a != nullptr) ? a : b;
        return dummy.next;
    }
};
```

- ⏱️ 时间复杂度：`O(k²n)`（即 `O(kN)`，`N` 为总结点数）
- 💾 空间复杂度：`O(1)`

### 解法二：小根堆

**思路**：`k` 条链各自有序，那么**全局最小值一定出自某条链的头结点**。把 `k` 个头结点放进小根堆，每轮弹出全局最小接到结果尾部，并把它的后继（若非空）入堆补位。堆中始终至多 `k` 个结点，每个结点进出堆各一次，单次代价 `O(log k)`。注意 `priority_queue` 默认是大根堆，比较器写成 `a->val > b->val` 才是小根语义。

```cpp
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto cmp = [](ListNode* a, ListNode* b) { return a->val > b->val; };
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);
        for (ListNode* lst : lists) {
            if (lst != nullptr) {
                pq.push(lst);  // 空链不入堆
            }
        }
        ListNode dummy(0);
        ListNode* tail = &dummy;
        while (!pq.empty()) {
            ListNode* node = pq.top();
            pq.pop();
            tail->next = node;  // 摘下全局最小
            tail = tail->next;
            if (node->next != nullptr) {
                pq.push(node->next);  // 后继补位
            }
        }
        return dummy.next;
    }
};
```

- ⏱️ 时间复杂度：`O(N log k)`
- 💾 空间复杂度：`O(k)`（堆）

### 解法三：分治合并（推荐）

**思路**：把"合并 `k` 条"拆成"合并左半 + 合并右半"再两两拼接：`mergeRange(lo, hi)` 递归对半分治，区间只剩一条链时直接返回，否则用 21 题的合并拼起来。与解法一的区别在于合并顺序——每条链只参与 `log k` 次合并而非 `k` 次，每层每个结点只被扫一遍、共 `log k` 层。与堆解法同为 `O(N log k)`，但没有每结点的堆开销，递归栈也仅 `O(log k)`，实际常数更小。

```cpp
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) {
            return nullptr;
        }
        return mergeRange(lists, 0, static_cast<int>(lists.size()) - 1);
    }

private:
    // 合并 lists[lo..hi] 范围内的所有链表
    ListNode* mergeRange(vector<ListNode*>& lists, int lo, int hi) {
        if (lo == hi) {
            return lists[lo];  // 只剩一条（可能是空链）
        }
        int mid = lo + (hi - lo) / 2;
        return mergeTwo(mergeRange(lists, lo, mid), mergeRange(lists, mid + 1, hi));
    }

    ListNode* mergeTwo(ListNode* a, ListNode* b) {
        ListNode dummy(0);
        ListNode* tail = &dummy;
        while (a != nullptr && b != nullptr) {
            if (a->val <= b->val) {
                tail->next = a;
                a = a->next;
            } else {
                tail->next = b;
                b = b->next;
            }
            tail = tail->next;
        }
        tail->next = (a != nullptr) ? a : b;
        return dummy.next;
    }
};
```

- ⏱️ 时间复杂度：`O(N log k)`
- 💾 空间复杂度：`O(log k)`（递归调用栈）

## ⚠️ 易错点

- 两种边界都要照顾：`lists` 本身为空（`k = 0`），以及数组里装着空链表（`lists[i] = []`）；分治版 `lo == hi` 直接返回该链，天然兼容空链。
- 堆解法的比较器方向易写反：`priority_queue` 默认大根堆，参数须为 `a->val > b->val` 才是小根堆，写反后弹出的是全局最大值。
- 堆解法初始化时要把空链过滤掉，否则 `pq.top()` 取出 `nullptr` 后解引用崩溃。
- 逐一合并是 `O(kN)`，在 `k = 10^4`、链均长较大时会超时；面试应至少给出堆或分治解法。

---

[← 返回目录](../../README.md)
