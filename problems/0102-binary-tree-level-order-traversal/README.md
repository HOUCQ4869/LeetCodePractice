# 102. 二叉树的层序遍历

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/binary-tree-level-order-traversal/) ｜ [国际站](https://leetcode.com/problems/binary-tree-level-order-traversal/)
>
> 🟡 中等 ｜ 标签：`树` `广度优先搜索`

## 📝 题目描述

给你二叉树的根节点 `root`，返回其节点值的**层序遍历**结果：即**逐层地**、**从左到右**访问所有节点，形成一个二维数组，第 `i` 个子数组包含第 `i` 层（根为第 `0` 层）的全部节点值。

**示例 1：**

```
输入：root = [3,9,20,null,null,15,7]
输出：[[3],[9,20],[15,7]]
解释：第 0 层只有根 3；第 1 层为 9、20（从左到右）；
     第 2 层为 15、7。
```

**示例 2：**

```
输入：root = [1]
输出：[[1]]
```

**示例 3：**

```
输入：root = []
输出：[]
```

**提示：**

- 树中节点数目在范围 `[0, 2000]` 内
- `-1000 <= Node.val <= 1000`

## 💡 题解

### 解法一：DFS 递归（携带层号）

**思路**：层序遍历不一定非要用队列。做前序 DFS 时把当前层号 `level` 作为参数传下去，保证访问到某层第一个节点之前，结果数组中已存在对应下标的空子数组（`res.size() == level` 时就 `emplace_back` 一个空数组），随后把节点值追加到 `res[level]`。前序（根、左、右）的访问顺序恰好保证每层内部从左到右有序，递归结束后 `res` 自然就是逐层的二维数组。

```cpp
#include <vector>

class Solution {
    void dfs(TreeNode* node, int level, vector<vector<int>>& res) {
        if (node == nullptr) return;
        if ((int)res.size() == level) {   // 第一次到达该层，开辟子数组
            res.emplace_back();
        }
        res[level].push_back(node->val);  // 前序：先记录当前节点
        dfs(node->left, level + 1, res);  // 再走左、右子树
        dfs(node->right, level + 1, res);
    }

public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        dfs(root, 0, res);
        return res;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(h)`（递归栈，不含输出数组；最坏 `O(n)`）

### 解法二：BFS 队列逐层处理（推荐）

**思路**：层序遍历的标准做法。根节点入队；每轮循环处理**一整层**——先记录当前队列长度 `sz`，它恰好等于本层的节点数，然后循环 `sz` 次：出队一个节点，把它的值收入当前层临时数组，并把其非空左右孩子入队。一轮结束后本层数组加入结果。`sz` 必须在入队孩子**之前**取定，这样新入队的孩子属于下一层，不会被本轮处理。队列天然保证"先入队的层先处理、同层内从左到右"。

```cpp
#include <queue>
#include <vector>

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (root == nullptr) return res;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int sz = (int)q.size();      // 当前层的节点数（入队前取定）
            vector<int> level;
            level.reserve(sz);
            for (int i = 0; i < sz; ++i) {
                TreeNode* node = q.front();
                q.pop();
                level.push_back(node->val);       // 访问本层节点
                if (node->left != nullptr) q.push(node->left);
                if (node->right != nullptr) q.push(node->right);
            }
            res.push_back(move(level));  // 本层结果进入答案
        }
        return res;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`（每个节点入队、出队各一次）
- 💾 空间复杂度：`O(w)`（队列开销，`w` 为最宽一层的节点数，最坏约 `n/2`；不含输出数组）

## ⚠️ 易错点

- 必须在内存循环开始前把 `q.size()` 存入 `sz`：若内层循环条件直接写 `i < q.size()`，孩子入队后队列变长，下一层节点会被并入本层。
- `root == nullptr` 要提前返回空结果，否则向队列压入空指针并解引用会崩溃。
- 结果是**二维数组**（每层一个子数组），不要把所有值铺平成一维；DFS 解法中"开辟子数组"的判断是 `res.size() == level`，写成 `<=` 会导致重复开层。
- 空孩子不要入队（普通层序遍历不需要占位），否则队列里混入空指针，出队解引用即出错。

---

[← 返回目录](../../README.md)
