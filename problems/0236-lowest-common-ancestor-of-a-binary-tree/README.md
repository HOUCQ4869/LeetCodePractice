# 236. 二叉树的最近公共祖先

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/) ｜ [国际站](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/)
>
> 🟡 中等 ｜ 标签：`树` `深度优先搜索`

## 📝 题目描述

给定一棵二叉树的根节点 `root` 和树中两个不同节点 `p`、`q`，找到它们的**最近公共祖先（LCA）**。

最近公共祖先的定义：对于有根树 `T` 的两个节点 `p`、`q`，最近公共祖先是一个节点 `x`，满足 `x` 是 `p` 和 `q` 的祖先，且 `x` 的深度尽可能大（**一个节点也可以是它自己的祖先**）。

注意：本题的二叉树**不是**二叉搜索树，节点值没有大小关系，只能靠结构判断。

**示例 1：**

```
输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
输出：3
解释：节点 5 和 1 的最近公共祖先是 3。
```

树形结构：根为 `3`；左子 `5`（孩子 `6`、`2`，其中 `2` 的孩子为 `7`、`4`）；右子 `1`（孩子 `0`、`8`）。`5`、`1` 分居根的两侧，因此 LCA 是根 `3`。

**示例 2：**

```
输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
输出：5
解释：节点 4 在节点 5 的子树中，5 是 4 的祖先，也可以是它自己的祖先，故 LCA 是 5。
```

**示例 3：**

```
输入：root = [1,2], p = 1, q = 2
输出：1
```

**提示：**

- 树中节点数目范围 `[2, 10^5]`
- `-10^9 <= Node.val <= 10^9`
- 所有节点值 `Node.val` 互不相同
- `p != q`，且 `p`、`q` 均存在于给定的二叉树中

## 💡 题解

### 解法一：记录父指针 + 祖先集合

**思路**：先做一次 DFS，用哈希表记下每个节点的父节点；随后从 `p` 出发沿父指针一路走到根，沿途所有节点（含 `p` 自身）存入集合，得到 `p` 的全部祖先。再让 `q` 也沿父指针向上走，**第一个**出现在集合中的节点就是两者的最近公共祖先。本质是把树上问题转化为「两条链求交」。

```cpp
#include <unordered_map>
#include <unordered_set>

class Solution {
    unordered_map<TreeNode*, TreeNode*> parent;  // 节点 -> 父节点

    void dfs(TreeNode* node) {
        if (!node) return;
        if (node->left) { parent[node->left] = node; dfs(node->left); }
        if (node->right) { parent[node->right] = node; dfs(node->right); }
    }

public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        parent[root] = nullptr;
        dfs(root);                             // 一次遍历记录所有父指针
        unordered_set<TreeNode*> ancestors;    // p 自身及其全部祖先
        for (TreeNode* x = p; x; x = parent[x]) ancestors.insert(x);
        for (TreeNode* x = q; x; x = parent[x])
            if (ancestors.count(x)) return x;  // q 向上走到的第一个交点即 LCA
        return nullptr;                        // 题目保证存在，不会到达
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`

### 解法二：后序 DFS 一次遍历（推荐）

**思路**：递归函数的返回值含义是「当前子树中的发现」：空则返回空；若 `root` 就是 `p` 或 `q`，直接返回 `root`（一个节点可以是自己的祖先，且无需再深入找另一个——无论另一个在哪，这棵子树能向上汇报的都只能是 `root`）。否则递归左右子树，拿到两个结果 `left`、`right`：

- 两者都非空：`p`、`q` 分居两侧，当前节点就是 LCA；
- 只有一侧非空：`p`、`q`（或已合并出的答案）都在那一侧，把该结果继续上传。

由于一旦命中 `p`/`q` 就立即返回、不再深入，答案自然取到深度最大的公共祖先。

```cpp
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || root == p || root == q) return root;  // 空节点或命中目标
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        if (left && right) return root;   // p、q 分居两侧：当前节点即 LCA
        return left ? left : right;       // 都在同一侧：上传非空的那个
    }
};
```

- ⏱️ 时间复杂度：`O(n)`（每个节点至多访问一次，命中即剪枝）
- 💾 空间复杂度：`O(h)` 递归栈，最坏（链状树）为 `O(n)`

## ⚠️ 易错点

- `root == p || root == q` 的短路判断**必不可少**：若缺少它，当 `p` 是 `q` 的祖先时，`p` 所在子树会向上返回 `nullptr`，把 `p`「弄丢」，导致答案错误。
- 递归返回值语义是「`p` / `q` / 已求出的 LCA」三者之一，靠 `left && right` 收束判断，不要试图在递归中区分返回的到底是哪个。
- 只有一侧非空时应**上传非空那侧的结果**；误写成返回 `root` 或 `nullptr` 都会出错。
- 题目保证 `p`、`q` 都存在且不相同；若允许不存在，此写法需要额外标记（如统计找到几个目标节点）。

---

[← 返回目录](../../README.md)
