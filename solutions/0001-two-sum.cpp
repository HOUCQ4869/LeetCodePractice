class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int>hash;
        for(int i = 0; i < nums.size(); i++) {
            int now = nums[i];
            int anthor = target - now;
            if (hash.count(anthor)){
                return {i, hash[anthor]};
            }
            hash[now] = i;
        }
        return {};
    }
};
