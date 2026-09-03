# LeetCodePractice

[简体中文](README.md) | [English](README.en.md)

A repository for tracking LeetCode practice, with all solutions written in C++. Each problem has its own solution file documenting the approach, complexity analysis, and common pitfalls, making it easy to review systematically.

## Directory Structure

```
LeetCodePractice/
├── README.md            # Chinese docs
├── README.en.md         # English docs
├── solutions/           # Solution source files, named by problem number + slug
│   ├── 0001-two-sum.cpp
│   └── ...
└── notes/               # Topic notes (organized by tag)
    ├── two-pointers.md
    └── ...
```

## Progress

| # | Problem | Difficulty | Tags | Solution | Date |
|---|---------|------------|------|----------|------|
| 1 | [Two Sum](https://leetcode.com/problems/two-sum/) | 🟢 Easy | Hash Table | [C++](solutions/0001-two-sum.cpp) | 2026-09-03 |

<!-- Example row, replace with your own records. Append one row per new problem -->

**Statistics**: Easy 0 / Medium 0 / Hard 0

## Topic Index

- [ ] Array & Hashing
- [ ] Two Pointers
- [ ] Sliding Window
- [ ] Linked List
- [ ] Stack & Queue
- [ ] Binary Tree
- [ ] Graph
- [ ] Binary Search
- [ ] Dynamic Programming
- [ ] Greedy
- [ ] Backtracking

## Usage

Compile and run a single solution (C++17):

```bash
g++ -std=c++17 -O2 -Wall solutions/0001-two-sum.cpp -o main && ./main
```

## Conventions

- **File naming**: `solutions/{4-digit number}-{problem-slug}.cpp`, e.g. `0206-reverse-linked-list.cpp`
- **Source header comment**: includes problem link, approach summary, and time/space complexity
- **Commit message**: `solve: {number} {problem name}`, e.g. `solve: 0001 Two Sum`
- **Keep in sync**: after solving a problem, update the Progress table and check it off in the Topic Index
