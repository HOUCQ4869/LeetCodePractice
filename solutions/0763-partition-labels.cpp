/**
 * @file    0763-partition-labels.cpp
 * @brief   763. 划分字母区间
 * @link    https://leetcode.cn/problems/partition-labels/
 *
 * 解法：贪心——记录最后出现位置
 * 思路：预处理每个字母的最后下标，扫描时用 end 维护片段必须延伸的最远位置，i 追上 end 即可安全切断。
 * 时间复杂度：O(n)
 * 空间复杂度：O(26)
 */

#include <vector>
#include <string>

class Solution {
public:
    vector<int> partitionLabels(string s) {
        int last[26] = {0};
        int n = (int)s.size();
        for (int i = 0; i < n; ++i) last[s[i] - 'a'] = i;

        vector<int> res;
        int start = 0, end = 0;
        for (int i = 0; i < n; ++i) {
            end = max(end, last[s[i] - 'a']);  // 当前片段必须延伸到 end
            if (i == end) {                    // 片段内字母已全部收尾
                res.push_back(i - start + 1);
                start = i + 1;
            }
        }
        return res;
    }
};
