# 124. 二叉树中的最大路径和

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/binary-tree-maximum-path-sum/) ｜ [国际站](https://leetcode.com/problems/binary-tree-maximum-path-sum/)
>
> 🔴 困难 ｜ 标签：`树` `深度优先搜索`

## 📝 题目描述

二叉树中的**路径**被定义为一条节点序列，序列中每对相邻节点之间都存在一条边；同一个节点在一条路径序列中**至多出现一次**。路径**至少包含一个节点**，且不一定经过根节点。

**路径和**是路径中各节点值的总和。给定二叉树的根节点 `root`，返回其**最大路径和**。

**示例 1：**

```
输入：root = [1,2,3]
输出：6
解释：最优路径是 2 -> 1 -> 3，路径和为 2 + 1 + 3 = 6。
```

**示例 2：**

```
输入：root = [-10,9,20,null,null,15,7]
输出：42
解释：最优路径是 15 -> 20 -> 7，路径和为 15 + 20 + 7 = 42。
```

树形结构：根为 `-10`，左子为单节点 `9`，右子 `20`（孩子 `15`、`7`）。最优路径完全位于右子树内部，不经过根。

**示例 3：**

```
输入：root = [-3]
输出：-3
解释：只有一个节点，路径就是它自身。
```

**提示：**

- 树中节点数目范围 `[1, 3 * 10^4]`
- `-1000 <= Node.val <= 1000`

## 💡 题解

### 解法一：后序 DFS（分情况讨论）

**思路**：任何路径都有一个「最高点」——路径上离根最近的节点。路径由最高点向左下、右下各伸一条**链**（两条链长度均可为 0，但路径至少含最高点自身）。定义 `chain(x)` 为以 `x` 为顶端、只向下延伸、至少含 `x` 的最大链和，它等于 `x->val` 加上「不延伸 / 延左链 / 延右链」三者中的最大值；而以 `x` 为最高点的最优路径和为 `x->val + max(chain(l), 0) + max(chain(r), 0)`。后序遍历：先递归求出左右子树的 `chain`，用上式更新全局答案，再返回 `chain(x)` 供父节点使用。注意「空子树不存在链」与「不延伸」是两种情况，需用负无穷哨兵区分；为避免哨兵参与运算溢出，内部用 `long long`。

```cpp
#include <algorithm>
#include <climits>

class Solution {
    long long ans = LLONG_MIN;

    // 返回以 node 为顶端、只向下延伸、至少含 node 自身的最大链和
    long long chain(TreeNode* node) {
        if (!node) return LLONG_MIN;              // 空子树：不存在可选的链
        long long v = node->val;
        long long l = chain(node->left);
        long long r = chain(node->right);
        long long lGain = (l == LLONG_MIN) ? 0 : max(l, 0LL);  // 左链增益（负则弃）
        long long rGain = (r == LLONG_MIN) ? 0 : max(r, 0LL);  // 右链增益（负则弃）
        ans = max(ans, v + lGain + rGain);        // 以 node 为最高点的最优路径
        long long best = v;                       // 向上单边延伸：不延伸 / 带左 / 带右
        if (l != LLONG_MIN) best = max(best, v + l);
        if (r != LLONG_MIN) best = max(best, v + r);
        return best;
    }

public:
    int maxPathSum(TreeNode* root) {
        chain(root);
        return (int)ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(h)` 递归栈，最坏（链状树）为 `O(n)`

### 解法二：负贡献归零（推荐）

**思路**：解法一繁琐的根源在于要区分「子树不存在」与「链和为负」。把两者统一：定义 `gain(x)` 为以 `x` 为一端、向下延伸的链带来的**增益**——空节点返回 `0`，负链与 `0` 取 `max` 即被舍弃，两种情况自然合并。递归到 `node` 时先取左右增益 `l = max(gain(left), 0)`、`r = max(gain(right), 0)`，用 `node->val + l + r` 更新全局答案（拐点在当前节点，两边都能要），返回 `node->val + max(l, r)`（向父节点上传只能带一边）。代码极简，一趟完成。

```cpp
#include <algorithm>
#include <climits>

class Solution {
    int ans = INT_MIN;

    // 返回以 node 为一端、只向下延伸的最大链和（至少含 node，可为负）
    int gain(TreeNode* node) {
        if (!node) return 0;
        int l = max(gain(node->left), 0);    // 左链负贡献直接舍弃
        int r = max(gain(node->right), 0);   // 右链负贡献直接舍弃
        ans = max(ans, node->val + l + r);   // 以 node 为拐点的最优路径
        return node->val + max(l, r);        // 向上只能延伸到一边
    }

public:
    int maxPathSum(TreeNode* root) {
        gain(root);
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(h)` 递归栈，最坏（链状树）为 `O(n)`

## ⚠️ 易错点

- 路径**至少包含一个节点**：答案初值必须是 `INT_MIN`，不能是 `0`，否则全负树（如 `[-3]`）会错误地返回 `0`。
- 向父节点返回的链**只能带一边**（`val + max(l, r)`）；两边都带就成了「分叉」，违反路径定义。只有以拐点身份更新答案时才允许两边都加。
- 子链和为负时要舍弃（与 `0` 取 `max`），否则负链会拖累最优路径。
- 值域 `±1000`、节点至多 `3 × 10^4`，最大路径和约 `3 × 10^7`，`int` 足够；若数据范围扩大需改用 `long long`。

---

[← 返回目录](../../README.md)
