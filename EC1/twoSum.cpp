// Two Sum - Given an array of integers nums and an integer target, return
// indices of the two numbers such that they add up to target.
/*
　　　　　 /＞    　フ
　　　　　|    _  _ |
　 　　　 /`ミ ＿x ノ
　　 　 /　　　 　|
　　　 /　 ヽ　　ﾉ
　 　 |　　|　|　|
　 /￣|　　 |　|　|
　| (￣ヽ＿_ヽ_)__)
　\__二つ
*/

#include <vector>

std::vector<int> twoSum(std::vector<int> &nums, int target) {
    std::vector<int> result;
    for (size_t i = 0; i < nums.size(); ++i) {
        for (size_t j = i + 1; j < nums.size(); ++j) {
            if (nums[i] + nums[j] == target) {
                result.push_back(i);
                result.push_back(j);
                return result;
            }
        }
    }
    return result;
}
