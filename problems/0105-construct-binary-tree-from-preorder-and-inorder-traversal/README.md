# 105. 从前序与中序遍历序列构造二叉树

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/) ｜ [国际站](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)
>
> 🟡 中等 ｜ 标签：`树` `分治`

## 📝 题目描述

给定两个整数数组 `preorder` 和 `inorder`，其中 `preorder` 是同一棵二叉树的**前序遍历**序列，`inorder` 是同一棵二叉树的**中序遍历**序列。请根据这两个序列构造出这棵二叉树，并返回其根节点。

两个序列的性质：

- 前序遍历顺序为「根 → 左子树 → 右子树」，因此**首元素一定是当前子树的根**；
- 中序遍历顺序为「左子树 → 根 → 右子树」，因此**根把序列切成左右两段**，分别对应左、右子树。

**示例 1：**

```
输入: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
输出: [3,9,20,null,null,15,7]
```

树形结构：根为 `3`，左子树为单节点 `9`，右子树根为 `20`（左孩子 `15`、右孩子 `7`）。

**示例 2：**

```
输入: preorder = [-1], inorder = [-1]
输出: [-1]
```

**提示：**

- `1 <= preorder.length <= 3000`
- `inorder.length == preorder.length`
- `-3000 <= preorder[i], inorder[i] <= 3000`
- `preorder` 和 `inorder` 中均**无重复**元素
- 给定的序列一定能重构出一棵有效的二叉树

## 💡 题解

### 解法一：递归分治（线性查找根）

**思路**：对当前子树，取前序区间首元素 `pre[pl]` 作为根，在中序区间 `[il, ir]` 中线性查找它的位置 `k`。于是中序被划分为左子树 `[il, k-1]` 和右子树 `[k+1, ir]`；由左子树节点个数 `leftSize = k - il`，前序区间也被划分为根、左子树 `[pl+1, pl+leftSize]`、右子树 `[pl+leftSize+1, pr]`。分别递归构造左右子树即可。每次找根需线性扫描，树退化为链时整体退化为 `O(n²)`。

```cpp
#include <vector>

class Solution {
    // 在 inorder[l..r] 中查找值 x 的下标
    int find(const vector<int>& inorder, int l, int r, int x) {
        for (int i = l; i <= r; ++i)
            if (inorder[i] == x) return i;
        return -1;
    }

    // 用 pre[pl..pr] 与 in[il..ir] 构造子树
    TreeNode* build(const vector<int>& pre, int pl, int pr,
                    const vector<int>& in, int il, int ir) {
        if (pl > pr) return nullptr;                 // 空区间：无子树
        auto root = new TreeNode(pre[pl]);           // 前序首元素为根
        int k = find(in, il, ir, pre[pl]);           // 根在中序中的位置
        int leftSize = k - il;                       // 左子树节点个数
        root->left = build(pre, pl + 1, pl + leftSize, in, il, k - 1);
        root->right = build(pre, pl + leftSize + 1, pr, in, k + 1, ir);
        return root;
    }

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = (int)preorder.size();
        return build(preorder, 0, n - 1, inorder, 0, n - 1);
    }
};
```

- ⏱️ 时间复杂度：`O(n²)` 最坏（链状树），平衡时约 `O(n log n)`
- 💾 空间复杂度：`O(h)` 递归栈（`h` 为树高，不含输出的树本身）

### 解法二：哈希表定位 + 前序游标（推荐）

**思路**：预先遍历一遍中序，用哈希表存「值 → 中序下标」，找根从 `O(n)` 降到 `O(1)`。再观察前序的消费顺序恰是「根、左子树全部、右子树全部」：递归只需携带中序区间 `[il, ir]`，用全局游标 `preIdx` 依次取出下一个根——只要**先递归左子树、再递归右子树**，游标就自动对齐。整体一趟 `O(n)`。

```cpp
#include <unordered_map>
#include <vector>

class Solution {
    unordered_map<int, int> idx;  // 值 -> 中序下标
    int preIdx = 0;               // 前序中下一个待消费的位置（即下一个根）

    // 用 inorder[il..ir] 区间递归建树，根从 preorder[preIdx] 依次取
    TreeNode* build(const vector<int>& preorder, int il, int ir) {
        if (il > ir) return nullptr;
        int rootVal = preorder[preIdx++];       // 消费一个根
        int k = idx[rootVal];                   // O(1) 定位根在中序中的位置
        auto root = new TreeNode(rootVal);
        root->left = build(preorder, il, k - 1);    // 必须先建左子树
        root->right = build(preorder, k + 1, ir);   // 再建右子树
        return root;
    }

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        idx.clear();
        for (int i = 0; i < (int)inorder.size(); ++i) idx[inorder[i]] = i;
        preIdx = 0;
        return build(preorder, 0, (int)inorder.size() - 1);
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`（哈希表 + 递归栈）

## ⚠️ 易错点

- 区间划分下标极易出错：左子树前序是 `[pl+1, pl+leftSize]`，长度恰为 `leftSize = k - il`；建议现场用「节点个数」推导，不要死记公式。
- 游标写法必须**先左后右**递归，因为前序顺序是「根 → 左 → 右」，顺序颠倒游标就乱了。
- 哈希表法依赖「值无重复」这一条件；若有重复值，此法失效，需要回退到按区间查找并处理歧义。
- 递归终止条件是区间为空（`il > ir` 或 `pl > pr`），单节点也要正常建出来，不要把 `pl == pr` 当成终止条件。

---

[← 返回目录](../../README.md)
