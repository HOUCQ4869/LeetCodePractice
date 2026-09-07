# 74. 搜索二维矩阵

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/search-a-2d-matrix/) ｜ [国际站](https://leetcode.com/problems/search-a-2d-matrix/)
>
> 🟡 中等 ｜ 标签：`二分查找` `矩阵`

## 📝 题目描述

给定一个 `m × n` 的整数矩阵，满足两条性质：每行元素从左到右升序排列；每行的第一个整数大于前一行的最后一个整数。再给定一个目标值 `target`，判断它是否存在于矩阵中。

由于上述性质，把矩阵每行依次拼接起来就是一个严格递增的一维数组，这正是本题能套用一维二分的关键。

**示例 1：**

```text
输入：matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
输出：true
```

**示例 2：**

```text
输入：matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
输出：false
```

**提示：**

- `m == matrix.length`，`n == matrix[i].length`
- `1 <= m, n <= 100`
- `-10^4 <= matrix[i][j], target <= 10^4`

## 💡 题解

### 解法一：两次二分（先定位行，再行内查找）

**思路**：利用"每行首元素递增"的性质，先二分找到最后一个首元素不超过 `target` 的行——`target` 若存在只能在这一行；再对该行做普通二分查找。两次二分互不干扰，写法均为标准模板。注意定位行时用上取整的 `mid`（偏右），避免区间只剩两个元素时死循环。

```cpp
#include <vector>

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        // 第一次二分：找最后一个首元素 <= target 的行
        int up = 0, down = m - 1;
        while (up < down) {
            int mid = up + (down - up + 1) / 2;  // 偏右，避免死循环
            if (matrix[mid][0] <= target) {
                up = mid;
            } else {
                down = mid - 1;
            }
        }
        // 第二次二分：在该行内查找 target
        int row = up;
        int left = 0, right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (matrix[row][mid] == target) return true;
            if (matrix[row][mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return false;
    }
};
```

- ⏱️ 时间复杂度：`O(log m + log n)`
- 💾 空间复杂度：`O(1)`

### 解法二：展平为一维，一次二分（推荐）

**思路**：矩阵逐行拼接后是有序数组，因此可以对虚拟的一维下标区间 `[0, m·n)` 直接二分：设列数为 `n`，一维下标 `mid` 对应二维位置 `(mid / n, mid % n)`。整个过程中矩阵并未真正展开，只是下标做了映射，一次二分即可得到答案。

```cpp
#include <vector>

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        int left = 0, right = m * n - 1;  // 闭区间 [left, right]
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int val = matrix[mid / n][mid % n];  // 一维下标映射回二维
            if (val == target) return true;
            if (val < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return false;
    }
};
```

- ⏱️ 时间复杂度：`O(log(mn))`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 一维下标映射容易写反：除的是列数 `n`（每行有 `n` 个元素），即 `matrix[mid / n][mid % n]`，写成 `mid / m` 是常见笔误。
- 本题与 240 题（每行、每列各自升序，但行首不一定大于上一行末）性质不同：本题可以当作一维二分，"Z 字形查找"反而多余；反过来 240 题不能用本题的一维二分。
- 两次二分定位行时，找"最后一个首元素 `<= target` 的行"必须让 `mid` 上取整，否则当区间只剩相邻两行时会死循环。

---

[← 返回目录](../../README.md)
