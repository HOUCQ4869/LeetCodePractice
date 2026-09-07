# 98. 验证二叉搜索树

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/validate-binary-search-tree/) ｜ [国际站](https://leetcode.com/problems/validate-binary-search-tree/)
>
> 🟡 中等 ｜ 标签：`树` `深度优先搜索`

## 📝 题目描述

给你一个二叉树的根节点 `root`，判断其是否是一棵**有效的二叉搜索树**（BST）。

有效 BST 的定义如下：

- 节点的左子树只包含**严格小于**该节点值的节点；
- 节点的右子树只包含**严格大于**该节点值的节点；
- 左右子树也必须分别是二叉搜索树（即大小约束要沿祖先链传递到整棵子树，而不仅限于直接孩子）。

**示例 1：**

```
输入：root = [2,1,3]
输出：true
解释：2 的左子树只有 1（1 < 2），右子树只有 3（3 > 2），是有效 BST。
```

**示例 2：**

```
输入：root = [5,1,4,null,null,3,6]
输出：false
解释：根为 5，右子树为 4、3、6。节点 3 位于 5 的右子树中但 3 < 5，
      违反了「右子树上所有节点都必须大于根」的约束。
```

**提示：**

- 树中节点数目在范围 `[1, 10^4]` 内
- `-2^31 <= Node.val <= 2^31 - 1`

## 💡 题解

### 解法一：自顶向下递归——传递上下界

**思路**：BST 的约束是「祖先链」级别的：每个节点必须落在由所有祖先共同划定的开区间 `(lo, hi)` 内。从根开始递归，初始区间为正负无穷——由于节点值本身可以取到 `int` 的最小/最大值，边界必须用 `long long` 表示。进入左子树时把上界收紧为当前节点值，进入右子树时把下界收紧为当前节点值；一旦发现节点值越界（含相等）立即返回 `false`。若只比较「节点与其直接孩子」，会漏判示例 2 这类深层违规。

```cpp
#include <climits>

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return check(root, LLONG_MIN, LLONG_MAX);
    }

private:
    bool check(TreeNode* node, long long lo, long long hi) {
        if (!node) return true;                       // 空树是合法 BST
        if (node->val <= lo || node->val >= hi) return false;  // 越界
        return check(node->left, lo, node->val)       // 左子树：上界收紧
            && check(node->right, node->val, hi);     // 右子树：下界收紧
    }
};
```

- ⏱️ 时间复杂度：`O(n)`（每个节点恰好访问一次）
- 💾 空间复杂度：`O(h)`（递归栈深度为树高，链状树退化为 `O(n)`）

### 解法二：中序遍历（推荐）

**思路**：BST 的中序遍历结果是**严格递增**序列，反之亦然。于是只需中序遍历一遍，用 `prev` 记录上一个访问到的节点，一旦出现 `当前值 <= prev 值` 即可断定非法。这里用显式栈实现迭代中序：先把左链依次压栈，弹出栈顶即为中序当前节点，访问后再转向其右子树；相比递归写法，找到违规可立即 `return`，也不需要额外的成员变量。

```cpp
#include <stack>

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        stack<TreeNode*> stk;
        TreeNode* prev = nullptr;
        TreeNode* cur = root;
        while (cur || !stk.empty()) {
            while (cur) {                    // 一路向左，依次压栈
                stk.push(cur);
                cur = cur->left;
            }
            cur = stk.top();                 // 栈顶即中序当前节点
            stk.pop();
            if (prev && cur->val <= prev->val) {
                return false;                // 中序序列必须严格递增
            }
            prev = cur;
            cur = cur->right;                // 转向右子树
        }
        return true;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(h)`（栈中最多保存一条根到叶路径上的节点）

## ⚠️ 易错点

- 只比较「节点与其左右孩子」是错的：如 `[5,4,6,null,null,3,7]` 中节点 3 与其父 6 满足父子大小关系，但 3 位于根 5 的右子树且 3 < 5，整棵树非法；逐层传递上下界（或看中序是否递增）才能查出来。
- 节点值域覆盖完整的 `int` 范围，初始边界若用 `INT_MIN / INT_MAX`，单节点树 `[2147483647]` 会因 `val >= INT_MAX` 被误判——边界必须换成 `long long` 的 `LLONG_MIN / LLONG_MAX`（或用空指针表示无穷）。
- BST 定义是**严格**大于/小于：出现重复值（如 `[2,2,2]`）应判为 `false`，判断越界时必须写成 `<=` / `>=`，漏掉等号会把重复值放过。
- 迭代中序的循环条件是 `cur || !stk.empty()`，两个条件缺一不可：只写前者会提前退出，只写后者无法回到右子树。

---

[← 返回目录](../../README.md)
