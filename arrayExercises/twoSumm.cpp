#include <vector>
class Solution {
  public:
    std::vector<int> twoSum(std::vector<int> &nums, int target) {
        int len = nums.size();
        std::vector<int> result;
        int ac = nums[0];
        for (int i = 0; i < len; ++i) {
            for (int j = 0; j < len; ++j) {
                if (nums[i] + nums[j] == target && i != j) {
                    result.push_back(i);
                    result.push_back(j);
                    return result;
                }
            }
        }
        return result;
    }
};
// Time Complexity: O(n^2)
// Now we can optimize this solution using a hash map to achieve O(n) time
// complexity.
#include <unordered_map>
class SolutionOptimized {
  public:
    std::vector<int> twoSum(std::vector<int> &nums, int target) {
        std::unordered_map<int, int> numMap;
        std::vector<int> result;

        for (int i = 0; i < nums.size(); ++i) {
            int complement = target - nums[i];
            if (numMap.find(complement) != numMap.end()) {
                result.push_back(numMap[complement]);
                result.push_back(i);
                return result;
            }
            numMap[nums[i]] = i;
        }
        return result;
    }
};
