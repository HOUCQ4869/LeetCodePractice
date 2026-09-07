# 101. 对称二叉树

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/symmetric-tree/) ｜ [国际站](https://leetcode.com/problems/symmetric-tree/)
>
> 🟢 简单 ｜ 标签：`树` `深度优先搜索` `广度优先搜索`

## 📝 题目描述

给你一棵二叉树的根节点 `root`，检查它是否**轴对称**：是否存在一条竖直中轴线，使得树沿该轴翻转后与原树完全相同。形式化地说，需要判断左子树与右子树是否互为**镜像**：两棵树镜像当且仅当它们的根节点值相同，且每棵树的左子树与另一棵树的右子树也互为镜像。

**示例 1：**

```
输入：root = [1,2,2,3,4,4,3]
输出：true
解释：根 1 的左右子树根均为 2。左侧 2 的孩子为 3、4，
     右侧 2 的孩子为 4、3，恰好左右互换，逐层递归都满足镜像。
```

**示例 2：**

```
输入：root = [2,3,3,4,5,null,4]
输出：false
解释：左子树中节点 3 的孩子是 4、5，而右子树中节点 3 的孩子是
     null、4。把左子树镜像后得到 5、4，与 null、4 不一致。
```

**提示：**

- 树中节点数目在范围 `[1, 1000]` 内
- `-100 <= Node.val <= 100`

**进阶**：你可以运用递归和迭代两种方法解决这个问题吗？

## 💡 题解

### 解法一：BFS 逐层判回文

**思路**：轴对称的树，**从上往下每一层的节点值序列（含空位标记）都应当是回文**。做层序遍历时，把 `nullptr` 也作为一种"占位值"记录并让孩子入队，从而保留空节点在层内的位置信息；每取完一层就用双指针检查该层序列是否回文，一旦某层不是回文即可提前返回 `false`。这个解法直观，但需要额外处理空占位，且不能提前剪枝已入队的节点。

```cpp
#include <optional>
#include <queue>
#include <vector>

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int sz = (int)q.size();
            vector<optional<int>> level;  // 用 nullopt 标记空位
            for (int i = 0; i < sz; ++i) {
                TreeNode* node = q.front();
                q.pop();
                if (node == nullptr) {
                    level.push_back(nullopt);
                } else {
                    level.push_back(node->val);
                    q.push(node->left);   // 空孩子也要入队，保住位置
                    q.push(node->right);
                }
            }
            int n = (int)level.size();
            for (int i = 0; i < n / 2; ++i) {
                if (level[i] != level[n - 1 - i]) return false;  // 本层不是回文
            }
        }
        return true;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`（队列与每层临时序列）

### 解法二：迭代——队列成对比较

**思路**：与其整层判断回文，不如**成对**比较镜像位置上的节点：初始把 `(root, root)` 入队，每次取出两个节点 `u`、`v`，二者需同时为空或同时非空且值相等；然后把 `u` 的左孩子与 `v` 的右孩子成对入队、`u` 的右孩子与 `v` 的左孩子成对入队（镜像位置配对），队列清空仍未失配即为对称。本质上是用队列模拟解法三的递归。

```cpp
#include <queue>

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        q.push(root);  // 初始镜像对 (root, root)
        while (!q.empty()) {
            TreeNode* u = q.front();
            q.pop();
            TreeNode* v = q.front();
            q.pop();
            if (u == nullptr && v == nullptr) continue;       // 都为空，配对成功
            if (u == nullptr || v == nullptr) return false;   // 一空一非空
            if (u->val != v->val) return false;               // 值不同
            q.push(u->left);   // u 的左 对 v 的右
            q.push(v->right);
            q.push(u->right);  // u 的右 对 v 的左
            q.push(v->left);
        }
        return true;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`（队列中最多约 n/2 个指针）

### 解法三：递归（推荐）

**思路**：把"整棵树对称"转化为"两棵子树互为镜像"。写辅助函数 `mirror(a, b)`：`a`、`b` 都空则对称；只一个空或值不等则不对称；否则要求 `a` 的左子树与 `b` 的右子树镜像、`a` 的右子树与 `b` 的左子树镜像（注意是**交叉**比较）。入口传 `mirror(root, root)` 统一处理根的边界。代码最短，且一旦失配立即短路返回，是本题的标准解法。

```cpp
class Solution {
    // 判断 a、b 两棵子树是否互为镜像
    bool mirror(TreeNode* a, TreeNode* b) {
        if (a == nullptr && b == nullptr) return true;   // 同时为空
        if (a == nullptr || b == nullptr) return false;  // 一空一非空
        if (a->val != b->val) return false;              // 值不同
        return mirror(a->left, b->right) && mirror(a->right, b->left);
    }

public:
    bool isSymmetric(TreeNode* root) {
        return mirror(root, root);
    }
};
```

- ⏱️ 时间复杂度：`O(n)`（每个节点至多被访问一次）
- 💾 空间复杂度：`O(h)`（递归栈，`h` 为树高，最坏 `O(n)`）

## ⚠️ 易错点

- 镜像比较是**交叉**的：`a` 的左对 `b` 的右、`a` 的右对 `b` 的左；写成"左对左、右对右"判断的就是两棵树是否相同而不是镜像。
- 终止条件的顺序：先判"都空"，再判"一空一非空"，最后判值相等；上来就解引用 `a->val` 会空指针崩溃。
- "树对称"不等于"左右子树各自对称"：需要比较的是左右子树**互为镜像**，两个独立的递归调用方向不同。
- 层序判回文时必须保留**空节点占位**（例如 `[2,3,3,4,null,null,4]` 各层值回文但树不对称），把空位丢掉就会误判。

---

[← 返回目录](../../README.md)
