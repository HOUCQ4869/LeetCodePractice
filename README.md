# LeetCodePractice

[简体中文](README.md) | [English](README.en.md)

LeetCode 刷题记录仓库，使用 C++ 解题。每道题附带独立题解文件，记录思路、复杂度分析与易错点，方便系统性复盘。

## 目录结构

```
LeetCodePractice/
├── README.md            # 中文说明
├── README.en.md         # 英文说明
├── solutions/           # 题解源码，按题号 + 题名slug 命名
│   ├── 0001-two-sum.cpp
│   └── ...
└── notes/               # 算法专题笔记（按标签整理）
    ├── two-pointers.md
    └── ...
```

## 刷题进度

| #  | 题目 | 难度 | 标签 | 题解 | 日期 |
|----|------|------|------|------|------|
| 1 | [Two Sum](https://leetcode.cn/problems/two-sum/) | 🟢 简单 | 哈希表 | [C++](solutions/0001-two-sum.cpp) | 2026-09-03 |

<!-- 示例行，请替换为实际记录。新增题目时在此追加一行 -->

**进度统计**：简单 0 / 中等 0 / 困难 0

## 分类索引

- [ ] 数组与哈希
- [ ] 双指针
- [ ] 滑动窗口
- [ ] 链表
- [ ] 栈与队列
- [ ] 二叉树
- [ ] 图论
- [ ] 二分查找
- [ ] 动态规划
- [ ] 贪心
- [ ] 回溯

## 使用方法

单文件编译运行（C++17 标准）：

```bash
g++ -std=c++17 -O2 -Wall solutions/0001-two-sum.cpp -o main && ./main
```

## 记录规范

- **文件命名**：`solutions/{题号四位}-{题名slug}.cpp`，如 `0206-reverse-linked-list.cpp`
- **源码头部注释**：包含题目链接、思路简述、时间/空间复杂度
- **提交信息**：`solve: {题号} {题名}`，如 `solve: 0001 两数之和`
- **同步更新**：每解一题，更新「刷题进度」表和「分类索引」勾选项
