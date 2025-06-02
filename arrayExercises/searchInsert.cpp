#include <iostream>
#include <vector>
class Solution {
  public:
    int searchInsert(std::vector<int> &nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return left; // If not found, return the insertion point
    }
};
// Example usage:
int main() {
    Solution solution;
    std::vector<int> nums = {1,  2,  3,  4,  5,  6,  7,  9,
                             10, 11, 12, 13, 14, 15, 16, 17};
    int target = 8;
    int result = solution.searchInsert(nums, target);
    std::cout << result << "\n";
    return 0;
}
