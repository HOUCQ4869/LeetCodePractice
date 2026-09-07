<div align="center">

# 🧩 LeetCodePractice

**简体中文** | [**English**](README.en.md)

[![Language](https://img.shields.io/badge/Language-C%2B%2B-00599C?style=flat-square&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Standard](https://img.shields.io/badge/Standard-C%2B%2B17-00599C?style=flat-square)](https://en.cppreference.com/w/cpp/17)
[![Platform](https://img.shields.io/badge/Platform-LeetCode-FFA116?style=flat-square&logo=leetcode&logoColor=black)](https://leetcode.cn/)
[![Hot100](https://img.shields.io/badge/Hot%20100-100%2F100%20%E5%B7%B2%E5%AE%8C%E6%88%90-brightgreen?style=flat-square)](#-刷题进度)
[![License](https://img.shields.io/badge/License-MIT-green?style=flat-square)](LICENSE)

</div>

> 🚀 LeetCode 刷题记录仓库，使用 C++ 解题。**已覆盖 LeetCode Hot 100 全部题目**：每题附带独立题解文档（多解法对比、复杂度分析、易错点）与可直接提交的 C++ 源码，方便系统性复盘。

## 📂 目录结构

```text
LeetCodePractice/
├── README.md            # 中文说明
├── README.en.md         # 英文说明
├── problems/            # 题目文档（每题一个文件夹，多解法对比）
│   ├── 0001-two-sum/
│   │   └── README.md    # 题目描述 + 2~3 个解法 + 易错点
│   └── ...
├── solutions/           # 题解源码（LeetCode 提交格式，仅 Solution 类）
│   ├── 0001-two-sum.cpp
│   └── ...
└── notes/               # 算法专题笔记（按标签整理）
```

## 📊 刷题进度

> 🎯 目标：LeetCode Hot 100
>
> **总进度**：`██████████ 100 / 100` ✅
>
> 🟢 简单 **21** ｜ 🟡 中等 **66** ｜ 🔴 困难 **13**

### 🔢 哈希

| # | 题目 | 难度 | 标签 | 题解 | 代码 |
|:-:|:-----|:---:|:-----|:--:|:--:|
| 1 | [两数之和](https://leetcode.cn/problems/two-sum/) | 🟢 | `哈希表` | [📝](problems/0001-two-sum/README.md) | [⚡](solutions/0001-two-sum.cpp) |
| 49 | [字母异位词分组](https://leetcode.cn/problems/group-anagrams/) | 🟡 | `哈希表` `字符串` | [📝](problems/0049-group-anagrams/README.md) | [⚡](solutions/0049-group-anagrams.cpp) |
| 128 | [最长连续序列](https://leetcode.cn/problems/longest-consecutive-sequence/) | 🟡 | `哈希表` `并查集` | [📝](problems/0128-longest-consecutive-sequence/README.md) | [⚡](solutions/0128-longest-consecutive-sequence.cpp) |

### 🎯 双指针

| # | 题目 | 难度 | 标签 | 题解 | 代码 |
|:-:|:-----|:---:|:-----|:--:|:--:|
| 283 | [移动零](https://leetcode.cn/problems/move-zeroes/) | 🟢 | `双指针` | [📝](problems/0283-move-zeroes/README.md) | [⚡](solutions/0283-move-zeroes.cpp) |
| 11 | [盛最多水的容器](https://leetcode.cn/problems/container-with-most-water/) | 🟡 | `双指针` `贪心` | [📝](problems/0011-container-with-most-water/README.md) | [⚡](solutions/0011-container-with-most-water.cpp) |
| 15 | [三数之和](https://leetcode.cn/problems/3sum/) | 🟡 | `双指针` `排序` | [📝](problems/0015-3sum/README.md) | [⚡](solutions/0015-3sum.cpp) |
| 42 | [接雨水](https://leetcode.cn/problems/trapping-rain-water/) | 🔴 | `双指针` `动态规划` | [📝](problems/0042-trapping-rain-water/README.md) | [⚡](solutions/0042-trapping-rain-water.cpp) |

### 🪟 滑动窗口

| # | 题目 | 难度 | 标签 | 题解 | 代码 |
|:-:|:-----|:---:|:-----|:--:|:--:|
| 3 | [无重复字符的最长子串](https://leetcode.cn/problems/longest-substring-without-repeating-characters/) | 🟡 | `滑动窗口` `哈希表` | [📝](problems/0003-longest-substring-without-repeating-characters/README.md) | [⚡](solutions/0003-longest-substring-without-repeating-characters.cpp) |
| 438 | [找到字符串中所有字母异位词](https://leetcode.cn/problems/find-all-anagrams-in-a-string/) | 🟡 | `滑动窗口` `哈希表` | [📝](problems/0438-find-all-anagrams-in-a-string/README.md) | [⚡](solutions/0438-find-all-anagrams-in-a-string.cpp) |

### 🧵 子串

| # | 题目 | 难度 | 标签 | 题解 | 代码 |
|:-:|:-----|:---:|:-----|:--:|:--:|
| 560 | [和为 K 的子数组](https://leetcode.cn/problems/subarray-sum-equals-k/) | 🟡 | `前缀和` `哈希表` | [📝](problems/0560-subarray-sum-equals-k/README.md) | [⚡](solutions/0560-subarray-sum-equals-k.cpp) |
| 239 | [滑动窗口最大值](https://leetcode.cn/problems/sliding-window-maximum/) | 🔴 | `单调队列` | [📝](problems/0239-sliding-window-maximum/README.md) | [⚡](solutions/0239-sliding-window-maximum.cpp) |
| 76 | [最小覆盖子串](https://leetcode.cn/problems/minimum-window-substring/) | 🔴 | `滑动窗口` `哈希表` | [📝](problems/0076-minimum-window-substring/README.md) | [⚡](solutions/0076-minimum-window-substring.cpp) |

### 📦 普通数组

| # | 题目 | 难度 | 标签 | 题解 | 代码 |
|:-:|:-----|:---:|:-----|:--:|:--:|
| 53 | [最大子数组和](https://leetcode.cn/problems/maximum-subarray/) | 🟡 | `动态规划` `分治` | [📝](problems/0053-maximum-subarray/README.md) | [⚡](solutions/0053-maximum-subarray.cpp) |
| 56 | [合并区间](https://leetcode.cn/problems/merge-intervals/) | 🟡 | `排序` `数组` | [📝](problems/0056-merge-intervals/README.md) | [⚡](solutions/0056-merge-intervals.cpp) |
| 189 | [轮转数组](https://leetcode.cn/problems/rotate-array/) | 🟡 | `数组` `数学` | [📝](problems/0189-rotate-array/README.md) | [⚡](solutions/0189-rotate-array.cpp) |
| 238 | [除自身以外数组的乘积](https://leetcode.cn/problems/product-of-array-except-self/) | 🟡 | `前缀和` | [📝](problems/0238-product-of-array-except-self/README.md) | [⚡](solutions/0238-product-of-array-except-self.cpp) |
| 41 | [缺失的第一个正数](https://leetcode.cn/problems/first-missing-positive/) | 🔴 | `哈希表` `原地交换` | [📝](problems/0041-first-missing-positive/README.md) | [⚡](solutions/0041-first-missing-positive.cpp) |

### 🧮 矩阵

| # | 题目 | 难度 | 标签 | 题解 | 代码 |
|:-:|:-----|:---:|:-----|:--:|:--:|
| 73 | [矩阵置零](https://leetcode.cn/problems/set-matrix-zeroes/) | 🟡 | `矩阵` `哈希表` | [📝](problems/0073-set-matrix-zeroes/README.md) | [⚡](solutions/0073-set-matrix-zeroes.cpp) |
| 54 | [螺旋矩阵](https://leetcode.cn/problems/spiral-matrix/) | 🟡 | `矩阵` `模拟` | [📝](problems/0054-spiral-matrix/README.md) | [⚡](solutions/0054-spiral-matrix.cpp) |
| 48 | [旋转图像](https://leetcode.cn/problems/rotate-image/) | 🟡 | `矩阵` `数学` | [📝](problems/0048-rotate-image/README.md) | [⚡](solutions/0048-rotate-image.cpp) |
| 240 | [搜索二维矩阵 II](https://leetcode.cn/problems/search-a-2d-matrix-ii/) | 🟡 | `二分查找` `分治` | [📝](problems/0240-search-a-2d-matrix-ii/README.md) | [⚡](solutions/0240-search-a-2d-matrix-ii.cpp) |

### 🔗 链表

| # | 题目 | 难度 | 标签 | 题解 | 代码 |
|:-:|:-----|:---:|:-----|:--:|:--:|
| 160 | [相交链表](https://leetcode.cn/problems/intersection-of-two-linked-lists/) | 🟢 | `链表` `双指针` | [📝](problems/0160-intersection-of-two-linked-lists/README.md) | [⚡](solutions/0160-intersection-of-two-linked-lists.cpp) |
| 206 | [反转链表](https://leetcode.cn/problems/reverse-linked-list/) | 🟢 | `链表` `递归` | [📝](problems/0206-reverse-linked-list/README.md) | [⚡](solutions/0206-reverse-linked-list.cpp) |
| 234 | [回文链表](https://leetcode.cn/problems/palindrome-linked-list/) | 🟢 | `链表` `双指针` | [📝](problems/0234-palindrome-linked-list/README.md) | [⚡](solutions/0234-palindrome-linked-list.cpp) |
| 141 | [环形链表](https://leetcode.cn/problems/linked-list-cycle/) | 🟢 | `链表` `双指针` | [📝](problems/0141-linked-list-cycle/README.md) | [⚡](solutions/0141-linked-list-cycle.cpp) |
| 142 | [环形链表 II](https://leetcode.cn/problems/linked-list-cycle-ii/) | 🟡 | `链表` `双指针` | [📝](problems/0142-linked-list-cycle-ii/README.md) | [⚡](solutions/0142-linked-list-cycle-ii.cpp) |
| 21 | [合并两个有序链表](https://leetcode.cn/problems/merge-two-sorted-lists/) | 🟢 | `链表` `递归` | [📝](problems/0021-merge-two-sorted-lists/README.md) | [⚡](solutions/0021-merge-two-sorted-lists.cpp) |
| 2 | [两数相加](https://leetcode.cn/problems/add-two-numbers/) | 🟡 | `链表` `数学` | [📝](problems/0002-add-two-numbers/README.md) | [⚡](solutions/0002-add-two-numbers.cpp) |
| 19 | [删除链表的倒数第 N 个结点](https://leetcode.cn/problems/remove-nth-node-from-end-of-list/) | 🟡 | `链表` `双指针` | [📝](problems/0019-remove-nth-node-from-end-of-list/README.md) | [⚡](solutions/0019-remove-nth-node-from-end-of-list.cpp) |
| 24 | [两两交换链表中的节点](https://leetcode.cn/problems/swap-nodes-in-pairs/) | 🟡 | `链表` `递归` | [📝](problems/0024-swap-nodes-in-pairs/README.md) | [⚡](solutions/0024-swap-nodes-in-pairs.cpp) |
| 25 | [K 个一组翻转链表](https://leetcode.cn/problems/reverse-nodes-in-k-group/) | 🔴 | `链表` `递归` | [📝](problems/0025-reverse-nodes-in-k-group/README.md) | [⚡](solutions/0025-reverse-nodes-in-k-group.cpp) |
| 138 | [随机链表的复制](https://leetcode.cn/problems/copy-list-with-random-pointer/) | 🟡 | `链表` `哈希表` | [📝](problems/0138-copy-list-with-random-pointer/README.md) | [⚡](solutions/0138-copy-list-with-random-pointer.cpp) |
| 148 | [排序链表](https://leetcode.cn/problems/sort-list/) | 🟡 | `链表` `归并排序` | [📝](problems/0148-sort-list/README.md) | [⚡](solutions/0148-sort-list.cpp) |
| 23 | [合并 K 个升序链表](https://leetcode.cn/problems/merge-k-sorted-lists/) | 🔴 | `链表` `堆` `分治` | [📝](problems/0023-merge-k-sorted-lists/README.md) | [⚡](solutions/0023-merge-k-sorted-lists.cpp) |
| 146 | [LRU 缓存](https://leetcode.cn/problems/lru-cache/) | 🟡 | `设计` `哈希表` `双向链表` | [📝](problems/0146-lru-cache/README.md) | [⚡](solutions/0146-lru-cache.cpp) |

### 🌳 二叉树

| # | 题目 | 难度 | 标签 | 题解 | 代码 |
|:-:|:-----|:---:|:-----|:--:|:--:|
| 94 | [二叉树的中序遍历](https://leetcode.cn/problems/binary-tree-inorder-traversal/) | 🟢 | `树` `栈` | [📝](problems/0094-binary-tree-inorder-traversal/README.md) | [⚡](solutions/0094-binary-tree-inorder-traversal.cpp) |
| 104 | [二叉树的最大深度](https://leetcode.cn/problems/maximum-depth-of-binary-tree/) | 🟢 | `树` `DFS` | [📝](problems/0104-maximum-depth-of-binary-tree/README.md) | [⚡](solutions/0104-maximum-depth-of-binary-tree.cpp) |
| 226 | [翻转二叉树](https://leetcode.cn/problems/invert-binary-tree/) | 🟢 | `树` `DFS` | [📝](problems/0226-invert-binary-tree/README.md) | [⚡](solutions/0226-invert-binary-tree.cpp) |
| 101 | [对称二叉树](https://leetcode.cn/problems/symmetric-tree/) | 🟢 | `树` `DFS` `BFS` | [📝](problems/0101-symmetric-tree/README.md) | [⚡](solutions/0101-symmetric-tree.cpp) |
| 543 | [二叉树的直径](https://leetcode.cn/problems/diameter-of-binary-tree/) | 🟢 | `树` `DFS` | [📝](problems/0543-diameter-of-binary-tree/README.md) | [⚡](solutions/0543-diameter-of-binary-tree.cpp) |
| 102 | [二叉树的层序遍历](https://leetcode.cn/problems/binary-tree-level-order-traversal/) | 🟡 | `树` `BFS` | [📝](problems/0102-binary-tree-level-order-traversal/README.md) | [⚡](solutions/0102-binary-tree-level-order-traversal.cpp) |
| 108 | [将有序数组转换为二叉搜索树](https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree/) | 🟢 | `树` `二分查找` | [📝](problems/0108-convert-sorted-array-to-binary-search-tree/README.md) | [⚡](solutions/0108-convert-sorted-array-to-binary-search-tree.cpp) |
| 98 | [验证二叉搜索树](https://leetcode.cn/problems/validate-binary-search-tree/) | 🟡 | `树` `DFS` | [📝](problems/0098-validate-binary-search-tree/README.md) | [⚡](solutions/0098-validate-binary-search-tree.cpp) |
| 230 | [二叉搜索树中第 K 小的元素](https://leetcode.cn/problems/kth-smallest-element-in-a-bst/) | 🟡 | `树` `中序遍历` | [📝](problems/0230-kth-smallest-element-in-a-bst/README.md) | [⚡](solutions/0230-kth-smallest-element-in-a-bst.cpp) |
| 199 | [二叉树的右视图](https://leetcode.cn/problems/binary-tree-right-side-view/) | 🟡 | `树` `DFS` `BFS` | [📝](problems/0199-binary-tree-right-side-view/README.md) | [⚡](solutions/0199-binary-tree-right-side-view.cpp) |
| 114 | [二叉树展开为链表](https://leetcode.cn/problems/flatten-binary-tree-to-linked-list/) | 🟡 | `树` `DFS` | [📝](problems/0114-flatten-binary-tree-to-linked-list/README.md) | [⚡](solutions/0114-flatten-binary-tree-to-linked-list.cpp) |
| 105 | [从前序与中序遍历序列构造二叉树](https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/) | 🟡 | `树` `分治` | [📝](problems/0105-construct-binary-tree-from-preorder-and-inorder-traversal/README.md) | [⚡](solutions/0105-construct-binary-tree-from-preorder-and-inorder-traversal.cpp) |
| 437 | [路径总和 III](https://leetcode.cn/problems/path-sum-iii/) | 🟡 | `树` `前缀和` | [📝](problems/0437-path-sum-iii/README.md) | [⚡](solutions/0437-path-sum-iii.cpp) |
| 236 | [二叉树的最近公共祖先](https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/) | 🟡 | `树` `DFS` | [📝](problems/0236-lowest-common-ancestor-of-a-binary-tree/README.md) | [⚡](solutions/0236-lowest-common-ancestor-of-a-binary-tree.cpp) |
| 124 | [二叉树中的最大路径和](https://leetcode.cn/problems/binary-tree-maximum-path-sum/) | 🔴 | `树` `DFS` | [📝](problems/0124-binary-tree-maximum-path-sum/README.md) | [⚡](solutions/0124-binary-tree-maximum-path-sum.cpp) |

### 🕸️ 图论

| # | 题目 | 难度 | 标签 | 题解 | 代码 |
|:-:|:-----|:---:|:-----|:--:|:--:|
| 200 | [岛屿数量](https://leetcode.cn/problems/number-of-islands/) | 🟡 | `图` `DFS` `并查集` | [📝](problems/0200-number-of-islands/README.md) | [⚡](solutions/0200-number-of-islands.cpp) |
| 994 | [腐烂的橘子](https://leetcode.cn/problems/rotting-oranges/) | 🟡 | `图` `BFS` | [📝](problems/0994-rotting-oranges/README.md) | [⚡](solutions/0994-rotting-oranges.cpp) |
| 207 | [课程表](https://leetcode.cn/problems/course-schedule/) | 🟡 | `图` `拓扑排序` | [📝](problems/0207-course-schedule/README.md) | [⚡](solutions/0207-course-schedule.cpp) |
| 208 | [实现 Trie（前缀树）](https://leetcode.cn/problems/implement-trie-prefix-tree/) | 🟡 | `设计` `树` | [📝](problems/0208-implement-trie-prefix-tree/README.md) | [⚡](solutions/0208-implement-trie-prefix-tree.cpp) |

### 🔙 回溯

| # | 题目 | 难度 | 标签 | 题解 | 代码 |
|:-:|:-----|:---:|:-----|:--:|:--:|
| 46 | [全排列](https://leetcode.cn/problems/permutations/) | 🟡 | `回溯` | [📝](problems/0046-permutations/README.md) | [⚡](solutions/0046-permutations.cpp) |
| 78 | [子集](https://leetcode.cn/problems/subsets/) | 🟡 | `回溯` `位运算` | [📝](problems/0078-subsets/README.md) | [⚡](solutions/0078-subsets.cpp) |
| 17 | [电话号码的字母组合](https://leetcode.cn/problems/letter-combinations-of-a-phone-number/) | 🟡 | `回溯` `哈希表` | [📝](problems/0017-letter-combinations-of-a-phone-number/README.md) | [⚡](solutions/0017-letter-combinations-of-a-phone-number.cpp) |
| 39 | [组合总和](https://leetcode.cn/problems/combination-sum/) | 🟡 | `回溯` | [📝](problems/0039-combination-sum/README.md) | [⚡](solutions/0039-combination-sum.cpp) |
| 22 | [括号生成](https://leetcode.cn/problems/generate-parentheses/) | 🟡 | `回溯` | [📝](problems/0022-generate-parentheses/README.md) | [⚡](solutions/0022-generate-parentheses.cpp) |
| 79 | [单词搜索](https://leetcode.cn/problems/word-search/) | 🟡 | `回溯` | [📝](problems/0079-word-search/README.md) | [⚡](solutions/0079-word-search.cpp) |
| 131 | [分割回文串](https://leetcode.cn/problems/palindrome-partitioning/) | 🟡 | `回溯` `动态规划` | [📝](problems/0131-palindrome-partitioning/README.md) | [⚡](solutions/0131-palindrome-partitioning.cpp) |
| 51 | [N 皇后](https://leetcode.cn/problems/n-queens/) | 🔴 | `回溯` | [📝](problems/0051-n-queens/README.md) | [⚡](solutions/0051-n-queens.cpp) |

### 🔍 二分查找

| # | 题目 | 难度 | 标签 | 题解 | 代码 |
|:-:|:-----|:---:|:-----|:--:|:--:|
| 35 | [搜索插入位置](https://leetcode.cn/problems/search-insert-position/) | 🟢 | `二分查找` | [📝](problems/0035-search-insert-position/README.md) | [⚡](solutions/0035-search-insert-position.cpp) |
| 74 | [搜索二维矩阵](https://leetcode.cn/problems/search-a-2d-matrix/) | 🟡 | `二分查找` | [📝](problems/0074-search-a-2d-matrix/README.md) | [⚡](solutions/0074-search-a-2d-matrix.cpp) |
| 34 | [在排序数组中查找元素的第一个和最后一个位置](https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/) | 🟡 | `二分查找` | [📝](problems/0034-find-first-and-last-position-of-element-in-sorted-array/README.md) | [⚡](solutions/0034-find-first-and-last-position-of-element-in-sorted-array.cpp) |
| 33 | [搜索旋转排序数组](https://leetcode.cn/problems/search-in-rotated-sorted-array/) | 🟡 | `二分查找` | [📝](problems/0033-search-in-rotated-sorted-array/README.md) | [⚡](solutions/0033-search-in-rotated-sorted-array.cpp) |
| 153 | [寻找旋转排序数组中的最小值](https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array/) | 🟡 | `二分查找` | [📝](problems/0153-find-minimum-in-rotated-sorted-array/README.md) | [⚡](solutions/0153-find-minimum-in-rotated-sorted-array.cpp) |
| 4 | [寻找两个正序数组的中位数](https://leetcode.cn/problems/median-of-two-sorted-arrays/) | 🔴 | `二分查找` | [📝](problems/0004-median-of-two-sorted-arrays/README.md) | [⚡](solutions/0004-median-of-two-sorted-arrays.cpp) |

### 🥞 栈

| # | 题目 | 难度 | 标签 | 题解 | 代码 |
|:-:|:-----|:---:|:-----|:--:|:--:|
| 20 | [有效的括号](https://leetcode.cn/problems/valid-parentheses/) | 🟢 | `栈` | [📝](problems/0020-valid-parentheses/README.md) | [⚡](solutions/0020-valid-parentheses.cpp) |
| 155 | [最小栈](https://leetcode.cn/problems/min-stack/) | 🟢 | `栈` `设计` | [📝](problems/0155-min-stack/README.md) | [⚡](solutions/0155-min-stack.cpp) |
| 394 | [字符串解码](https://leetcode.cn/problems/decode-string/) | 🟡 | `栈` | [📝](problems/0394-decode-string/README.md) | [⚡](solutions/0394-decode-string.cpp) |
| 739 | [每日温度](https://leetcode.cn/problems/daily-temperatures/) | 🟡 | `单调栈` | [📝](problems/0739-daily-temperatures/README.md) | [⚡](solutions/0739-daily-temperatures.cpp) |
| 84 | [柱状图中最大的矩形](https://leetcode.cn/problems/largest-rectangle-in-histogram/) | 🔴 | `单调栈` | [📝](problems/0084-largest-rectangle-in-histogram/README.md) | [⚡](solutions/0084-largest-rectangle-in-histogram.cpp) |

### ⛰️ 堆

| # | 题目 | 难度 | 标签 | 题解 | 代码 |
|:-:|:-----|:---:|:-----|:--:|:--:|
| 215 | [数组中的第K个最大元素](https://leetcode.cn/problems/kth-largest-element-in-an-array/) | 🟡 | `堆` `快速选择` | [📝](problems/0215-kth-largest-element-in-an-array/README.md) | [⚡](solutions/0215-kth-largest-element-in-an-array.cpp) |
| 347 | [前 K 个高频元素](https://leetcode.cn/problems/top-k-frequent-elements/) | 🟡 | `堆` `哈希表` | [📝](problems/0347-top-k-frequent-elements/README.md) | [⚡](solutions/0347-top-k-frequent-elements.cpp) |
| 295 | [数据流的中位数](https://leetcode.cn/problems/find-median-from-data-stream/) | 🔴 | `堆` `设计` | [📝](problems/0295-find-median-from-data-stream/README.md) | [⚡](solutions/0295-find-median-from-data-stream.cpp) |

### 💰 贪心

| # | 题目 | 难度 | 标签 | 题解 | 代码 |
|:-:|:-----|:---:|:-----|:--:|:--:|
| 121 | [买卖股票的最佳时机](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/) | 🟢 | `贪心` `动态规划` | [📝](problems/0121-best-time-to-buy-and-sell-stock/README.md) | [⚡](solutions/0121-best-time-to-buy-and-sell-stock.cpp) |
| 55 | [跳跃游戏](https://leetcode.cn/problems/jump-game/) | 🟡 | `贪心` | [📝](problems/0055-jump-game/README.md) | [⚡](solutions/0055-jump-game.cpp) |
| 45 | [跳跃游戏 II](https://leetcode.cn/problems/jump-game-ii/) | 🟡 | `贪心` | [📝](problems/0045-jump-game-ii/README.md) | [⚡](solutions/0045-jump-game-ii.cpp) |
| 763 | [划分字母区间](https://leetcode.cn/problems/partition-labels/) | 🟡 | `贪心` `哈希表` | [📝](problems/0763-partition-labels/README.md) | [⚡](solutions/0763-partition-labels.cpp) |

### 🏃 动态规划

| # | 题目 | 难度 | 标签 | 题解 | 代码 |
|:-:|:-----|:---:|:-----|:--:|:--:|
| 70 | [爬楼梯](https://leetcode.cn/problems/climbing-stairs/) | 🟢 | `动态规划` | [📝](problems/0070-climbing-stairs/README.md) | [⚡](solutions/0070-climbing-stairs.cpp) |
| 118 | [杨辉三角](https://leetcode.cn/problems/pascals-triangle/) | 🟢 | `动态规划` `数组` | [📝](problems/0118-pascals-triangle/README.md) | [⚡](solutions/0118-pascals-triangle.cpp) |
| 198 | [打家劫舍](https://leetcode.cn/problems/house-robber/) | 🟡 | `动态规划` | [📝](problems/0198-house-robber/README.md) | [⚡](solutions/0198-house-robber.cpp) |
| 279 | [完全平方数](https://leetcode.cn/problems/perfect-squares/) | 🟡 | `动态规划` `BFS` | [📝](problems/0279-perfect-squares/README.md) | [⚡](solutions/0279-perfect-squares.cpp) |
| 322 | [零钱兑换](https://leetcode.cn/problems/coin-change/) | 🟡 | `动态规划` `BFS` | [📝](problems/0322-coin-change/README.md) | [⚡](solutions/0322-coin-change.cpp) |
| 139 | [单词拆分](https://leetcode.cn/problems/word-break/) | 🟡 | `动态规划` `哈希表` | [📝](problems/0139-word-break/README.md) | [⚡](solutions/0139-word-break.cpp) |
| 300 | [最长递增子序列](https://leetcode.cn/problems/longest-increasing-subsequence/) | 🟡 | `动态规划` `二分查找` | [📝](problems/0300-longest-increasing-subsequence/README.md) | [⚡](solutions/0300-longest-increasing-subsequence.cpp) |
| 152 | [乘积最大子数组](https://leetcode.cn/problems/maximum-product-subarray/) | 🟡 | `动态规划` | [📝](problems/0152-maximum-product-subarray/README.md) | [⚡](solutions/0152-maximum-product-subarray.cpp) |
| 416 | [分割等和子集](https://leetcode.cn/problems/partition-equal-subset-sum/) | 🟡 | `动态规划` `背包` | [📝](problems/0416-partition-equal-subset-sum/README.md) | [⚡](solutions/0416-partition-equal-subset-sum.cpp) |
| 32 | [最长有效括号](https://leetcode.cn/problems/longest-valid-parentheses/) | 🔴 | `动态规划` `栈` | [📝](problems/0032-longest-valid-parentheses/README.md) | [⚡](solutions/0032-longest-valid-parentheses.cpp) |

### 🧩 多维动态规划

| # | 题目 | 难度 | 标签 | 题解 | 代码 |
|:-:|:-----|:---:|:-----|:--:|:--:|
| 62 | [不同路径](https://leetcode.cn/problems/unique-paths/) | 🟡 | `动态规划` `数学` | [📝](problems/0062-unique-paths/README.md) | [⚡](solutions/0062-unique-paths.cpp) |
| 64 | [最小路径和](https://leetcode.cn/problems/minimum-path-sum/) | 🟡 | `动态规划` `矩阵` | [📝](problems/0064-minimum-path-sum/README.md) | [⚡](solutions/0064-minimum-path-sum.cpp) |
| 5 | [最长回文子串](https://leetcode.cn/problems/longest-palindromic-substring/) | 🟡 | `动态规划` `中心扩展` | [📝](problems/0005-longest-palindromic-substring/README.md) | [⚡](solutions/0005-longest-palindromic-substring.cpp) |
| 1143 | [最长公共子序列](https://leetcode.cn/problems/longest-common-subsequence/) | 🟡 | `动态规划` `字符串` | [📝](problems/1143-longest-common-subsequence/README.md) | [⚡](solutions/1143-longest-common-subsequence.cpp) |
| 72 | [编辑距离](https://leetcode.cn/problems/edit-distance/) | 🔴 | `动态规划` `字符串` | [📝](problems/0072-edit-distance/README.md) | [⚡](solutions/0072-edit-distance.cpp) |

### ✨ 技巧

| # | 题目 | 难度 | 标签 | 题解 | 代码 |
|:-:|:-----|:---:|:-----|:--:|:--:|
| 136 | [只出现一次的数字](https://leetcode.cn/problems/single-number/) | 🟢 | `位运算` | [📝](problems/0136-single-number/README.md) | [⚡](solutions/0136-single-number.cpp) |
| 169 | [多数元素](https://leetcode.cn/problems/majority-element/) | 🟢 | `哈希表` `摩尔投票` | [📝](problems/0169-majority-element/README.md) | [⚡](solutions/0169-majority-element.cpp) |
| 75 | [颜色分类](https://leetcode.cn/problems/sort-colors/) | 🟡 | `双指针` | [📝](problems/0075-sort-colors/README.md) | [⚡](solutions/0075-sort-colors.cpp) |
| 31 | [下一个排列](https://leetcode.cn/problems/next-permutation/) | 🟡 | `数组` `双指针` | [📝](problems/0031-next-permutation/README.md) | [⚡](solutions/0031-next-permutation.cpp) |
| 287 | [寻找重复数](https://leetcode.cn/problems/find-the-duplicate-number/) | 🟡 | `二分查找` `快慢指针` | [📝](problems/0287-find-the-duplicate-number/README.md) | [⚡](solutions/0287-find-the-duplicate-number.cpp) |

## ⚙️ 使用方法

题解源码为 **LeetCode 提交格式**（仅 `Solution` 类），可直接粘贴至 LeetCode 在线提交：

```bash
# 本地语法检查（无需额外依赖）
g++ -std=c++17 -fsyntax-only solutions/0001-two-sum.cpp
```

📖 **阅读建议**：先看 `problems/{题号-slug}/README.md` 中的多解法对比（由易到优、含复杂度与易错点），再对照 `solutions/` 中的推荐解法源码。

## 📌 记录规范

- **文件命名**：`solutions/{题号四位}-{题名slug}.cpp`；题解文档位于 `problems/{题号四位}-{题名slug}/README.md`
- **源码头部注释**：包含题目链接、解法名、思路简述、时间/空间复杂度
- **题解文档**：题目描述 + 示例约束 + 2~3 个解法（由易到优，最优解标注「推荐」）+ 易错点
- **提交信息**：`solve: {题号} {题名}`，如 `solve: 0001 两数之和`
- **同步更新**：每解一题，更新「📊 刷题进度」表对应分类

---

<p align="center">
  🌐 语言 / Language：
  <a href="README.md">🇨🇳 <b>简体中文</b></a> ｜
  <a href="README.en.md">🇺🇸 English</a>
</p>
