# 142. 环形链表 II

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/linked-list-cycle-ii/) ｜ [国际站](https://leetcode.com/problems/linked-list-cycle-ii/)
>
> 🟡 中等 ｜ 标签：`链表` `双指针`

## 📝 题目描述

给定一个链表的头节点 `head`，返回链表**开始入环的第一个节点**。如果链表无环，则返回 `nullptr`。

如果链表中有某个节点，可以通过连续跟踪 `next` 指针再次到达该节点，则链表中存在环。参数 `pos` 表示链表尾接到链表中的位置（从 0 开始索引），仅用于标识环的存在，**不作为参数传入**。**不允许修改**链表。

**进阶**：你是否可以使用 `O(1)` 空间解决此题？

**示例 1：**

```
输入：head = [3,2,0,-4], pos = 1
输出：返回索引为 1 的链表节点（值为 2 的节点）
解释：链表中有一个环，其尾部连接到第二个节点。
```

**示例 2：**

```
输入：head = [1,2], pos = 0
输出：返回索引为 0 的链表节点
解释：链表中有一个环，其尾部连接到第一个节点。
```

**示例 3：**

```
输入：head = [1], pos = -1
输出：null
解释：链表中没有环。
```

**提示：**

- 链表中节点的数目范围在 `[0, 10^4]` 内
- `-10^5 <= Node.val <= 10^5`
- `pos` 的值为 `-1` 或者链表中的一个有效索引

## 💡 题解

### 解法一：哈希表找第一个重复节点

**思路**：沿 `next` 指针遍历，把每个**节点地址**依次插入哈希集合。第一个插入失败的节点（即集合中已存在的节点）就是绕回来的入环点，直接返回；若一路走到 `nullptr`，说明链表无环，返回 `nullptr`。思路直观，但需要 `O(n)` 额外空间。

```cpp
#include <unordered_set>

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        unordered_set<ListNode*> visited;  // 依次出现过的节点地址
        for (auto p = head; p != nullptr; p = p->next) {
            if (!visited.insert(p).second) {
                return p;  // 第一个重复出现的节点即入环点
            }
        }
        return nullptr;  // 走到 nullptr，无环
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`

### 解法二：Floyd 快慢指针 + 数学推导（推荐）

**思路**：在 141 题 Floyd 判圈的基础上多推一步。设头到入环点距离为 `a`，入环点到相遇点距离为 `b`，环剩余部分长 `c`（环长 `b + c`）。相遇时：
- 慢指针走了 `a + b`；
- 快指针走的路程是慢的两倍：`a + b + k(b + c)`（快指针在环里多绕了 `k ≥ 1` 圈）。

由 `2(a + b) = a + b + k(b + c)` 化简得 `a = (k - 1)(b + c) + c`。这说明：**从头节点走 `a` 步、从相遇点走 `c + (k-1) 圈` 步，会恰好同时到达入环点**。于是相遇后让一个指针回到 `head`，两指针改为每次各走 1 步，再次相遇的位置就是入环点。全程只用常数个指针。

```cpp
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        // 第一阶段：快慢指针判环并找到相遇点
        ListNode *slow = head;
        ListNode *fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;        // 慢走 1 步
            fast = fast->next->next;  // 快走 2 步
            if (slow == fast) {       // 有环，在环内相遇
                // 第二阶段：一个指针回头，同速前进找入环点
                ListNode *p = head;
                while (p != slow) {   // 再次相遇处即入环点
                    p = p->next;
                    slow = slow->next;
                }
                return p;
            }
        }
        return nullptr;  // fast 到达 nullptr，无环
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 第二阶段两个指针必须都改为**每次走 1 步**，快指针若仍走 2 步推导不再成立。
- 相遇点不等于入环点：两指针在环内某处相遇，必须再走第二阶段才能定位入环口。
- 无环时快慢循环要能正常退出并返回 `nullptr`，循环条件 `fast != nullptr && fast->next != nullptr` 两个都不能少。
- 题目不允许修改链表，不能用"给访问过的节点打标记 / 断链"等破坏性做法。
- 数学推导中 `a = (k-1)(b+c) + c` 依赖快指针路程恰为慢指针 2 倍，若改成快走 3 步公式需重推（且可能跳过相遇）。

---

[← 返回目录](../../README.md)
