/**
 * @file    0207-course-schedule.cpp
 * @brief   207. 课程表
 * @link    https://leetcode.cn/problems/course-schedule/
 *
 * 解法：拓扑排序（Kahn 算法 / BFS 入度表）
 * 思路：把「先修 p[1] 才能修 p[0]」建成边 p[1] -> p[0] 并统计入度；
 *      入度为 0 的课无先修要求，可立即修，入队；每修完一门就把其后修课入度减一，
 *      减到 0 入队。能出队全部课程 <=> 依赖图无环 <=> 可以修完。
 * 时间复杂度：O(V + E)，V 为课程数、E 为先修关系数
 * 空间复杂度：O(V + E)，邻接表、入度表与队列
 */

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
