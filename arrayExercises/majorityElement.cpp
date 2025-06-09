#include <unordered_map>
#include <vector>
class Solution {
  public:
    int majorityElement(std::vector<int> &nums) {
        std::unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); ++i) {
            ++map[nums[i]];
            if (map[nums[i]] > nums.size() / 2) {
                return nums[i];
            }
        }
        return -1; // This line should never be reached if the input guarantees
                   // a majority element.
    }
    int majorityElementOptimized(std::vector<int> &nums) {
        int count = 0, candidate = 0;
        for (int num : nums) {
            if (count == 0) {
                candidate = num;
            }
            count += (num == candidate) ? 1 : -1;
        }
        return candidate;
    }
};
