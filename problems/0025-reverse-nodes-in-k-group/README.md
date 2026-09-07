# 25. K 个一组翻转链表

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/reverse-nodes-in-k-group/) ｜ [国际站](https://leetcode.com/problems/reverse-nodes-in-k-group/)
>
> 🔴 困难 ｜ 标签：`链表` `递归`

## 📝 题目描述

给定链表的头结点 `head` 和整数 `k`，每 `k` 个结点一组对链表进行翻转，返回修改后的链表头结点。

- 必须真实翻转结点（修改 `next` 指针），**不能只改结点内部的值**；
- 若结点总数不是 `k` 的整数倍，最后剩余不足 `k` 个的结点**保持原有顺序**。

**进阶**：你可以设计一个只使用 `O(1)` 额外空间的算法来解决此问题吗？

**示例 1：**

```
输入：head = [1,2,3,4,5], k = 2
输出：[2,1,4,3,5]
解释：前 4 个结点两两一组翻转，末尾的 5 落单，保持原序。
```

**示例 2：**

```
输入：head = [1,2,3,4,5], k = 3
输出：[3,2,1,4,5]
解释：前三结点一组翻转为 3 -> 2 -> 1；剩余两个不足 3，保持 4 -> 5。
```

**提示：**

- 链表中的结点数目 `n` 满足 `1 <= n <= 5000`
- `0 <= Node.val <= 1000`
- `1 <= k <= n`

## 💡 题解

### 解法一：递归

**思路**：函数的语义定义为"把从 `head` 起的链表按 k 个一组翻转，返回新头"。每层先向后探测 `k` 步：途中遇到 `nullptr` 说明剩余不足 `k` 个，直接原样返回 `head`。若凑够了一组，用**头插法**翻转这 `k` 个结点——`prev` 初始化为"下一组的头"（而不是 `nullptr`），这样本组翻转完天然衔接下一组；最后让原组头（现组尾）接上"递归处理剩余部分"的结果即可。

```cpp
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        // 探测剩余结点是否凑够 k 个
        ListNode* check = head;
        for (int i = 0; i < k; ++i) {
            if (check == nullptr) {
                return head;  // 不足 k 个，保持原序
            }
            check = check->next;
        }
        // check 指向下一组的头；头插法翻转本组 k 个结点
        ListNode* prev = check;
        ListNode* cur = head;
        for (int i = 0; i < k; ++i) {
            ListNode* nxt = cur->next;
            cur->next = prev;  // 依次把结点反向接到 prev 前
            prev = cur;
            cur = nxt;
        }
        head->next = reverseKGroup(check, k);  // 原组头（现组尾）接上已处理的剩余部分
        return prev;  // prev 为本组翻转后的新头
    }
};
```

- ⏱️ 时间复杂度：`O(n)`，每个结点被探测、翻转各一次
- 💾 空间复杂度：`O(n/k)`，递归栈深度等于组数（题目进阶要求下的考量见解法二）

### 解法二：迭代（推荐）

**思路**：与递归同构，改为循环推进。`groupPrev` 指向当前组的前驱（哑节点起步，统一处理第一组）。每轮：① 从 `groupPrev` 向后探 `k` 步，途中断链说明剩余不足 `k` 个，整体收工返回；② 记下原组头 `groupHead` 与下一组的头 `nextGroup`；③ 头插翻转本组区间 `[groupHead, check]`，`prev` 从 `nextGroup` 起步保证组间不断链；④ 前驱接上本组新头，而原组头翻转变成了组尾，正好作为下一轮的 `groupPrev`。全程只用常数个指针，满足进阶的 `O(1)` 空间要求。

```cpp
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode* groupPrev = &dummy;  // 当前组的前驱

        for (;;) {
            // ① 探测本组是否凑够 k 个结点
            ListNode* check = groupPrev;
            for (int i = 0; i < k; ++i) {
                check = check->next;
                if (check == nullptr) {
                    return dummy.next;  // 剩余不足 k 个，整体结束
                }
            }
            ListNode* groupHead = groupPrev->next;  // 原组头，翻转后成为组尾
            ListNode* nextGroup = check->next;      // 下一组的头
            // ② 头插法翻转本组：prev 从 nextGroup 起步，保证与下一组衔接
            ListNode* prev = nextGroup;
            ListNode* cur = groupHead;
            while (cur != nextGroup) {
                ListNode* nxt = cur->next;
                cur->next = prev;
                prev = cur;
                cur = nxt;
            }
            // ③ 前驱接本组新头；原组头变为组尾，充当下一轮前驱
            groupPrev->next = prev;
            groupPrev = groupHead;
        }
    }
};
```

- ⏱️ 时间复杂度：`O(n)`，探测与翻转加起来每个结点至多被访问两次
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- **先探测后翻转**：不足 `k` 个的尾部必须保持原序，翻转之后才发现不够就回不去了。
- 头插翻转一组时，`prev` 的初值应是**下一组的头**而非 `nullptr`——若置空再想衔接就得再扫一遍，两处写法极易混淆。
- 组与组之间的两条连接线都要接：前驱 `groupPrev->next` 指向本组新头；本组翻转后的尾（原组头）指向下一组。漏接任何一条都会断链。
- 下一轮的前驱是**原组头**（翻转后的组尾），误用新头会把已处理的结点再处理一遍，导致死循环。
- 题目禁止只交换结点值；虽然 `n <= 5000` 时交换值也能过判题，但违背考察目的，且无法推广到要求 `O(1)` 空间的场景。

---

[← 返回目录](../../README.md)
