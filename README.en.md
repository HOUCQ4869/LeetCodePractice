<div align="center">

# 🧩 LeetCodePractice

[**简体中文**](README.md) | [**English**]

[![Language](https://img.shields.io/badge/Language-C%2B%2B-00599C?style=flat-square&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Standard](https://img.shields.io/badge/Standard-C%2B%2B17-00599C?style=flat-square)](https://en.cppreference.com/w/cpp/17)
[![Platform](https://img.shields.io/badge/Platform-LeetCode-FFA116?style=flat-square&logo=leetcode&logoColor=black)](https://leetcode.com/)
[![Hot100](https://img.shields.io/badge/Hot%20100-100%2F100%20Solved-brightgreen?style=flat-square)](#-progress)
[![License](https://img.shields.io/badge/License-MIT-green?style=flat-square)](LICENSE)

</div>

> 🚀 A repository for tracking LeetCode practice, with all solutions written in C++. **All 100 problems from LeetCode Hot 100 are covered**: each one comes with a dedicated write-up (multi-solution comparison, complexity analysis, common pitfalls) and a ready-to-submit C++ solution, making it easy to review systematically.

> 🇨🇳 **Note**: The per-problem write-ups under `problems/` are written in Chinese.

## 📂 Directory Structure

```text
LeetCodePractice/
├── README.md            # Chinese docs
├── README.en.md         # English docs
├── problems/            # Problem write-ups (one folder per problem)
│   ├── 0001-two-sum/
│   │   └── README.md    # Description + 2~3 solutions + pitfalls (in Chinese)
│   └── ...
├── solutions/           # Solution sources (LeetCode submission format, Solution class only)
│   ├── 0001-two-sum.cpp
│   └── ...
└── notes/               # Topic notes (organized by tag)
```

## 📊 Progress

> 🎯 Goal: LeetCode Hot 100
>
> **Overall**: `██████████ 100 / 100` ✅
>
> 🟢 Easy **21** ｜ 🟡 Medium **66** ｜ 🔴 Hard **13**

### 🔢 Hash

| # | Problem | Difficulty | Tags | Write-up | Code |
|:-:|:--------|:----------:|:-----|:--:|:--:|
| 1 | [Two Sum](https://leetcode.com/problems/two-sum/) | 🟢 | `Hash Table` | [📝](problems/0001-two-sum/README.md) | [⚡](solutions/0001-two-sum.cpp) |
| 49 | [Group Anagrams](https://leetcode.com/problems/group-anagrams/) | 🟡 | `Hash Table` `String` | [📝](problems/0049-group-anagrams/README.md) | [⚡](solutions/0049-group-anagrams.cpp) |
| 128 | [Longest Consecutive Sequence](https://leetcode.com/problems/longest-consecutive-sequence/) | 🟡 | `Hash Table` `Union Find` | [📝](problems/0128-longest-consecutive-sequence/README.md) | [⚡](solutions/0128-longest-consecutive-sequence.cpp) |

### 🎯 Two Pointers

| # | Problem | Difficulty | Tags | Write-up | Code |
|:-:|:--------|:----------:|:-----|:--:|:--:|
| 283 | [Move Zeroes](https://leetcode.com/problems/move-zeroes/) | 🟢 | `Two Pointers` | [📝](problems/0283-move-zeroes/README.md) | [⚡](solutions/0283-move-zeroes.cpp) |
| 11 | [Container With Most Water](https://leetcode.com/problems/container-with-most-water/) | 🟡 | `Two Pointers` `Greedy` | [📝](problems/0011-container-with-most-water/README.md) | [⚡](solutions/0011-container-with-most-water.cpp) |
| 15 | [3Sum](https://leetcode.com/problems/3sum/) | 🟡 | `Two Pointers` `Sorting` | [📝](problems/0015-3sum/README.md) | [⚡](solutions/0015-3sum.cpp) |
| 42 | [Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/) | 🔴 | `Two Pointers` `DP` | [📝](problems/0042-trapping-rain-water/README.md) | [⚡](solutions/0042-trapping-rain-water.cpp) |

### 🪟 Sliding Window

| # | Problem | Difficulty | Tags | Write-up | Code |
|:-:|:--------|:----------:|:-----|:--:|:--:|
| 3 | [Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/) | 🟡 | `Sliding Window` `Hash Table` | [📝](problems/0003-longest-substring-without-repeating-characters/README.md) | [⚡](solutions/0003-longest-substring-without-repeating-characters.cpp) |
| 438 | [Find All Anagrams in a String](https://leetcode.com/problems/find-all-anagrams-in-a-string/) | 🟡 | `Sliding Window` `Hash Table` | [📝](problems/0438-find-all-anagrams-in-a-string/README.md) | [⚡](solutions/0438-find-all-anagrams-in-a-string.cpp) |

### 🧵 Substring

| # | Problem | Difficulty | Tags | Write-up | Code |
|:-:|:--------|:----------:|:-----|:--:|:--:|
| 560 | [Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/) | 🟡 | `Prefix Sum` `Hash Table` | [📝](problems/0560-subarray-sum-equals-k/README.md) | [⚡](solutions/0560-subarray-sum-equals-k.cpp) |
| 239 | [Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/) | 🔴 | `Monotonic Queue` | [📝](problems/0239-sliding-window-maximum/README.md) | [⚡](solutions/0239-sliding-window-maximum.cpp) |
| 76 | [Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/) | 🔴 | `Sliding Window` `Hash Table` | [📝](problems/0076-minimum-window-substring/README.md) | [⚡](solutions/0076-minimum-window-substring.cpp) |

### 📦 Array

| # | Problem | Difficulty | Tags | Write-up | Code |
|:-:|:--------|:----------:|:-----|:--:|:--:|
| 53 | [Maximum Subarray](https://leetcode.com/problems/maximum-subarray/) | 🟡 | `DP` `Divide & Conquer` | [📝](problems/0053-maximum-subarray/README.md) | [⚡](solutions/0053-maximum-subarray.cpp) |
| 56 | [Merge Intervals](https://leetcode.com/problems/merge-intervals/) | 🟡 | `Sorting` `Array` | [📝](problems/0056-merge-intervals/README.md) | [⚡](solutions/0056-merge-intervals.cpp) |
| 189 | [Rotate Array](https://leetcode.com/problems/rotate-array/) | 🟡 | `Array` `Math` | [📝](problems/0189-rotate-array/README.md) | [⚡](solutions/0189-rotate-array.cpp) |
| 238 | [Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/) | 🟡 | `Prefix Sum` | [📝](problems/0238-product-of-array-except-self/README.md) | [⚡](solutions/0238-product-of-array-except-self.cpp) |
| 41 | [First Missing Positive](https://leetcode.com/problems/first-missing-positive/) | 🔴 | `Hash Table` `In-place Swap` | [📝](problems/0041-first-missing-positive/README.md) | [⚡](solutions/0041-first-missing-positive.cpp) |

### 🧮 Matrix

| # | Problem | Difficulty | Tags | Write-up | Code |
|:-:|:--------|:----------:|:-----|:--:|:--:|
| 73 | [Set Matrix Zeroes](https://leetcode.com/problems/set-matrix-zeroes/) | 🟡 | `Matrix` `Hash Table` | [📝](problems/0073-set-matrix-zeroes/README.md) | [⚡](solutions/0073-set-matrix-zeroes.cpp) |
| 54 | [Spiral Matrix](https://leetcode.com/problems/spiral-matrix/) | 🟡 | `Matrix` `Simulation` | [📝](problems/0054-spiral-matrix/README.md) | [⚡](solutions/0054-spiral-matrix.cpp) |
| 48 | [Rotate Image](https://leetcode.com/problems/rotate-image/) | 🟡 | `Matrix` `Math` | [📝](problems/0048-rotate-image/README.md) | [⚡](solutions/0048-rotate-image.cpp) |
| 240 | [Search a 2D Matrix II](https://leetcode.com/problems/search-a-2d-matrix-ii/) | 🟡 | `Binary Search` `Divide & Conquer` | [📝](problems/0240-search-a-2d-matrix-ii/README.md) | [⚡](solutions/0240-search-a-2d-matrix-ii.cpp) |

### 🔗 Linked List

| # | Problem | Difficulty | Tags | Write-up | Code |
|:-:|:--------|:----------:|:-----|:--:|:--:|
| 160 | [Intersection of Two Linked Lists](https://leetcode.com/problems/intersection-of-two-linked-lists/) | 🟢 | `Linked List` `Two Pointers` | [📝](problems/0160-intersection-of-two-linked-lists/README.md) | [⚡](solutions/0160-intersection-of-two-linked-lists.cpp) |
| 206 | [Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/) | 🟢 | `Linked List` `Recursion` | [📝](problems/0206-reverse-linked-list/README.md) | [⚡](solutions/0206-reverse-linked-list.cpp) |
| 234 | [Palindrome Linked List](https://leetcode.com/problems/palindrome-linked-list/) | 🟢 | `Linked List` `Two Pointers` | [📝](problems/0234-palindrome-linked-list/README.md) | [⚡](solutions/0234-palindrome-linked-list.cpp) |
| 141 | [Linked List Cycle](https://leetcode.com/problems/linked-list-cycle/) | 🟢 | `Linked List` `Two Pointers` | [📝](problems/0141-linked-list-cycle/README.md) | [⚡](solutions/0141-linked-list-cycle.cpp) |
| 142 | [Linked List Cycle II](https://leetcode.com/problems/linked-list-cycle-ii/) | 🟡 | `Linked List` `Two Pointers` | [📝](problems/0142-linked-list-cycle-ii/README.md) | [⚡](solutions/0142-linked-list-cycle-ii.cpp) |
| 21 | [Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/) | 🟢 | `Linked List` `Recursion` | [📝](problems/0021-merge-two-sorted-lists/README.md) | [⚡](solutions/0021-merge-two-sorted-lists.cpp) |
| 2 | [Add Two Numbers](https://leetcode.com/problems/add-two-numbers/) | 🟡 | `Linked List` `Math` | [📝](problems/0002-add-two-numbers/README.md) | [⚡](solutions/0002-add-two-numbers.cpp) |
| 19 | [Remove Nth Node From End of List](https://leetcode.com/problems/remove-nth-node-from-end-of-list/) | 🟡 | `Linked List` `Two Pointers` | [📝](problems/0019-remove-nth-node-from-end-of-list/README.md) | [⚡](solutions/0019-remove-nth-node-from-end-of-list.cpp) |
| 24 | [Swap Nodes in Pairs](https://leetcode.com/problems/swap-nodes-in-pairs/) | 🟡 | `Linked List` `Recursion` | [📝](problems/0024-swap-nodes-in-pairs/README.md) | [⚡](solutions/0024-swap-nodes-in-pairs.cpp) |
| 25 | [Reverse Nodes in k-Group](https://leetcode.com/problems/reverse-nodes-in-k-group/) | 🔴 | `Linked List` `Recursion` | [📝](problems/0025-reverse-nodes-in-k-group/README.md) | [⚡](solutions/0025-reverse-nodes-in-k-group.cpp) |
| 138 | [Copy List with Random Pointer](https://leetcode.com/problems/copy-list-with-random-pointer/) | 🟡 | `Linked List` `Hash Table` | [📝](problems/0138-copy-list-with-random-pointer/README.md) | [⚡](solutions/0138-copy-list-with-random-pointer.cpp) |
| 148 | [Sort List](https://leetcode.com/problems/sort-list/) | 🟡 | `Linked List` `Merge Sort` | [📝](problems/0148-sort-list/README.md) | [⚡](solutions/0148-sort-list.cpp) |
| 23 | [Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/) | 🔴 | `Linked List` `Heap` `Divide & Conquer` | [📝](problems/0023-merge-k-sorted-lists/README.md) | [⚡](solutions/0023-merge-k-sorted-lists.cpp) |
| 146 | [LRU Cache](https://leetcode.com/problems/lru-cache/) | 🟡 | `Design` `Hash Table` `Doubly Linked List` | [📝](problems/0146-lru-cache/README.md) | [⚡](solutions/0146-lru-cache.cpp) |

### 🌳 Binary Tree

| # | Problem | Difficulty | Tags | Write-up | Code |
|:-:|:--------|:----------:|:-----|:--:|:--:|
| 94 | [Binary Tree Inorder Traversal](https://leetcode.com/problems/binary-tree-inorder-traversal/) | 🟢 | `Tree` `Stack` | [📝](problems/0094-binary-tree-inorder-traversal/README.md) | [⚡](solutions/0094-binary-tree-inorder-traversal.cpp) |
| 104 | [Maximum Depth of Binary Tree](https://leetcode.com/problems/maximum-depth-of-binary-tree/) | 🟢 | `Tree` `DFS` | [📝](problems/0104-maximum-depth-of-binary-tree/README.md) | [⚡](solutions/0104-maximum-depth-of-binary-tree.cpp) |
| 226 | [Invert Binary Tree](https://leetcode.com/problems/invert-binary-tree/) | 🟢 | `Tree` `DFS` | [📝](problems/0226-invert-binary-tree/README.md) | [⚡](solutions/0226-invert-binary-tree.cpp) |
| 101 | [Symmetric Tree](https://leetcode.com/problems/symmetric-tree/) | 🟢 | `Tree` `DFS` `BFS` | [📝](problems/0101-symmetric-tree/README.md) | [⚡](solutions/0101-symmetric-tree.cpp) |
| 543 | [Diameter of Binary Tree](https://leetcode.com/problems/diameter-of-binary-tree/) | 🟢 | `Tree` `DFS` | [📝](problems/0543-diameter-of-binary-tree/README.md) | [⚡](solutions/0543-diameter-of-binary-tree.cpp) |
| 102 | [Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/) | 🟡 | `Tree` `BFS` | [📝](problems/0102-binary-tree-level-order-traversal/README.md) | [⚡](solutions/0102-binary-tree-level-order-traversal.cpp) |
| 108 | [Convert Sorted Array to Binary Search Tree](https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/) | 🟢 | `Tree` `Binary Search` | [📝](problems/0108-convert-sorted-array-to-binary-search-tree/README.md) | [⚡](solutions/0108-convert-sorted-array-to-binary-search-tree.cpp) |
| 98 | [Validate Binary Search Tree](https://leetcode.com/problems/validate-binary-search-tree/) | 🟡 | `Tree` `DFS` | [📝](problems/0098-validate-binary-search-tree/README.md) | [⚡](solutions/0098-validate-binary-search-tree.cpp) |
| 230 | [Kth Smallest Element in a BST](https://leetcode.com/problems/kth-smallest-element-in-a-bst/) | 🟡 | `Tree` `Inorder` | [📝](problems/0230-kth-smallest-element-in-a-bst/README.md) | [⚡](solutions/0230-kth-smallest-element-in-a-bst.cpp) |
| 199 | [Binary Tree Right Side View](https://leetcode.com/problems/binary-tree-right-side-view/) | 🟡 | `Tree` `DFS` `BFS` | [📝](problems/0199-binary-tree-right-side-view/README.md) | [⚡](solutions/0199-binary-tree-right-side-view.cpp) |
| 114 | [Flatten Binary Tree to Linked List](https://leetcode.com/problems/flatten-binary-tree-to-linked-list/) | 🟡 | `Tree` `DFS` | [📝](problems/0114-flatten-binary-tree-to-linked-list/README.md) | [⚡](solutions/0114-flatten-binary-tree-to-linked-list.cpp) |
| 105 | [Construct Binary Tree from Preorder and Inorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/) | 🟡 | `Tree` `Divide & Conquer` | [📝](problems/0105-construct-binary-tree-from-preorder-and-inorder-traversal/README.md) | [⚡](solutions/0105-construct-binary-tree-from-preorder-and-inorder-traversal.cpp) |
| 437 | [Path Sum III](https://leetcode.com/problems/path-sum-iii/) | 🟡 | `Tree` `Prefix Sum` | [📝](problems/0437-path-sum-iii/README.md) | [⚡](solutions/0437-path-sum-iii.cpp) |
| 236 | [Lowest Common Ancestor of a Binary Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/) | 🟡 | `Tree` `DFS` | [📝](problems/0236-lowest-common-ancestor-of-a-binary-tree/README.md) | [⚡](solutions/0236-lowest-common-ancestor-of-a-binary-tree.cpp) |
| 124 | [Binary Tree Maximum Path Sum](https://leetcode.com/problems/binary-tree-maximum-path-sum/) | 🔴 | `Tree` `DFS` | [📝](problems/0124-binary-tree-maximum-path-sum/README.md) | [⚡](solutions/0124-binary-tree-maximum-path-sum.cpp) |

### 🕸️ Graph

| # | Problem | Difficulty | Tags | Write-up | Code |
|:-:|:--------|:----------:|:-----|:--:|:--:|
| 200 | [Number of Islands](https://leetcode.com/problems/number-of-islands/) | 🟡 | `Graph` `DFS` `Union Find` | [📝](problems/0200-number-of-islands/README.md) | [⚡](solutions/0200-number-of-islands.cpp) |
| 994 | [Rotting Oranges](https://leetcode.com/problems/rotting-oranges/) | 🟡 | `Graph` `BFS` | [📝](problems/0994-rotting-oranges/README.md) | [⚡](solutions/0994-rotting-oranges.cpp) |
| 207 | [Course Schedule](https://leetcode.com/problems/course-schedule/) | 🟡 | `Graph` `Topological Sort` | [📝](problems/0207-course-schedule/README.md) | [⚡](solutions/0207-course-schedule.cpp) |
| 208 | [Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree/) | 🟡 | `Design` `Tree` | [📝](problems/0208-implement-trie-prefix-tree/README.md) | [⚡](solutions/0208-implement-trie-prefix-tree.cpp) |

### 🔙 Backtracking

| # | Problem | Difficulty | Tags | Write-up | Code |
|:-:|:--------|:----------:|:-----|:--:|:--:|
| 46 | [Permutations](https://leetcode.com/problems/permutations/) | 🟡 | `Backtracking` | [📝](problems/0046-permutations/README.md) | [⚡](solutions/0046-permutations.cpp) |
| 78 | [Subsets](https://leetcode.com/problems/subsets/) | 🟡 | `Backtracking` `Bit Manipulation` | [📝](problems/0078-subsets/README.md) | [⚡](solutions/0078-subsets.cpp) |
| 17 | [Letter Combinations of a Phone Number](https://leetcode.com/problems/letter-combinations-of-a-phone-number/) | 🟡 | `Backtracking` `Hash Table` | [📝](problems/0017-letter-combinations-of-a-phone-number/README.md) | [⚡](solutions/0017-letter-combinations-of-a-phone-number.cpp) |
| 39 | [Combination Sum](https://leetcode.com/problems/combination-sum/) | 🟡 | `Backtracking` | [📝](problems/0039-combination-sum/README.md) | [⚡](solutions/0039-combination-sum.cpp) |
| 22 | [Generate Parentheses](https://leetcode.com/problems/generate-parentheses/) | 🟡 | `Backtracking` | [📝](problems/0022-generate-parentheses/README.md) | [⚡](solutions/0022-generate-parentheses.cpp) |
| 79 | [Word Search](https://leetcode.com/problems/word-search/) | 🟡 | `Backtracking` | [📝](problems/0079-word-search/README.md) | [⚡](solutions/0079-word-search.cpp) |
| 131 | [Palindrome Partitioning](https://leetcode.com/problems/palindrome-partitioning/) | 🟡 | `Backtracking` `DP` | [📝](problems/0131-palindrome-partitioning/README.md) | [⚡](solutions/0131-palindrome-partitioning.cpp) |
| 51 | [N-Queens](https://leetcode.com/problems/n-queens/) | 🔴 | `Backtracking` | [📝](problems/0051-n-queens/README.md) | [⚡](solutions/0051-n-queens.cpp) |

### 🔍 Binary Search

| # | Problem | Difficulty | Tags | Write-up | Code |
|:-:|:--------|:----------:|:-----|:--:|:--:|
| 35 | [Search Insert Position](https://leetcode.com/problems/search-insert-position/) | 🟢 | `Binary Search` | [📝](problems/0035-search-insert-position/README.md) | [⚡](solutions/0035-search-insert-position.cpp) |
| 74 | [Search a 2D Matrix](https://leetcode.com/problems/search-a-2d-matrix/) | 🟡 | `Binary Search` | [📝](problems/0074-search-a-2d-matrix/README.md) | [⚡](solutions/0074-search-a-2d-matrix.cpp) |
| 34 | [Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/) | 🟡 | `Binary Search` | [📝](problems/0034-find-first-and-last-position-of-element-in-sorted-array/README.md) | [⚡](solutions/0034-find-first-and-last-position-of-element-in-sorted-array.cpp) |
| 33 | [Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/) | 🟡 | `Binary Search` | [📝](problems/0033-search-in-rotated-sorted-array/README.md) | [⚡](solutions/0033-search-in-rotated-sorted-array.cpp) |
| 153 | [Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/) | 🟡 | `Binary Search` | [📝](problems/0153-find-minimum-in-rotated-sorted-array/README.md) | [⚡](solutions/0153-find-minimum-in-rotated-sorted-array.cpp) |
| 4 | [Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/) | 🔴 | `Binary Search` | [📝](problems/0004-median-of-two-sorted-arrays/README.md) | [⚡](solutions/0004-median-of-two-sorted-arrays.cpp) |

### 🥞 Stack

| # | Problem | Difficulty | Tags | Write-up | Code |
|:-:|:--------|:----------:|:-----|:--:|:--:|
| 20 | [Valid Parentheses](https://leetcode.com/problems/valid-parentheses/) | 🟢 | `Stack` | [📝](problems/0020-valid-parentheses/README.md) | [⚡](solutions/0020-valid-parentheses.cpp) |
| 155 | [Min Stack](https://leetcode.com/problems/min-stack/) | 🟢 | `Stack` `Design` | [📝](problems/0155-min-stack/README.md) | [⚡](solutions/0155-min-stack.cpp) |
| 394 | [Decode String](https://leetcode.com/problems/decode-string/) | 🟡 | `Stack` | [📝](problems/0394-decode-string/README.md) | [⚡](solutions/0394-decode-string.cpp) |
| 739 | [Daily Temperatures](https://leetcode.com/problems/daily-temperatures/) | 🟡 | `Monotonic Stack` | [📝](problems/0739-daily-temperatures/README.md) | [⚡](solutions/0739-daily-temperatures.cpp) |
| 84 | [Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/) | 🔴 | `Monotonic Stack` | [📝](problems/0084-largest-rectangle-in-histogram/README.md) | [⚡](solutions/0084-largest-rectangle-in-histogram.cpp) |

### ⛰️ Heap

| # | Problem | Difficulty | Tags | Write-up | Code |
|:-:|:--------|:----------:|:-----|:--:|:--:|
| 215 | [Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/) | 🟡 | `Heap` `Quick Select` | [📝](problems/0215-kth-largest-element-in-an-array/README.md) | [⚡](solutions/0215-kth-largest-element-in-an-array.cpp) |
| 347 | [Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/) | 🟡 | `Heap` `Hash Table` | [📝](problems/0347-top-k-frequent-elements/README.md) | [⚡](solutions/0347-top-k-frequent-elements.cpp) |
| 295 | [Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/) | 🔴 | `Heap` `Design` | [📝](problems/0295-find-median-from-data-stream/README.md) | [⚡](solutions/0295-find-median-from-data-stream.cpp) |

### 💰 Greedy

| # | Problem | Difficulty | Tags | Write-up | Code |
|:-:|:--------|:----------:|:-----|:--:|:--:|
| 121 | [Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/) | 🟢 | `Greedy` `DP` | [📝](problems/0121-best-time-to-buy-and-sell-stock/README.md) | [⚡](solutions/0121-best-time-to-buy-and-sell-stock.cpp) |
| 55 | [Jump Game](https://leetcode.com/problems/jump-game/) | 🟡 | `Greedy` | [📝](problems/0055-jump-game/README.md) | [⚡](solutions/0055-jump-game.cpp) |
| 45 | [Jump Game II](https://leetcode.com/problems/jump-game-ii/) | 🟡 | `Greedy` | [📝](problems/0045-jump-game-ii/README.md) | [⚡](solutions/0045-jump-game-ii.cpp) |
| 763 | [Partition Labels](https://leetcode.com/problems/partition-labels/) | 🟡 | `Greedy` `Hash Table` | [📝](problems/0763-partition-labels/README.md) | [⚡](solutions/0763-partition-labels.cpp) |

### 🏃 Dynamic Programming

| # | Problem | Difficulty | Tags | Write-up | Code |
|:-:|:--------|:----------:|:-----|:--:|:--:|
| 70 | [Climbing Stairs](https://leetcode.com/problems/climbing-stairs/) | 🟢 | `DP` | [📝](problems/0070-climbing-stairs/README.md) | [⚡](solutions/0070-climbing-stairs.cpp) |
| 118 | [Pascal's Triangle](https://leetcode.com/problems/pascals-triangle/) | 🟢 | `DP` `Array` | [📝](problems/0118-pascals-triangle/README.md) | [⚡](solutions/0118-pascals-triangle.cpp) |
| 198 | [House Robber](https://leetcode.com/problems/house-robber/) | 🟡 | `DP` | [📝](problems/0198-house-robber/README.md) | [⚡](solutions/0198-house-robber.cpp) |
| 279 | [Perfect Squares](https://leetcode.com/problems/perfect-squares/) | 🟡 | `DP` `BFS` | [📝](problems/0279-perfect-squares/README.md) | [⚡](solutions/0279-perfect-squares.cpp) |
| 322 | [Coin Change](https://leetcode.com/problems/coin-change/) | 🟡 | `DP` `BFS` | [📝](problems/0322-coin-change/README.md) | [⚡](solutions/0322-coin-change.cpp) |
| 139 | [Word Break](https://leetcode.com/problems/word-break/) | 🟡 | `DP` `Hash Table` | [📝](problems/0139-word-break/README.md) | [⚡](solutions/0139-word-break.cpp) |
| 300 | [Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/) | 🟡 | `DP` `Binary Search` | [📝](problems/0300-longest-increasing-subsequence/README.md) | [⚡](solutions/0300-longest-increasing-subsequence.cpp) |
| 152 | [Maximum Product Subarray](https://leetcode.com/problems/maximum-product-subarray/) | 🟡 | `DP` | [📝](problems/0152-maximum-product-subarray/README.md) | [⚡](solutions/0152-maximum-product-subarray.cpp) |
| 416 | [Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/) | 🟡 | `DP` `Knapsack` | [📝](problems/0416-partition-equal-subset-sum/README.md) | [⚡](solutions/0416-partition-equal-subset-sum.cpp) |
| 32 | [Longest Valid Parentheses](https://leetcode.com/problems/longest-valid-parentheses/) | 🔴 | `DP` `Stack` | [📝](problems/0032-longest-valid-parentheses/README.md) | [⚡](solutions/0032-longest-valid-parentheses.cpp) |

### 🧩 Multidimensional DP

| # | Problem | Difficulty | Tags | Write-up | Code |
|:-:|:--------|:----------:|:-----|:--:|:--:|
| 62 | [Unique Paths](https://leetcode.com/problems/unique-paths/) | 🟡 | `DP` `Math` | [📝](problems/0062-unique-paths/README.md) | [⚡](solutions/0062-unique-paths.cpp) |
| 64 | [Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/) | 🟡 | `DP` `Matrix` | [📝](problems/0064-minimum-path-sum/README.md) | [⚡](solutions/0064-minimum-path-sum.cpp) |
| 5 | [Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/) | 🟡 | `DP` `Expand Around Center` | [📝](problems/0005-longest-palindromic-substring/README.md) | [⚡](solutions/0005-longest-palindromic-substring.cpp) |
| 1143 | [Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/) | 🟡 | `DP` `String` | [📝](problems/1143-longest-common-subsequence/README.md) | [⚡](solutions/1143-longest-common-subsequence.cpp) |
| 72 | [Edit Distance](https://leetcode.com/problems/edit-distance/) | 🔴 | `DP` `String` | [📝](problems/0072-edit-distance/README.md) | [⚡](solutions/0072-edit-distance.cpp) |

### ✨ Techniques

| # | Problem | Difficulty | Tags | Write-up | Code |
|:-:|:--------|:----------:|:-----|:--:|:--:|
| 136 | [Single Number](https://leetcode.com/problems/single-number/) | 🟢 | `Bit Manipulation` | [📝](problems/0136-single-number/README.md) | [⚡](solutions/0136-single-number.cpp) |
| 169 | [Majority Element](https://leetcode.com/problems/majority-element/) | 🟢 | `Hash Table` `Boyer-Moore` | [📝](problems/0169-majority-element/README.md) | [⚡](solutions/0169-majority-element.cpp) |
| 75 | [Sort Colors](https://leetcode.com/problems/sort-colors/) | 🟡 | `Two Pointers` | [📝](problems/0075-sort-colors/README.md) | [⚡](solutions/0075-sort-colors.cpp) |
| 31 | [Next Permutation](https://leetcode.com/problems/next-permutation/) | 🟡 | `Array` `Two Pointers` | [📝](problems/0031-next-permutation/README.md) | [⚡](solutions/0031-next-permutation.cpp) |
| 287 | [Find the Duplicate Number](https://leetcode.com/problems/find-the-duplicate-number/) | 🟡 | `Binary Search` `Two Pointers` | [📝](problems/0287-find-the-duplicate-number/README.md) | [⚡](solutions/0287-find-the-duplicate-number.cpp) |

## ⚙️ Usage

Solution sources are in **LeetCode submission format** (`Solution` class only) and can be pasted directly into the LeetCode editor:

```bash
# Local syntax check (no extra dependencies needed)
g++ -std=c++17 -fsyntax-only solutions/0001-two-sum.cpp
```

📖 **Reading tip**: start with the multi-solution comparison in `problems/{number-slug}/README.md` (easy → optimal, with complexity and pitfalls, in Chinese), then study the recommended solution in `solutions/`.

## 📌 Conventions

- **File naming**: `solutions/{4-digit number}-{problem-slug}.cpp`; write-ups live at `problems/{4-digit number}-{problem-slug}/README.md`
- **Source header comment**: includes problem link, solution name, approach summary, and time/space complexity
- **Write-up**: problem description + examples & constraints + 2~3 solutions (easy → optimal, best one marked "recommended") + pitfalls
- **Commit message**: `solve: {number} {problem name}`, e.g. `solve: 0001 Two Sum`
- **Keep in sync**: after solving a problem, update the corresponding category in the 📊 Progress section

---

<p align="center">
  🌐 Language / 语言：
  <a href="README.md">🇨🇳 简体中文</a> ｜
  <a href="README.en.md">🇺🇸 <b>English</b></a>
</p>
