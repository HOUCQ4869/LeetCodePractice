# 226. 翻转二叉树

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/invert-binary-tree/) ｜ [国际站](https://leetcode.com/problems/invert-binary-tree/)
>
> 🟢 简单 ｜ 标签：`树` `深度优先搜索`

## 📝 题目描述

给你一棵二叉树的根节点 `root`，翻转这棵二叉树，并返回其根节点。翻转（也称为"镜像"）是指：**交换树中每一个节点的左右子树**，整个树随之左右对称地翻转过来。

**示例 1：**

```
输入：root = [4,2,7,1,3,6,9]
输出：[4,7,2,9,6,3,1]
解释：原树中 4 的左右孩子是 2、7，翻转后变为 7、2；
     2 的孩子 1、3 变为 3、1；7 的孩子 6、9 变为 9、6。
```

**示例 2：**

```
输入：root = [2,1,3]
输出：[2,3,1]
解释：根 2 的左右孩子 1、3 交换为 3、1。
```

**示例 3：**

```
输入：root = []
输出：[]
```

**提示：**

- 树中节点数目在范围 `[0, 100]` 内
- `-100 <= Node.val <= 100`

## 💡 题解

### 解法一：迭代 BFS（队列）

**思路**：翻转只要求"每个节点的左右孩子都交换一次"，与处理顺序无关。用队列做层序遍历：每弹出一个节点，就交换它的左右孩子，再把（交换后的）左右孩子入队等待处理，直到队列为空。所有节点都被处理过一次，整棵树即完成镜像。

```cpp
#include <queue>
#include <utility>

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) return nullptr;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            swap(node->left, node->right);  // 交换左右孩子
            if (node->left != nullptr) q.push(node->left);
            if (node->right != nullptr) q.push(node->right);
        }
        return root;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(w)`（队列开销，`w` 为最宽一层的节点数）

### 解法二：迭代 DFS（栈）

**思路**：把上面的队列换成栈即可得到深度优先的迭代版本：弹出一个节点、交换左右孩子、把孩子压栈。虽然弹出顺序变成"后进先出"（相当于前序遍历的变体），但"每个节点恰好交换一次"这一不变量不变，因此同样正确。展示了同一问题在两种遍历策略下的统一写法。

```cpp
#include <stack>
#include <utility>

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) return nullptr;
        stack<TreeNode*> stk;
        stk.push(root);
        while (!stk.empty()) {
            TreeNode* node = stk.top();
            stk.pop();
            swap(node->left, node->right);
            if (node->left != nullptr) stk.push(node->left);
            if (node->right != nullptr) stk.push(node->right);
        }
        return root;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(h)`（栈中最坏保存一条根到叶的路径，`h` 为树高）

### 解法三：递归（推荐）

**思路**：问题的定义天然递归：翻转以 `node` 为根的树 = 先递归翻转左子树、再递归翻转右子树，最后交换这两棵**已经各自翻转好**的子树（后序）；先交换再递归（前序）同样正确。空节点直接返回。三行代码，是本题最简洁、最不易错的写法。

```cpp
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) return nullptr;
        TreeNode* left = invertTree(root->left);    // 递归翻转左子树
        TreeNode* right = invertTree(root->right);  // 递归翻转右子树
        root->left = right;  // 交换两棵已翻转好的子树
        root->right = left;
        return root;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(h)`（递归栈，平衡时 `O(log n)`，链状时 `O(n)`）

## ⚠️ 易错点

- 必须先**保存**递归调用的返回值（或先用临时变量接住 `root->left`），再赋值给 `root->right`；直接连写 `root->left = invertTree(root->left); root->right = invertTree(root->left)` 之类会丢失原子树指针。
- 忘记 `return root`（或递归中忘记返回节点指针），导致返回的是野指针/空指针；本题要在原树上修改并返回根。
- 递归终止条件 `root == nullptr` 不能漏，空树直接返回，否则空指针解引用。
- 每个节点只交换一次即可，不要在递归中既交换左右又递归交换两遍，虽不致错但做了重复工作。

---

[← 返回目录](../../README.md)
