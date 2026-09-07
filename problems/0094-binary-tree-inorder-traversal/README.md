# 94. 二叉树的中序遍历

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/binary-tree-inorder-traversal/) ｜ [国际站](https://leetcode.com/problems/binary-tree-inorder-traversal/)
>
> 🟢 简单 ｜ 标签：`树` `栈`

## 📝 题目描述

给定一棵二叉树的根节点 `root`，返回它的**中序遍历**结果。中序遍历的访问顺序为：先递归地遍历**左子树**，再访问**根节点**，最后递归地遍历**右子树**，按此规则得到节点值的线性序列。

**示例 1：**

```
输入：root = [1,null,2,3]
输出：[1,3,2]
解释：树的结构为 1 -> (右子) 2 -> (左子) 3。
     中序遍历先走左子树（为空），再访问 1，
     然后进入右子树：先走 2 的左子树访问 3，再访问 2。
```

**示例 2：**

```
输入：root = []
输出：[]
```

**示例 3：**

```
输入：root = [1]
输出：[1]
```

**提示：**

- 树中节点数目在范围 `[0, 100]` 内
- `-100 <= Node.val <= 100`

**进阶**：递归算法很简单，你可以通过一个显式栈或者 **Morris 遍历**（空间 `O(1)`）来完成迭代解法吗？

## 💡 题解

### 解法一：递归

**思路**：中序遍历的定义本身就是递归的：`inorder(node) = inorder(node.left) → 访问 node → inorder(node.right)`。写一个辅助函数，遇到空节点直接返回，否则先递归左子树，把当前值加入结果，再递归右子树。注意 `root` 本身可能为 `nullptr`，递归入口天然覆盖这一边界。

```cpp
#include <vector>

class Solution {
    void inorder(TreeNode* node, vector<int>& res) {
        if (node == nullptr) return;
        inorder(node->left, res);   // 左
        res.push_back(node->val);   // 根
        inorder(node->right, res);  // 右
    }

public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        inorder(root, res);
        return res;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`（每个节点恰好访问一次）
- 💾 空间复杂度：`O(n)`（递归调用栈，最坏为链状树）

### 解法二：显式栈的迭代遍历

**思路**：用一个栈模拟递归过程。设指针 `cur` 从根出发，只要 `cur` 非空就一路压栈并走向左孩子（模拟"一路向左"）；走到头后弹出一个节点——它是当前子树中最左的节点，访问它，然后让 `cur` 指向它的右孩子，对右子树重复同样流程。栈非空或 `cur` 非空时循环继续，即可得到完整的中序序列。

```cpp
#include <stack>
#include <vector>

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> stk;
        TreeNode* cur = root;
        while (cur != nullptr || !stk.empty()) {
            while (cur != nullptr) {  // 一路向左，沿途全部压栈
                stk.push(cur);
                cur = cur->left;
            }
            cur = stk.top();          // 栈顶是当前最左节点
            stk.pop();
            res.push_back(cur->val);  // 访问
            cur = cur->right;         // 转向右子树
        }
        return res;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`（栈中最多保存一条从根到叶的路径，最坏为链状树）

### 解法三：Morris 中序遍历（推荐）

**思路**：利用树中大量空闲的 `nullptr` 指针实现 `O(1)` 空间。对当前节点 `cur`，若它有左子树，则找到其**中序前驱**（左子树的最右节点）：若前驱的右指针为空，就让它指回 `cur`（建线索，方便之后从左子树回来），然后 `cur` 进入左子树；若前驱的右指针已指向 `cur`（说明左子树已访问完），拆掉线索、访问 `cur`，再进入右子树。若 `cur` 没有左子树，直接访问并进入右子树。整个过程会把每个节点的空右指针临时借用一次并在用完后还原，树最终恢复原状。

```cpp
#include <vector>

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        TreeNode* cur = root;
        while (cur != nullptr) {
            if (cur->left != nullptr) {
                // 找中序前驱：左子树的最右节点
                TreeNode* pred = cur->left;
                while (pred->right != nullptr && pred->right != cur) {
                    pred = pred->right;
                }
                if (pred->right == nullptr) {
                    pred->right = cur;   // 建线索，之后能回到 cur
                    cur = cur->left;     // 进入左子树
                } else {
                    pred->right = nullptr;  // 左子树已访问完，拆线索
                    res.push_back(cur->val);
                    cur = cur->right;
                }
            } else {
                res.push_back(cur->val);  // 没有左子树，直接访问
                cur = cur->right;
            }
        }
        return res;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`（每条边最多被走 2 次：建线索一次、遍历一次）
- 💾 空间复杂度：`O(1)`（仅使用常数个指针，不借助栈）

## ⚠️ 易错点

- 循环条件是 `cur != nullptr || !stk.empty()`，漏掉 `!stk.empty()` 会在回溯阶段提前退出，漏掉 `cur` 判断则无法进入新的右子树。
- 迭代版中弹出节点后要先 `pop()` 再取 `cur->right`，顺序写反容易在访问和转向之间破坏栈状态。
- Morris 找前驱时的循环条件必须同时包含 `pred->right != nullptr && pred->right != cur`，漏掉后者可能绕线索一圈形成死循环。
- Morris 结束后务必把线索拆掉（`pred->right = nullptr`），否则会破坏树结构，影响后续调用。

---

[← 返回目录](../../README.md)
