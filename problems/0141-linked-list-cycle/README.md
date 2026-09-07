# 141. 环形链表

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/linked-list-cycle/) ｜ [国际站](https://leetcode.com/problems/linked-list-cycle/)
>
> 🟢 简单 ｜ 标签：`链表` `双指针`

## 📝 题目描述

给你一个链表的头节点 `head`，判断链表中**是否有环**。

如果链表中有某个节点，可以通过连续跟踪 `next` 指针再次到达该节点，则链表中存在环。参数 `pos` 表示链表尾接到链表中的位置（从 0 开始索引），**仅用于标识环的存在，不作为参数传入**；链表无环时 `pos` 为 `-1`。

**进阶**：你能用 `O(1)`（即常数级）内存解决此题吗？

**示例 1：**

```
输入：head = [3,2,0,-4], pos = 1
输出：true
解释：链表中有一个环，其尾部连接到第二个节点（索引 1）。
```

**示例 2：**

```
输入：head = [1,2], pos = 0
输出：true
解释：链表中有一个环，其尾部连接到第一个节点（索引 0）。
```

**示例 3：**

```
输入：head = [1], pos = -1
输出：false
解释：链表中没有环。
```

**提示：**

- 链表中节点的数目范围是 `[0, 10^4]`
- `-10^5 <= Node.val <= 10^5`
- `pos` 为 `-1` 或者链表中的一个**有效索引**

## 💡 题解

### 解法一：哈希表记录访问过的节点

**思路**：从头遍历链表，把每个**节点地址**存入哈希集合。遇到两种情况结束：某个节点已在集合中出现过——说明绕回了已访问的节点，有环；或者走到 `nullptr`——说明到达链表自然结尾，无环。注意不能以节点值判重，值相同不代表是同一个节点。

```cpp
#include <unordered_set>

class Solution {
public:
    bool hasCycle(ListNode *head) {
        unordered_set<ListNode*> visited;  // 已访问节点地址
        for (auto p = head; p != nullptr; p = p->next) {
            if (!visited.insert(p).second) {
                return true;  // 第二次访问同一节点，有环
            }
        }
        return false;  // 走到 nullptr，无环
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`

### 解法二：Floyd 快慢指针（推荐）

**思路**：把链表想象成带环的跑道：慢指针每次走 1 步、快指针每次走 2 步。若无环，快指针会率先到达 `nullptr`，循环结束返回 `false`；若有环，两指针进入环后都不会退出，且快指针相对慢指针每轮**多走 1 步**，差距逐轮缩小，最终必然追上并相遇（类似操场套圈），返回 `true`。这就是 Floyd 判圈算法，只用两个指针，满足进阶的 `O(1)` 空间要求。

```cpp
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *slow = head;  // 每次走 1 步
        ListNode *fast = head;  // 每次走 2 步
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;        // 慢走一步
            fast = fast->next->next;  // 快走两步
            if (slow == fast) {       // 快追上慢，说明有环
                return true;
            }
        }
        return false;  // fast 到达 nullptr，链表有尾，无环
    }
};
```

- ⏱️ 时间复杂度：`O(n)`（无环走 `n/2` 轮；有环时进环前最多 `n` 步、环内差距每轮缩小 1，总共线性）
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 循环条件必须同时检查 `fast != nullptr && fast->next != nullptr`，漏掉前者在尾节点是奇偶末尾时会解引用空指针。
- `fast->next->next` 走两步时**不要先移动 slow 再比较**也别忘了初始时两指针同起点、循环内先移动后比较，否则首轮就误判相等。
- 哈希表解法判重依据是节点地址（指针值），用 `val` 判重在值重复时误报。
- 空链表 `head == nullptr` 应直接无环返回，快慢写法天然覆盖，但若写成 `do-while` 结构需单独处理。

---

[← 返回目录](../../README.md)
