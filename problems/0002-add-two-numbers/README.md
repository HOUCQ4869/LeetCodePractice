# 2. 两数相加

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/add-two-numbers/) ｜ [国际站](https://leetcode.com/problems/add-two-numbers/)
>
> 🟡 中等 ｜ 标签：`链表` `数学`

## 📝 题目描述

给你两个**非空**链表，表示两个非负整数。每个节点保存该数的一位数字，并且是**逆序**存储的（个位在链表头部）。请你将这两个数相加，并以相同形式（同样是逆序链表）返回一个表示和的链表。

可以假设这两个数除了 `0` 以外，都不会以 `0` 开头（无前导零）。

**示例 1：**

```
输入：l1 = [2,4,3], l2 = [5,6,4]
输出：[7,0,8]
解释：342 + 465 = 807，逆序存储即 7 -> 0 -> 8。
```

**示例 2：**

```
输入：l1 = [0], l2 = [0]
输出：[0]
```

**示例 3：**

```
输入：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
输出：[8,9,9,9,0,0,0,1]
解释：9999999 + 9999 = 10009998，注意最高位进位产生的新节点。
```

**提示：**

- 每个链表中的节点数在范围 `[1, 100]` 内
- `0 <= Node.val <= 9`
- 题目数据保证列表表示的数字不含前导零

## 💡 题解

### 解法一：转数字再相加（仅作对照，面试不推荐）

**思路**：最"直觉"的做法是把两条链表各转成整数，相加后再逐位拆回链表。但链表最长 100 位，远超 `unsigned long long`（约 20 位）的表示范围，必须借助大整数（如字符串模拟加法）才能正确。这里用字符串处理，仅用于说明为什么不直接转 `long long`。

```cpp
#include <string>

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // 链表本身已是逆序，字符串下标 0 即个位，直接按位加
        string a = toDigits(l1), b = toDigits(l2);
        string sum;
        int carry = 0;
        size_t n = max(a.size(), b.size());
        for (size_t i = 0; i < n || carry; ++i) {
            int s = carry;
            if (i < a.size()) s += a[i] - '0';
            if (i < b.size()) s += b[i] - '0';
            sum.push_back(static_cast<char>('0' + s % 10));
            carry = s / 10;
        }
        // 逐位建链（仍是逆序）
        ListNode dummy(0);
        ListNode* tail = &dummy;
        for (char c : sum) {
            tail->next = new ListNode(c - '0');
            tail = tail->next;
        }
        return dummy.next;
    }

private:
    // 把逆序链表转成"低位在前"的数字串
    string toDigits(ListNode* head) {
        string s;
        for (auto p = head; p != nullptr; p = p->next) {
            s.push_back(static_cast<char>('0' + p->val));
        }
        return s;
    }
};
```

- ⏱️ 时间复杂度：`O(max(m, n))`
- 💾 空间复杂度：`O(max(m, n))`

### 解法二：模拟竖式加法，边遍历边建链（推荐）

**思路**：逆序存储恰好是竖式加法的天然顺序——**个位对齐在最前**。同时遍历两条链表，用 `carry` 记录进位：每位的和为 `l1 当前位 + l2 当前位 + carry`，`% 10` 作为结果位，`/ 10` 更新进位。哪条链表先走完就视其为 0 继续参与运算；两链都走完后若 `carry` 仍为 1，需要**额外补一个值为 1 的节点**（对应示例 3 的最高位）。用哑节点 `dummy` 统一处理结果头，`tail` 始终指向已建部分的末尾，逐位 `new` 节点接上去。

```cpp
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);        // 哑节点，结果头不确定时简化拼接
        ListNode* tail = &dummy;  // 已建结果链的尾
        int carry = 0;            // 进位
        ListNode *p1 = l1, *p2 = l2;
        while (p1 != nullptr || p2 != nullptr || carry != 0) {
            int sum = carry;
            if (p1 != nullptr) {  // 较短的链表按 0 参与
                sum += p1->val;
                p1 = p1->next;
            }
            if (p2 != nullptr) {
                sum += p2->val;
                p2 = p2->next;
            }
            carry = sum / 10;     // 新进位
            tail->next = new ListNode(sum % 10);  // 当前位
            tail = tail->next;
        }
        return dummy.next;
    }
};
```

- ⏱️ 时间复杂度：`O(max(m, n))`
- 💾 空间复杂度：`O(1)`（不计返回值所占空间；结果链最长 `max(m, n) + 1` 个节点）

## ⚠️ 易错点

- 循环条件必须是 `p1 != nullptr || p2 != nullptr || carry != 0`，漏掉 `carry != 0` 会丢失最高位进位（如 `999 + 1 = 1000` 只输出 `000`）。
- 进位要在**取出本位和之后**立即用 `sum / 10` 更新，不能把旧 `carry` 留到下一轮；每位之和最大为 `9 + 9 + 1 = 19`，进位只会是 0 或 1。
- 两链长度可能不同，短的一方要按 0 参与，不能提前退出循环。
- 逆序存储意味着无需先反转链表再算，直接从头就是个位；若误按正序处理会全盘算错。

---

[← 返回目录](../../README.md)
