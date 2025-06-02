#include <vector>
class Solution {
  public:
    int removeDuplicates(std::vector<int> &nums) {
        if (nums.empty())
            return 0;
        int head = nums[0];
        int n = 1;
        while (n < nums.size()) {
            if (nums[n] != head) {
                head = nums[n];
                n++;
            } else {
                nums.erase(nums.begin() + n);
            }
        }
        return nums.size();
    }
};
// This code defines a class `Solution` with a method `removeDuplicates` that
// removes duplicates from a sorted vector of integers. It uses a two-pointer
// technique to keep track of the current unique element and modifies the vector
// in place by erasing duplicates. The method returns the new size of the vector
// after duplicates have been removed.
// // Note: This implementation modifies the input vector and may not be optimal
// for large vectors due to the use of `erase`, which can be costly in terms of
// performance. A more efficient approach would involve using a single pass with
// a separate index for unique elements.
class SolutionOptimized {
  public:
    int removeDuplicates(std::vector<int> &nums) {
        if (nums.empty())
            return 0;
        int uniqueIndex = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] != nums[uniqueIndex - 1]) {
                nums[uniqueIndex] = nums[i];
                uniqueIndex++;
            }
        }
        return uniqueIndex;
    }
};
// Example usage:
// nums = [1,1,2]
// ------------------------
// output = 2;
// nums = [1,2,_] // The first two elements are unique, and the rest can be
// ignored
