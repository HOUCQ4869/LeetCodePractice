# 104. 二叉树的最大深度

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/maximum-depth-of-binary-tree/) ｜ [国际站](https://leetcode.com/problems/maximum-depth-of-binary-tree/)
>
> 🟢 简单 ｜ 标签：`树` `深度优先搜索`

## 📝 题目描述

给定一棵二叉树的根节点 `root`，返回它的**最大深度**。二叉树的深度（高度）定义如下：**根节点为第 1 层**（也可定义为根节点深度为 1），从根到最远叶子节点所经过的**节点总数**即为最大深度。空树（`root` 为空）的深度为 `0`。

**示例 1：**

```
输入：root = [3,9,20,null,null,15,7]
输出：3
解释：树为 3 的左右孩子 9、20，20 的左右孩子 15、7。
     从根 3 到叶子 15（或 7）共经过 3 个节点，最大深度为 3。
```

**示例 2：**

```
输入：root = [1,null,2]
输出：2
解释：根 1 只有右孩子 2，路径 1 -> 2 共 2 个节点。
```

**提示：**

- 树中节点数目在范围 `[0, 10^4]` 内
- `-100 <= Node.val <= 100`

## 💡 题解

### 解法一：自顶向下的 DFS（携带深度参数）

**思路**：把"当前深度 `d`"作为参数随递归向下传递。进入一个节点时它位于第 `d` 层，若它是叶子节点，就用 `d` 尝试更新全局最大值；否则分别以 `d + 1` 递归左右子树。这是一种前序（根先于子树处理）的思考方式：先在父节点处算好自己的深度，再告诉孩子。

```cpp
#include <algorithm>

class Solution {
    void dfs(TreeNode* node, int d, int& ans) {
        if (node == nullptr) return;
        ans = max(ans, d);  // 当前节点在第 d 层，尝试更新答案
        dfs(node->left, d + 1, ans);
        dfs(node->right, d + 1, ans);
    }

public:
    int maxDepth(TreeNode* root) {
        int ans = 0;
        dfs(root, 1, ans);  // 根节点位于第 1 层
        return ans;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(h)`（递归栈，`h` 为树高，最坏 `O(n)`）

### 解法二：BFS 逐层计数

**思路**：按层序遍历（BFS）把节点一圈一圈地处理，每处理完一圈深度加一。用队列保存当前层的所有节点，循环开始时记录队列长度 `sz`（即当前层节点数），把这一层节点依次出队、把它们的孩子入队。外层循环每执行一轮，就说明又向下走了一层，`depth` 自增，队列为空时的 `depth` 即最大深度。BFS 还可以**提前结束**：当某层节点都无孩子时即是最后一层（普通写法不提前退出也正确）。

```cpp
#include <queue>

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        queue<TreeNode*> q;
        q.push(root);
        int depth = 0;
        while (!q.empty()) {
            ++depth;                     // 即将处理新的一层
            int sz = (int)q.size();      // 当前层的节点数
            for (int i = 0; i < sz; ++i) {
                TreeNode* node = q.front();
                q.pop();
                if (node->left != nullptr) q.push(node->left);
                if (node->right != nullptr) q.push(node->right);
            }
        }
        return depth;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(w)`（队列开销，`w` 为最宽一层的节点数，最坏约 `n/2`）

### 解法三：自底向上的 DFS——后序求高度（推荐）

**思路**：换一个角度：**整棵树的最大深度 = 左右子树最大深度的较大者 + 1**（那个 `+1` 就是根自己），空节点深度为 `0`。这正是后序遍历（先算子树、再合并到根）的递归写法，一行核心代码即可，无需全局变量，也天然处理了空树。`n` 个节点、`n` 个子问题，是最简洁也最不容易写错的解法。

```cpp
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`（每个节点恰好计算一次）
- 💾 空间复杂度：`O(h)`（递归栈，平衡时 `O(log n)`，链状时 `O(n)`）

## ⚠️ 易错点

- 空树必须返回 `0`：递归入口 `root == nullptr` 的判断不可遗漏，否则空指针解引用。
- 深度的定义是**节点数**而非边数：根节点单独成树时深度为 `1`，不是 `0`，因此自顶向下要从 `d = 1` 起传。
- BFS 中必须先取出 `q.size()` 存成固定值 `sz` 再进入内层循环，若在循环里直接写 `i < q.size()`，会因队列长度随孩子入队而变化导致层数混乱。
- 递归是"先递归再 `+1`"（后序合并），不要把 `+1` 加在传给子调用的参数上又同时加在返回值上，导致重复计数。

---

[← 返回目录](../../README.md)
