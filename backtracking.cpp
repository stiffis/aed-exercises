//* Backtracking algorithm to solve the subsets problem *//
// BACKTRACKING ALGORITHM
// nivel:= 1
// s:=s_0
// fin:= false
// repetir
//     Generar(nivel, s)
//     si Solución(nivel, s) entonces
//         fin := true
//     sino si Criterio(nivel, s) entonces
//         nivel := nivel + 1
//     sino
//         mientras NO tenga más hermanos(nivel, s) hacer
//             Retroceder(nivel, s)
//     fin
// hasta (nivel == 0) or (fin == true)
#include <iostream>
#include <vector>

void backtrack(int start, std::vector<int> &current,
               const std::vector<int> &nums,
               std::vector<std::vector<int>> &result) {
    result.push_back(current); // Add the current subset to the result

    for (int i = start; i < nums.size(); ++i) {
        current.push_back(nums[i]); // Include nums[i] in the current subset
        backtrack(i + 1, current, nums, result); // Recur with the next index
        current.pop_back(); // Backtrack: remove the last element added
    }
}
std::vector<std::vector<int>> subsets(const std::vector<int> &nums) {
    std::vector<std::vector<int>> result;
    std::vector<int> current;
    backtrack(0, current, nums, result);
    return result;
}
int main() {
    std::vector<int> nums = {1, 2, 3};
    std::vector<std::vector<int>> result = subsets(nums);

    // Print the result
    for (const auto &subset : result) {
        std::cout << "{ ";
        for (int num : subset) {
            std::cout << num << " ";
        }
        std::cout << "}" << std::endl;
    }

    return 0;
}
