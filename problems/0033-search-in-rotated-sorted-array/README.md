# 33. 搜索旋转排序数组

> 🔗 题目链接：[中文站](https://leetcode.cn/problems/search-in-rotated-sorted-array/) ｜ [国际站](https://leetcode.com/problems/search-in-rotated-sorted-array/)
>
> 🟡 中等 ｜ 标签：`二分查找`

## 📝 题目描述

一个原本升序且元素互不相同的整数数组 `nums`，在某个预先未知的下标处被旋转了一次（例如 `[0,1,2,4,5,6,7]` 旋转后可能变为 `[4,5,6,7,0,1,2]`）。给定旋转后的数组和整数 `target`，如果 `target` 存在于数组中则返回其下标，否则返回 `-1`。题目要求设计 `O(log n)` 的算法。

**示例 1：**

```text
输入：nums = [4,5,6,7,0,1,2], target = 0
输出：4
```

**示例 2：**

```text
输入：nums = [4,5,6,7,0,1,2], target = 3
输出：-1
```

**示例 3：**

```text
输入：nums = [1], target = 0
输出：-1
```

**提示：**

- `1 <= nums.length <= 5000`
- `-10^4 <= nums[i] <= 10^4`，原数组为元素互异的升序数组，旋转次数在 `[1, n]` 内
- `-10^4 <= target <= 10^4`

## 💡 题解

### 解法一：直接遍历

**思路**：从头到尾扫一遍找 `target`。旋转数组的有序性被打断后线性查找当然可行，但完全没有利用"旋转前有序"的性质，`O(n)` 不满足题目进阶要求，仅作对照。

```cpp
#include <vector>

class Solution {
public:
    int search(vector<int>& nums, int target) {
        for (int i = 0; i < (int)nums.size(); i++) {
            if (nums[i] == target) return i;
        }
        return -1;
    }
};
```

- ⏱️ 时间复杂度：`O(n)`
- 💾 空间复杂度：`O(1)`

### 解法二：先找旋转点，再二分

**思路**：旋转点（最小值位置）把数组分成两段各自有序的区间。先用一次二分（比较 `nums[mid]` 与 `nums[right]`，即 153 题的做法）找到旋转点；再根据 `target` 与 `nums[0]` 的大小关系判断它落在哪一段，最后对该有序段做一次普通二分。逻辑清晰，两次二分各自独立。

```cpp
#include <vector>

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        // 第一步：二分找旋转点（最小值下标）
        int lo = 0, hi = n - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] > nums[hi]) {
                lo = mid + 1;  // 最小值在 mid 右侧
            } else {
                hi = mid;      // mid 可能就是最小值
            }
        }
        int pivot = lo;
        // 第二步：判断 target 落在哪一段，再做普通二分
        if (pivot == 0) {
            lo = 0, hi = n - 1;                 // 未旋转，整段有序
        } else if (target >= nums[0]) {
            lo = 0, hi = pivot - 1;             // 在左段（较大段）
        } else {
            lo = pivot, hi = n - 1;             // 在右段（较小段）
        }
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] == target) return mid;
            if (nums[mid] < target) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return -1;
    }
};
```

- ⏱️ 时间复杂度：`O(log n)`
- 💾 空间复杂度：`O(1)`

### 解法三：一次二分（推荐）

**思路**：虽然整个数组不是全局有序，但每次取 `mid` 后，`[left, mid]` 与 `[mid, right]` 中**必有一半是有序的**：若 `nums[left] <= nums[mid]` 则左半有序，否则右半有序。判断出有序的一半后，用它的首尾元素即可判断 `target` 是否落在这一半内——落在则收缩到这一半，否则收缩到另一半。每轮仍能排除一半元素，保持 `O(log n)`。

```cpp
#include <vector>

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;  // 闭区间
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) return mid;
            if (nums[left] <= nums[mid]) {
                // 左半 [left, mid] 有序
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;  // target 落在左半
                } else {
                    left = mid + 1;
                }
            } else {
                // 右半 [mid, right] 有序
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;  // target 落在右半
                } else {
                    right = mid - 1;
                }
            }
        }
        return -1;
    }
};
```

- ⏱️ 时间复杂度：`O(log n)`
- 💾 空间复杂度：`O(1)`

## ⚠️ 易错点

- 判断哪半有序必须带等号：`nums[left] <= nums[mid]`。当 `left == mid`（区间只剩一两个元素）时左半只有一个元素，同样视为有序，漏掉等号会走向错误分支。
- 判断 `target` 是否落在有序半段时边界要含端点：左半用 `nums[left] <= target && target < nums[mid]`（`target == nums[mid]` 已提前返回），右半用 `nums[mid] < target && target <= nums[right]`。
- 旋转数组上不能照搬普通二分的"比大小定方向"：`nums[mid]` 与 `target` 的大小关系无法直接决定去哪半，必须先确定有序的一半。
- 数组可能旋转了 `n` 次回到完全有序（如示例中的 `[1]` 或旋转点为 0），代码需保证这种情况同样正确。

---

[← 返回目录](../../README.md)
