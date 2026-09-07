# 114. 二叉树展开为链表

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/flatten-binary-tree-to-linked-list/) ｜ [国际站](https://leetcode.com/problems/flatten-binary-tree-to-linked-list/)
>
> 🟡 中等 ｜ 标签：`树` `深度优先搜索`

## 📝 题目描述

给你二叉树的根节点 `root`，请你将它展开为一棵「单链表」形态的树：

- 展开后的单链表同样使用 `TreeNode`，其中 `right` 指针指向链表中的下一个节点，`left` 指针始终为 `nullptr`；
- 展开后的顺序与该树的**前序遍历**（根-左-右）一致；
- 展开在原树上**就地**进行——函数无返回值，直接修改给定树。

**示例 1：**

```
输入：root = [1,2,5,3,4,null,6]
输出：[1,null,2,null,3,null,4,null,5,null,6]
解释：前序遍历顺序为 1→2→3→4→5→6，展开为右指针串联的单链表，
      且每个节点的 left 都置为 null。
```

**示例 2：**

```
输入：root = []
输出：[]
```

**示例 3：**

```
输入：root = [0]
输出：[0]
```

**提示：**

- 树中结点数在范围 `[0, 2000]` 内
- `-100 <= Node.val <= 100`

**进阶：** 你可以使用原地算法（`O(1)` 额外空间）展开这棵树吗？

## 💡 题解

### 解法一：前序遍历收集节点再重连

**思路**：最直接的做法：先递归前序遍历，把所有节点按访问顺序存入数组，再从头到尾用 `right` 指针把数组中的节点依次串起来，同时把每个节点的 `left` 置空。逻辑清晰不易错，但需要 `O(n)` 的节点数组（外加递归栈）。

```cpp
#include <vector>

class Solution {
public:
    void flatten(TreeNode* root) {
        vector<TreeNode*> nodes;
        preorder(root, nodes);
        for (int i = 1; i < static_cast<int>(nodes.size()); ++i) {
            nodes[i - 1]->left = nullptr;
            nodes[i - 1]->right = nodes[i];
        }
    }

private:
    void preorder(TreeNode* node, vector<TreeNode*>& nodes) {
        if (!node) return;
        nodes.push_back(node);        // 根
        preorder(node->left, nodes);  // 左
        preorder(node->right, nodes); // 右
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`（节点数组 + 递归栈）

### 解法二：逆前序递归——右-左-根

**思路**：前序是「根-左-右」，整体反过来就是「右-左-根」。用成员变量 `prev` 指向已拼好的链表头（初始为空），按「右-左-根」递归：当前节点的两棵子树都处理完后，把它插到链表头部——`right` 指向 `prev`、`left` 置空，再更新 `prev`。这等价于从链表尾部向头部反向构建，一趟完成，空间只需 `O(h)` 递归栈。

```cpp
class Solution {
public:
    void flatten(TreeNode* root) {
        dfs(root);
    }

private:
    TreeNode* prev_ = nullptr;  // 已拼好的链表头

    void dfs(TreeNode* node) {
        if (!node) return;
        dfs(node->right);       // 先展开右子树
        dfs(node->left);        // 再展开左子树
        node->right = prev_;    // 当前节点接到链表头部
        node->left = nullptr;
        prev_ = node;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(h)`（递归栈深度为树高）

### 解法三：迭代寻找前驱，O(1) 空间（推荐）

**思路**：借鉴 Morris 遍历的思想。维护当前节点 `cur`，逐个确定链表的下一个节点：若 `cur` 有左子树，就找到左子树的最右节点——它是 `cur` 在前序意义下的**前驱**（也是左子树前序遍历的最后一个节点），把 `cur` 原来的右子树整体接到前驱的右侧；随后把左子树整体搬到 `cur` 的右边，`left` 置空。若 `cur` 没有左子树，说明它已处于正确位置，直接右移。每个节点只被「路过」常数次，无递归、无栈，满足进阶的 `O(1)` 空间要求。

```cpp
class Solution {
public:
    void flatten(TreeNode* root) {
        TreeNode* cur = root;
        while (cur) {
            if (cur->left) {
                TreeNode* pred = cur->left;              // 进入左子树
                while (pred->right) pred = pred->right;  // 左子树最右节点 = 前序前驱
                pred->right = cur->right;                // 原右子树接到前驱之后
                cur->right = cur->left;                  // 左子树整体上移为右链
                cur->left = nullptr;
            }
            cur = cur->right;  // 移动到链表的下一个节点
        }
    }
};
```

- ⏱️ 时间复杂度：`O(n)`（寻找前驱的总步数均摊到每条边只有常数次）
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 展开顺序是**前序遍历**而非中序/后序，解法一中若把收集顺序写错，整条链都会接反。
- 重连时忘记把每个节点的 `left` 置空，LeetCode 的序列化校验会因 `left` 非空判错。
- 解法三中必须**先**把原右子树接到前驱后面、**再**修改 `cur->right`；若顺序颠倒，`cur->right = cur->left` 之后原右子树的引用就丢失了。
- 解法二的递归顺序必须是「右-左-根」（逆前序）；若按「根-左-右」正向递归，处理根时左右子树尚未展开，无法在 `O(1)` 时间内正确衔接。

---

[← 返回目录](../../README.md)
