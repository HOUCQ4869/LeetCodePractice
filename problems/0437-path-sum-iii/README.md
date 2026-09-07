# 437. 路径总和 III

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/path-sum-iii/) ｜ [国际站](https://leetcode.com/problems/path-sum-iii/)
>
> 🟡 中等 ｜ 标签：`树` `深度优先搜索` `前缀和`

## 📝 题目描述

给定一棵二叉树的根节点 `root` 和一个整数 `targetSum`，求这棵树中**节点值之和等于 `targetSum`** 的路径数目。

路径不需要从根节点开始，也不需要在叶子节点结束，但方向必须是**向下**的——只能从父节点走到子节点。

**示例 1：**

```
输入：root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
输出：3
```

树形结构：根为 `10`；左子 `5`（孩子 `3`、`2`，其中 `3` 的孩子为 `3`、`-2`，`2` 的孩子为 `1`）；右子 `-3`（右孩子 `11`）。和为 8 的路径共 3 条：

1. `5 → 3`（5 + 3 = 8）
2. `5 → 2 → 1`（5 + 2 + 1 = 8）
3. `-3 → 11`（-3 + 11 = 8）

**示例 2：**

```
输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
输出：3
```

树形结构：根为 `5`；左子 `4`（孩子 `11`，其孩子为 `7`、`2`）；右子 `8`（孩子 `13`、`4`，`4` 的孩子为 `5`、`1`）。和为 22 的路径共 3 条：`5→4→11→2`、`4→11→7`、`5→8→4→5`。

**提示：**

- 树中节点数目范围 `[1, 1000]`
- `-10^9 <= Node.val <= 10^9`
- `-1000 <= targetSum <= 1000`

## 💡 题解

### 解法一：双重递归（枚举每个起点）

**思路**：路径可以从任意节点出发，于是对每个节点 `x` 都统计一次「从 `x` 出发、只向下走、和恰好等于 `target` 的路径数」，记为 `rootSum(x, target)`。它是自包含的递归：若 `x->val == sum`，则以 `x` 自身结尾算一条；再向左右孩子递归 `rootSum(child, sum - x->val)`。外层 `pathSum(x)` 累加 `rootSum(x)` 与 `pathSum(x->left)`、`pathSum(x->right)`。两重递归互相独立，最坏（链状树）达 `O(n²)`。注意自上而下的累加和会溢出 `int`，全程用 `long long`。

```cpp
class Solution {
    // 从 node 出发、只向下、和恰好为 sum 的路径数（路径至少含 node）
    long long rootSum(TreeNode* node, long long sum) {
        if (!node) return 0;
        long long cnt = (node->val == sum) ? 1 : 0;  // 以 node 自身结尾的一条
        cnt += rootSum(node->left, sum - node->val);
        cnt += rootSum(node->right, sum - node->val);
        return cnt;
    }

public:
    int pathSum(TreeNode* root, int targetSum) {
        if (!root) return 0;
        long long target = targetSum;
        return (int)(rootSum(root, target)
                     + pathSum(root->left, targetSum)
                     + pathSum(root->right, targetSum));
    }
};
```

- ⏱️ 时间复杂度：`O(n²)` 最坏（链状树），平衡时约 `O(n log n)`
- 💾 空间复杂度：`O(h)` 递归栈（`h` 为树高）

### 解法二：前缀和 + 哈希表 + 回溯（推荐）

**思路**：借鉴数组的「区间和 = 前缀和之差」：设 `prefix(x)` 为根到 `x` 的路径和，则从祖先 `a` 向下到 `b` 的路径和为 `prefix(b) - prefix(a)`（不含 `a`、含 `b`）。于是对每个节点 `b`，只需统计**根到 `b` 的链上**有多少祖先 `a` 满足 `prefix(a) = prefix(b) - target`。DFS 时维护哈希表「前缀和 → 出现次数」，只记录当前链上的前缀和：进入节点时累加 `cur`，先查询 `cnt[cur - target]`，再登记 `cnt[cur]`；递归完左右子树后 `--cnt[cur]` 撤销登记（回溯），保证哈希表始终只反映当前路径。初始 `cnt[0] = 1` 代表「空前缀」，使从根出发的路径也能被统计到。每个节点进出各一次，整体 `O(n)`。

```cpp
#include <unordered_map>

class Solution {
    unordered_map<long long, int> cnt;  // 当前根到节点链上的 前缀和 -> 出现次数

    int dfs(TreeNode* node, long long cur, long long target) {
        if (!node) return 0;
        cur += node->val;   // 根到当前节点的前缀和
        int res = cnt.count(cur - target) ? cnt[cur - target] : 0;
        ++cnt[cur];                       // 登记后再进入子树
        res += dfs(node->left, cur, target);
        res += dfs(node->right, cur, target);
        --cnt[cur];                       // 回溯：撤销登记
        return res;
    }

public:
    int pathSum(TreeNode* root, int targetSum) {
        cnt.clear();
        cnt[0] = 1;  // 空路径：根之前的“空前缀”
        return dfs(root, 0, targetSum);
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(n)`（哈希表 + 递归栈）

## ⚠️ 易错点

- **溢出**：节点值绝对值可达 `10^9`，路径最长 1000 个节点，自上而下累加的和远超 `int` 范围，必须用 `long long`（大量错误提交源于此）。
- **回溯不能漏**：`--cnt[cur]` 必须在递归完左右子树后执行，否则兄弟分支的前缀和会被误当作祖先，导致多算。
- **`cnt[0] = 1` 不能漏**：它对应「空前缀」，漏掉会少算所有从根节点开始的路径。
- **先查询后登记**：若先把 `cur` 登记再查询，当 `target == 0` 时会把「节点到自身」的空路径也计入，答案偏大。

---

[← 返回目录](../../README.md)
