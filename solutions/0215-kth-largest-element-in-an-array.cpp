/**
 * @file    0215-kth-largest-element-in-an-array.cpp
 * @brief   215. 数组中的第K个最大元素
 * @link    https://leetcode.cn/problems/kth-largest-element-in-an-array/
 *
 * 解法：快速选择（随机基准）
 * 思路：按从大到小 partition，基准落在最终下标 p；与 k-1 比较后只需递归包含答案的一侧，期望线性时间。
 * 时间复杂度：O(n)（期望）
 * 空间复杂度：O(1)
 */

#include <vector>
#include <random>

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // [l, r] 内查找第 k 大，目标最终下标为 k - 1（从大到小排）
        int l = 0, r = (int)nums.size() - 1, target = k - 1;
        mt19937 rng(random_device{}());
        while (true) {
            int p = partition(nums, l, r, rng);
            if (p == target) return nums[p];
            if (p < target) {
                l = p + 1;   // 答案在右侧
            } else {
                r = p - 1;   // 答案在左侧
            }
        }
    }

private:
    // 随机选基准并划分，返回基准最终下标；大于基准的在左，小于基准的在右
    int partition(vector<int>& nums, int l, int r, mt19937& rng) {
        swap(nums[l], nums[l + (int)(rng() % (r - l + 1))]);
        int pivot = nums[l];
        int i = l + 1, j = r;
        while (i <= j) {
            while (i <= j && nums[i] > pivot) ++i;
            while (i <= j && nums[j] < pivot) --j;
            if (i <= j) {
                swap(nums[i], nums[j]);
                ++i;
                --j;
            }
        }
        swap(nums[l], nums[j]);
        return j;
    }
};
