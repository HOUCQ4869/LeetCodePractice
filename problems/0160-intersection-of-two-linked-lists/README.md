# 160. 相交链表

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/intersection-of-two-linked-lists/) ｜ [国际站](https://leetcode.com/problems/intersection-of-two-linked-lists/)
>
> 🟢 简单 ｜ 标签：`链表` `双指针`

## 📝 题目描述

给你两个单链表的头节点 `headA` 和 `headB`，请你找出并返回两个单链表相交的起始节点。如果两个链表**不存在**相交节点，返回 `nullptr`。

题目保证整个链式结构中**不存在环**。函数返回结果后，链表必须**保持其原始结构**。

**示例 1：**

```
输入：intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3
输出：Intersected at '8'
解释：相交节点的值为 8（注意，如果两个链表相交则不能为 0）。
各自从头出发：A 走 2 个节点到达相交处，B 走 3 个节点到达相交处。
```

**示例 2：**

```
输入：intersectVal = 2, listA = [1,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1
输出：Intersected at '2'
解释：从 A 的头节点走 3 步、从 B 的头节点走 1 步即可到达值同为 2 的相交节点。
```

**示例 3：**

```
输入：intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
输出：null
解释：两链表长度不同且末尾不同，不相交，返回 nullptr。
```

**提示：**

- `listA` 的节点数目范围是 `[1, 3 * 10^4]`
- `listB` 的节点数目范围是 `[1, 3 * 10^4]`
- `1 <= Node.val <= 10^5`
- `intersectVal` 为 `0` 或**不在**两个链表中的值时表示两链表不相交
- 题目**保证**整个链式结构中不存在环

## 💡 题解

### 解法一：哈希表记录已访问节点

**思路**：相交意味着从某个节点开始，两条链表共享**同一段后缀**（是同一个节点对象，而不只是值相等）。先把链表 A 的每个节点地址存入哈希集合，再遍历链表 B，第一个出现在集合中的节点就是相交起点。判断的是**指针地址**而非节点值。

```cpp
#include <unordered_set>

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_set<ListNode*> visited;  // 记录 A 中出现过的节点地址
        for (auto p = headA; p != nullptr; p = p->next) {
            visited.insert(p);
        }
        for (auto p = headB; p != nullptr; p = p->next) {
            if (visited.count(p)) {  // 第一个共同节点即相交起点
                return p;
            }
        }
        return nullptr;  // 不相交
    }
};
```

- ⏱️ 时间复杂度：`O(m + n)`
- 💾 空间复杂度：`O(m)`

### 解法二：双指针两次遍历（推荐）

**思路**：设 A、B 的长度分别为 `a`、`b`，公共部分长 `c`，则 A 的独有前缀长 `a - c`，B 的独有前缀长 `b - c`。让指针 `pA` 从 `headA` 出发、`pB` 从 `headB` 出发同步后移；`pA` 走到 A 末尾后转到 `headB` 继续走，`pB` 走到 B 末尾后转到 `headA` 继续走。两指针各自总路程均为 `a + b`，且**会在走过 `a + b - c` 步时同时到达相交起点**（若不相交则同时变为 `nullptr`，循环同样结束）。这本质上是让长链表先"消耗"掉多出来的前缀。

```cpp
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headA == nullptr || headB == nullptr) {
            return nullptr;
        }
        ListNode *pA = headA, *pB = headB;
        while (pA != pB) {  // 相遇（或同时为空）时退出
            // pA 走到 A 尾后切换到 B；仍在 A 中则后移一步
            pA = (pA == nullptr) ? headB : pA->next;
            pB = (pB == nullptr) ? headA : pB->next;
        }
        return pA;  // 相交则为目标节点；不相交则为 nullptr
    }
};
```

- ⏱️ 时间复杂度：`O(m + n)`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 相交的判定依据是**节点地址相同**，不是节点值相等；用值做判断会在两链表有相同值的不相交部分时误判。
- 双指针切换时判断的是 `pA == nullptr`（已走过尾节点）而不是 `pA->next == nullptr`，后者会在尾节点处多停一步导致错位。
- 两链表不相交时双指针会在同一轮同时变为 `nullptr`，`while (pA != pB)` 自然退出并返回 `nullptr`，不会死循环。
- 题目要求不能修改链表结构，不能用"把 A 的尾节点接到 B 头上制造环"之类的破坏性做法。

---

[← 返回目录](../../README.md)
