#include <unordered_map>
#include <unordered_set>
#include <vector>
class Solution {
  public:
    bool containsDuplicate(std::vector<int> &nums) {
        std::unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); ++i) {
            ++map[nums[i]];
            if (map[nums[i]] == 2) {
                return true;
            }
        }
        return false;
    }
    bool containsDuplicateOptimized(std::vector<int> &nums) {
        std::unordered_map<int, int> map;
        for (int num : nums) {
            if (++map[num] == 2) {
                return true;
            }
        }
        return false;
    }
    bool containsDuplicateSet(std::vector<int> &nums) {
        std::unordered_set<int> set;
        for (int num : nums) {
            if (!set.insert(num).second) {
                return true; // If insert fails, the element is a duplicate
            }
        }
        return false;
    }
};
