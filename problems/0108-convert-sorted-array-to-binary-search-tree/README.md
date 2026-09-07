# 108. 将有序数组转换为二叉搜索树

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree/) ｜ [国际站](https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/)
>
> 🟢 简单 ｜ 标签：`树` `二分查找`

## 📝 题目描述

给定一个整数数组 `nums`，其中元素已按**严格递增**顺序排序，请将其转换为一棵**高度平衡**的二叉搜索树（BST），并返回这棵树的根节点。

- 二叉搜索树（BST）：任意节点的左子树上所有节点值都**严格小于**该节点，右子树上所有节点值都**严格大于**该节点；
- 高度平衡：任意节点的左右子树高度差的绝对值不超过 `1`。

有序数组本质上就是某棵 BST 的中序遍历结果，因此满足条件的 BST 不止一棵，返回任意一棵均可。

**示例 1：**

```
输入：nums = [-10,-3,0,5,9]
输出：[0,-3,9,-10,null,5]
解释：一种可行的树形：根为 0；左子树含 -10、-3，右子树含 5、9。
      层序表示 [0,-3,9,-10,null,5]：0 的左孩子是 -3、右孩子是 9；
      -3 的左孩子是 -10，9 的左孩子是 5。
```

**示例 2：**

```
输入：nums = [1,3]
输出：[3,1]
解释：[3,1] 与 [1,null,3] 都是高度平衡的 BST，返回任意一个均可。
```

**提示：**

- `1 <= nums.length <= 10^4`
- `-10^4 <= nums[i] <= 10^4`
- `nums` 按严格递增顺序排列

## 💡 题解

### 解法一：递归分治——拷贝子数组

**思路**：数组有序，所以「取中点为根」天然满足 BST 性质（左侧元素都小、右侧元素都大），同时让左右两半长度尽量接近，从而保证高度平衡。具体做法：取当前区间的中点元素作为根节点，再对中点左侧、右侧两段子数组分别递归构建左右子树。本解法为了直观，每层递归直接用 `vector` 拷贝出子数组传入，写法简单，但带来了额外的时间与空间开销。

```cpp
#include <vector>

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return build(nums);
    }

private:
    TreeNode* build(vector<int> nums) {  // 传值，自动拷贝出子数组
        if (nums.empty()) return nullptr;
        int mid = nums.size() / 2;
        auto* root = new TreeNode(nums[mid]);
        root->left = build(vector<int>(nums.begin(), nums.begin() + mid));
        root->right = build(vector<int>(nums.begin() + mid + 1, nums.end()));
        return root;
    }
};
```

- ⏱️ 时间复杂度：`O(n log n)`（每层递归合计拷贝约 `n` 个元素，共约 `log n` 层）
- 💾 空间复杂度：`O(n)`（某一时刻活跃的子数组拷贝总量为 `n/2 + n/4 + ... = O(n)`，不计输出树本身）

### 解法二：递归分治——传递下标区间（推荐）

**思路**：与解法一相同的分治策略，但递归时只传子数组的下标区间 `[lo, hi)`（左闭右开），不再拷贝数组，所有访问都直接作用在原数组上。取中点 `mid = lo + (hi - lo) / 2` 作为根，再递归构建 `[lo, mid)` 与 `[mid + 1, hi)` 两段。数组严格递增保证区间内无重复值，以中点为根一定合法；两侧长度差不超过 `1`，递归得到的树必然高度平衡。

```cpp
#include <vector>

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return build(nums, 0, static_cast<int>(nums.size()));  // [0, n)
    }

private:
    TreeNode* build(vector<int>& nums, int lo, int hi) {
        if (lo >= hi) return nullptr;        // 空区间，没有子树
        int mid = lo + (hi - lo) / 2;        // 中点作根，保证左右平衡
        auto* root = new TreeNode(nums[mid]);
        root->left = build(nums, lo, mid);   // 严格小于根的部分
        root->right = build(nums, mid + 1, hi);
        return root;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`（每个元素只被访问一次、恰好新建一个节点）
- 💾 空间复杂度：`O(log n)`（递归栈深度等于树高，而树是平衡的）

## ⚠️ 易错点

- 只保证是 BST 并不够：若每次都取区间第一个元素作根，会退化成一条右斜链——虽是合法 BST 但不满足「高度平衡」，必须取**中点**作根。
- 递归区间定义要自洽：左闭右开与左闭右闭混用容易漏掉或多算一个元素，`mid` 的归属要和区间定义一致。
- 空区间必须返回 `nullptr`：虽然题目保证 `n >= 1`，但递归边界一定会出现空区间，漏判会导致数组越界或空指针崩溃。
- 中点写成 `(lo + hi) / 2` 在本题（下标不超过 `10^4`）不会溢出，但 `lo + (hi - lo) / 2` 是更稳妥的通用习惯。

---

[← 返回目录](../../README.md)
