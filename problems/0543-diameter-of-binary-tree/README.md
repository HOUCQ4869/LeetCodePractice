# 543. 二叉树的直径

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/diameter-of-binary-tree/) ｜ [国际站](https://leetcode.com/problems/diameter-of-binary-tree/)
>
> 🟢 简单 ｜ 标签：`树` `深度优先搜索`

## 📝 题目描述

给你一棵二叉树的根节点 `root`，返回该树的**直径**：树中**任意两节点之间最长路径的长度**（路径上的**边数**）。这条路径可能经过也可能不经过根节点。两节点之间路径的长度由它们之间的边数表示。

**示例 1：**

```
输入：root = [1,2,3,4,5]
输出：3
解释：树为 1 的孩子 2、3，2 的孩子 4、5。
     最长路径为 4 -> 2 -> 1 -> 3 或 5 -> 2 -> 1 -> 3，含 3 条边。
```

**示例 2：**

```
输入：root = [2,3,null,1]
输出：2
解释：最长路径为 1 -> 3 -> 2，含 2 条边。
```

**提示：**

- 树中节点数目在范围 `[1, 10^4]` 内
- `-100 <= Node.val <= 100`

## 💡 题解

### 解法一：枚举拐点（自顶向下暴力递归）

**思路**：任意一条路径在树里一定有一个"最高点"（即离根最近的节点，路径在此拐弯），我们称它为拐点。当拐点是 `node` 时，最优路径是"左子树中最深的叶子 → node → 右子树中最深的叶子"，长度为 `左子树深度 + 右子树深度`（深度按节点数计，相加恰好等于边数）。于是对每个节点分别求左右深度取和，再递归处理左右子树，三者取最大即为直径。缺点是每层都重复计算深度，最坏（链状树）退化为 `O(n²)`。

```cpp
#include <algorithm>

class Solution {
    // 以 node 为根的最大深度（节点数）
    int depth(TreeNode* node) {
        if (node == nullptr) return 0;
        return max(depth(node->left), depth(node->right)) + 1;
    }

public:
    int diameterOfBinaryTree(TreeNode* root) {
        if (root == nullptr) return 0;
        int through = depth(root->left) + depth(root->right);  // 拐点在 root
        int sub = max(diameterOfBinaryTree(root->left),       // 拐点在子树中
                      diameterOfBinaryTree(root->right));
        return max(through, sub);
    }
};
```

- ⏱️ 时间复杂度：`O(n²)`（链状树最坏情形；平衡树为 `O(n log n)`）
- 💾 空间复杂度：`O(h)`（递归栈）

### 解法二：一趟后序 DFS + 成员变量

**思路**：解法一慢在"求深度"和"枚举拐点"是两趟递归。其实算深度的递归**本身就会路过每个拐点**：在后序计算 `depth(node)` 时，左右子树的深度 `l`、`r` 都已拿到，顺手用 `l + r` 更新全局最大直径 `ans` 即可，深度照常返回 `max(l, r) + 1` 给父节点使用。每个节点只访问一次，时间降到 `O(n)`。注意直径用**边数**计，而深度按**节点数**计，`l + r`（节点数相加）恰好等于路径的边数，无需 `+1` 或 `-1` 修正。

```cpp
#include <algorithm>

class Solution {
    int ans = 0;  // 全局最大直径（边数）

    int depth(TreeNode* node) {  // 返回以 node 为根的最大深度（节点数）
        if (node == nullptr) return 0;
        int l = depth(node->left);
        int r = depth(node->right);
        ans = max(ans, l + r);  // 拐点在 node 的路径长 = l + r 条边
        return max(l, r) + 1;
    }

public:
    int diameterOfBinaryTree(TreeNode* root) {
        depth(root);
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(h)`（递归栈）

### 解法三：后序 DFS 返回「深度 + 直径」二元组（推荐）

**思路**：不借助类成员变量，让递归函数直接返回一个 `pair`：`{该子树的最大深度（节点数）, 该子树内的最大直径（边数）}`。合并时：深度为 `max(左深度, 右深度) + 1`；直径在"左子树直径、右子树直径、横跨当前节点的 `左深度 + 右深度`"三者中取最大。无共享状态，逻辑封装在函数内，多测例下最安全，是可复用的标准写法。

```cpp
#include <algorithm>
#include <utility>

class Solution {
    // 返回 {子树最大深度（节点数）, 子树内最大直径（边数）}
    pair<int, int> dfs(TreeNode* node) {
        if (node == nullptr) return {0, 0};
        auto [ld, lans] = dfs(node->left);
        auto [rd, rans] = dfs(node->right);
        int depth = max(ld, rd) + 1;
        int best = max({lans, rans, ld + rd});  // 左、右、横跨 node 三种情况
        return {depth, best};
    }

public:
    int diameterOfBinaryTree(TreeNode* root) {
        return dfs(root).second;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(h)`（递归栈）

## ⚠️ 易错点

- 直径统计的是**边数**不是节点数：深度按节点数定义时，`左深度 + 右深度` 恰为边数，直接相加即可；若误写成 `l + r + 1` 会多算一条边（如单节点树应返回 `0`）。
- 最长路径**不一定经过根节点**：只在根处算一次 `左深度 + 右深度` 会漏掉拐点在深层的情况，必须对每个节点都尝试更新。
- 用成员变量（解法二）时注意它在多个测试用例间复用，入口处必须保证 `ans` 从 `0` 重新开始（LeetCode 会复用同一个 `Solution` 实例时尤需留意初始化位置）。
- 拐点路径是"左子树最深叶子到右子树最深叶子"，不能只沿一侧走；`max(l, r)` 是返回给父节点的深度，不是本节点的候选直径，两个量不要混用。

---

[← 返回目录](../../README.md)
