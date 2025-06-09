#include <iostream>
#include <vector>
class Solution {
  public:
    int decimalToBinary(int n) {
        int binary = 0, base = 1;
        while (n > 0) {
            int last_digit = n % 2;
            n = n / 2;
            binary += last_digit * base;
            base *= 10;
        }
        return binary;
    }
    int singleNumber(std::vector<int> &nums) {
        int result = 0;
        for (int i = 0; i < nums.size(); ++i) {
            std::cout << "Current number: " << nums[i] << std::endl;
            std::cout << "Binary representation: " << decimalToBinary(nums[i])
                      << std::endl;
            result = result ^ nums[i];
            std::cout << "Current result after XOR: " << result << std::endl;
            std::cout << "Binary representation of result: "
                      << decimalToBinary(result) << std::endl;
        }
        return result;
    }
};
// The function uses XOR operation to find the single number in an array where
// every other number appears twice.
//
int main() {
    Solution solution;
    std::vector<int> nums = {4, 1, 2, 1, 2};
    int result = solution.singleNumber(nums);
    // Output should be 4
    std::cout << "The single number is: " << result << std::endl;
    return 0;
}
