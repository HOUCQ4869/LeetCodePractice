# 155. 最小栈

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/min-stack/) ｜ [国际站](https://leetcode.com/problems/min-stack/)
>
> 🟢 简单 ｜ 标签：`栈` `设计`

## 📝 题目描述

设计一个支持 `push`、`pop`、`top` 操作，并能在**常数时间**内检索到最小元素的栈：

- `MinStack()` 初始化栈对象；
- `void push(int val)` 将元素 `val` 压入栈；
- `void pop()` 删除栈顶元素；
- `int top()` 获取栈顶元素；
- `int getMin()` 获取栈中的最小元素。

要求每个函数的时间复杂度均为 `O(1)`。

**示例 1：**

```text
输入：
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

输出：
[null,null,null,null,-3,null,0,-2]

解释：
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   // 返回 -3
minStack.pop();
minStack.top();      // 返回 0
minStack.getMin();   // 返回 -2
```

**提示：**

- `-2^31 <= val <= 2^31 - 1`
- `push`、`pop`、`top`、`getMin` 的总调用次数不超过 `3 * 10^4`
- 调用 `pop`、`top`、`getMin` 时栈保证非空

## 💡 题解

### 解法一：单栈存「值 + 当前最小值」对

**思路**：让栈里的每个元素携带额外信息：压栈时记录"**压入这个值之后**栈内的最小值"，即 `min(val, 压栈前的最小值)`，存成 `pair<值, 当前最小值>`。这样任意时刻的栈内最小值就是栈顶对中的第二个分量，弹栈时历史最小值天然随下层元素保留，无需额外回退逻辑。

```cpp
#include <stack>
#include <utility>

class MinStack {
public:
    MinStack() {}

    void push(int val) {
        // 压栈后的最小值 = 新值与之前最小值取较小者
        int curMin = st.empty() ? val : min(val, st.top().second);
        st.push({val, curMin});
    }

    void pop() {
        st.pop();
    }

    int top() {
        return st.top().first;
    }

    int getMin() {
        return st.top().second;  // 栈顶即当前栈内最小值
    }

private:
    stack<pair<int, int>> st;  // {当前值, 压栈后的栈内最小值}
};
```

- ⏱️ 时间复杂度：`O(1)`（每个操作）
- 💾 空间复杂度：`O(n)`

### 解法二：辅助栈（推荐）

**思路**：用一个**主栈**正常存值，再配一个**辅助栈**专门维护最小值：`push` 时若新值 `<=` 辅助栈顶（或辅助栈为空）才压入辅助栈；`pop` 时若两栈栈顶相等则辅助栈同步弹出；`getMin` 直接返回辅助栈顶。辅助栈从底到顶单调不增，栈顶永远是当前最小值。注意入栈条件用 `<=`（而非 `<`），保证**重复出现的最小值在辅助栈中个数对齐**，弹出时才不会提前枯竭。

```cpp
#include <stack>

class MinStack {
public:
    MinStack() {}

    void push(int val) {
        st.push(val);
        // 用 <= 保证重复出现的最小值都入辅助栈，弹出时数量才能对上
        if (minSt.empty() || val <= minSt.top()) {
            minSt.push(val);
        }
    }

    void pop() {
        if (st.top() == minSt.top()) {
            minSt.pop();  // 弹出的恰是当前最小值，辅助栈同步弹出
        }
        st.pop();
    }

    int top() {
        return st.top();
    }

    int getMin() {
        return minSt.top();  // 辅助栈顶即当前栈内最小值
    }

private:
    stack<int> st;     // 主栈
    stack<int> minSt;  // 辅助栈：与主栈同步维护最小值
};
```

- ⏱️ 时间复杂度：`O(1)`（每个操作）
- 💾 空间复杂度：`O(n)`

## ⚠️ 易错点

- 只用一个普通变量记录最小值不可行：最小值被弹出后无法回退到"次小值"，`getMin` 就错了。
- 辅助栈的入栈条件必须是 `val <= minSt.top()`：若写成 `<`，连续压入多个相同的最小值（如 `5, 5, 5`）时辅助栈只存一份，弹出一次后最小值就"丢失"了。
- `pop` 时要先比较两栈顶是否相等、再决定是否弹辅助栈，且比较必须在主栈弹出之前完成。
- 本题保证空栈时不会调用 `pop` / `top` / `getMin`，因此无需大量判空；但辅助栈在 `push` 第一个元素前为空，判空逻辑不能漏。

---

[← 返回目录](../../README.md)
