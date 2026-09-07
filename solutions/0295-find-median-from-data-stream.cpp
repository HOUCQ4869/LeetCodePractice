/**
 * @file    0295-find-median-from-data-stream.cpp
 * @brief   295. 数据流的中位数
 * @link    https://leetcode.cn/problems/find-median-from-data-stream/
 *
 * 解法：双堆（大顶堆 + 小顶堆）
 * 思路：较小一半进大顶堆 low、较大一半进小顶堆 high，插入后两次倒腾维持有序分割与大小平衡，中位数由两堆顶 O(1) 得出。
 * 时间复杂度：addNum O(log n)，findMedian O(1)
 * 空间复杂度：O(n)
 */

#include <queue>

class MedianFinder {
public:
    MedianFinder() {}

    void addNum(int num) {
        // 先入大顶堆，再把它当前的最大值移入小顶堆，保证 low 中元素 <= high 中元素
        low.push(num);
        high.push(low.top());
        low.pop();
        // 平衡大小：low 与 high 相等，或 low 恰好多一个
        if (high.size() > low.size()) {
            low.push(high.top());
            high.pop();
        }
    }

    double findMedian() {
        if (low.size() > high.size()) return low.top();
        return (low.top() + high.top()) / 2.0;
    }

private:
    priority_queue<int> low;                              // 大顶堆：较小的一半
    priority_queue<int, vector<int>, greater<int>> high;  // 小顶堆：较大的一半
};
