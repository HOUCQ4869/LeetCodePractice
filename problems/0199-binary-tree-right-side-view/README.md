# 199. 二叉树的右视图

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/binary-tree-right-side-view/) ｜ [国际站](https://leetcode.com/problems/binary-tree-right-side-view/)
>
> 🟡 中等 ｜ 标签：`树` `深度优先搜索` `广度优先搜索`

## 📝 题目描述

给定一棵二叉树的根节点 `root`，想象自己站在树的**右侧**，按照从顶部到底部的顺序，返回你从右侧能看到的节点值列表。

- 每一层只能看到该层**最靠右**的节点，同层更靠左的节点会被挡住；
- 注意是「每一层取一个」：若某层最深的节点位于左子树（根的右指针为空），它也会出现在右视图中，因此不能简单地沿右指针一路向下。

**示例 1：**

```
输入：root = [1,2,3,null,5,null,4]
输出：[1,3,4]
解释：第 0 层只有 1；第 1 层为 2、3，最右是 3；
      第 2 层为 5、4（5 挂在 2 下、4 挂在 3 下），4 在 5 右侧挡住 5，
      故右视图自上而下为 [1,3,4]。
```

**示例 2：**

```
输入：root = [1,null,3]
输出：[1,3]
```

**示例 3：**

```
输入：root = []
输出：[]
```

**提示：**

- 二叉树的节点个数的范围是 `[0, 100]`
- `-100 <= Node.val <= 100`

## 💡 题解

### 解法一：BFS 层序遍历——每层取最后一个

**思路**：右视图的本质是「每一层最靠右的节点」。借助队列做层序遍历（BFS）：每轮处理一层，先记录本层节点数 `sz`，再把这 `sz` 个节点逐个出队、将其孩子入队；当出队到本层最后一个（`i == sz - 1`）时，该节点的值就是右视图在该层的取值。BFS 天然按层分组，是本题最直观的思路。

```cpp
#include <queue>
#include <vector>

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        if (!root) return res;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int sz = q.size();  // 当前层的节点数，必须在入队前取定
            for (int i = 0; i < sz; ++i) {
                TreeNode* node = q.front();
                q.pop();
                if (i == sz - 1) res.push_back(node->val);  // 本层最右
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        return res;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`（队列最多同时容纳最宽一层的节点）

### 解法二：DFS 根-右-左（推荐）

**思路**：换一个视角：每层「从右侧看到」的节点，恰好是按「根-右-左」顺序访问时**每个深度第一个被访问到**的节点。因此 DFS 每次先递归右子树、再递归左子树，并用结果数组 `res` 的长度隐式记录「目前已记录到第几层」：当节点所在深度 `depth == res.size()` 时，说明该深度尚未有节点入列，当前节点即该层的最右节点。相比 BFS 只需 `O(h)` 的递归栈空间，且不需要队列分层。

```cpp
#include <vector>

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        dfs(root, 0, res);
        return res;
    }

private:
    void dfs(TreeNode* node, int depth, vector<int>& res) {
        if (!node) return;
        if (depth == static_cast<int>(res.size())) {  // 该深度首个被访问的节点
            res.push_back(node->val);
        }
        dfs(node->right, depth + 1, res);  // 先走右侧
        dfs(node->left, depth + 1, res);   // 右侧走完再走左侧
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(h)`（递归栈深度为树高，链状树退化为 `O(n)`）

## ⚠️ 易错点

- 右视图不是「沿右指针一路向下」：若根只有左子树且很深，左子树中每层的节点同样会出现在右视图里。
- BFS 中 `sz = q.size()` 必须在进入本层循环前一次性取出；若把循环条件写成 `i < q.size()`，会因为孩子不断入队导致层边界漂移、结果错误。
- DFS 必须先右后左，写成先左后右得到的就是左视图。
- 空树（题目允许 `n = 0`）要返回空数组，开头的判空不能省。

---

[← 返回目录](../../README.md)
