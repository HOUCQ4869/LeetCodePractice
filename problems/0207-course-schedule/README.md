# 207. 课程表

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/course-schedule/) ｜ [国际站](https://leetcode.com/problems/course-schedule/)
>
> 🟡 中等 ｜ 标签：`图` `拓扑排序`

## 📝 题目描述

本学期共需选修 `numCourses` 门课程，编号为 `0` 到 `numCourses - 1`。给定数组 `prerequisites`，其中 `prerequisites[i] = [ai, bi]` 表示**想修课程 `ai` 必须先修完课程 `bi`**。请判断是否可能修完全部课程（允许按任意顺序）。

本质：把课程看作节点、`bi -> ai` 看作有向边，问题等价于判断这个有向图**是否存在环**——无环（即存在拓扑序）才能修完。

**示例 1：**

```
输入：numCourses = 2, prerequisites = [[1,0]]
输出：true
解释：共 2 门课。修课程 1 之前必须先修课程 0，顺序 0 -> 1 即可。
```

**示例 2：**

```
输入：numCourses = 2, prerequisites = [[1,0],[0,1]]
输出：false
解释：课程 0 依赖课程 1，课程 1 又依赖课程 0，互相等待，无法修完。
```

**提示：**

- `1 <= numCourses <= 2000`
- `0 <= prerequisites.length <= 5000`
- `prerequisites[i].length == 2`
- `0 <= ai, bi < numCourses`
- 所有先修关系对 `[ai, bi]` **互不相同**

## 💡 题解

### 解法一：深度优先搜索（三色标记判环）

**思路**：对图做 DFS，用三种状态标记节点——`0` 未访问、`1` 访问中（在当前递归栈里）、`2` 已完成。若 DFS 过程中遇到一个状态为 `1` 的邻居，说明沿着边走了回**仍在递归中的祖先节点**，即出现环。注意必须区分"访问中"与"已完成"：指向已完成节点的边（如菱形依赖 `A→B→D`、`A→C→D` 中的 `C→D`）只是汇合，不是环。每个节点各做一次未访问起点的 DFS，全程没有发现环则可以修完。

```cpp
#include <vector>

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        for (const auto& p : prerequisites) {
            graph[p[1]].push_back(p[0]);  // 先修 p[1] -> 后修 p[0]
        }
        vector<int> color(numCourses, 0);  // 0 未访问 / 1 访问中 / 2 已完成
        for (int i = 0; i < numCourses; ++i) {
            if (color[i] == 0 && hasCycle(graph, i, color)) return false;
        }
        return true;
    }

private:
    bool hasCycle(const vector<vector<int>>& graph, int u, vector<int>& color) {
        color[u] = 1;  // 进入递归栈
        for (int v : graph[u]) {
            if (color[v] == 1) return true;  // 指向在途节点：回边，有环
            if (color[v] == 0 && hasCycle(graph, v, color)) return true;
        }
        color[u] = 2;  // 子树处理完毕
        return false;
    }
};
```

- ⏱️ 时间复杂度：`O(V + E)`，每个节点、每条边各访问一次
- 💾 空间复杂度：`O(V + E)`，邻接表、颜色数组与递归栈

### 解法二：拓扑排序——Kahn 算法 / BFS 入度表（推荐）

**思路**：维护每个节点的**入度**（先修课程数）。入度为 `0` 的课没有任何未完成的先修，可以立刻修——全部入队。每从队列中取出（"修完"）一门课，就把它指向的每门后修课的入度减一；某门课的入度减到 `0`，说明先修全部就绪，也入队。最终**出队的课程总数等于 `numCourses`** 当且仅当图无环：环上节点的入度永远无法归零，会被剩在队列之外。这个迭代写法没有递归深度顾虑，而且天然产出拓扑序——把出队序列记下来就是第 210 题「课程表 II」要的答案。

```cpp
#include <queue>
#include <vector>

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> indegree(numCourses, 0);
        for (const auto& p : prerequisites) {
            graph[p[1]].push_back(p[0]);  // 先修 p[1] -> 后修 p[0]
            ++indegree[p[0]];
        }

        queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (indegree[i] == 0) q.push(i);  // 无先修要求的课程直接可修
        }

        int taken = 0;  // 已确定可修的课程数
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            ++taken;
            for (int next : graph[course]) {
                if (--indegree[next] == 0) q.push(next);  // 先修全部完成，可以入队
            }
        }
        return taken == numCourses;  // 全部课程都能修 <=> 依赖图无环
    }
};
```

- ⏱️ 时间复杂度：`O(V + E)`
- 💾 空间复杂度：`O(V + E)`，邻接表、入度表与队列

## ⚠️ 易错点

- **建边方向**：`[a, b]` 的语义是"先修 b 才能修 a"，应建边 `b -> a`、入度加在 `a` 上；建反后整张图入度计算全部失效。
- DFS 判环只用一个 `visited` 布尔会把"指向已完成节点的普通边"误判成环，必须区分**访问中 / 已完成**两种状态。
- 判断条件是「出队数量 == 课程总数」，而不是「队列变为空」——有环时队列同样会空，只是有节点从未入队。
- 入度数组和邻接表的大小应开 `numCourses`（节点数），不是 `prerequisites.size()`（边数）。

---

[← 返回目录](../../README.md)
