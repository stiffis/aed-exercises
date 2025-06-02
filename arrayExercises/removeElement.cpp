#include <iostream>
#include <vector>
class Solution {
  public:
    int removeElement(std::vector<int> &nums, int val) {
        int k = 0; // Pointer for the position of the next valid element
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != val) {
                nums[k] = nums[i]; // Move valid element to the front
                k++; // Increment the position for the next valid element
            }
        }
        return k; // Return the new length of the array
    }
};
// Example usage
int main() {
    Solution solution;
    std::vector<int> nums = {0, 1, 2, 2, 3, 0, 4, 2};
    int val = 2;
    int newLength = solution.removeElement(nums, val);

    // Output the new length and the modified array
    std::cout << "New length: " << newLength << std::endl;
    for (int i = 0; i < nums.size(); ++i) {
        std::cout << nums[i] << " ";
    }
    return 0;
}
