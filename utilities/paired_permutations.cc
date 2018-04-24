#include <iostream>
#include <unordered_map>
#include <vector>

// Returns all permutations of length n, such that a value and its index form a
// cycle.
std::vector<std::unordered_map<int, int>> permute(int n, std::unordered_map<int, int>& current) {
  std::vector<std::unordered_map<int, int>> result;
  if (current.size() == n) {
    // std::cout << "[ ";
    // for (int i = 0; i < n; ++i) {
    //   std::cout << current.at(i) << ' ';
    // }
    // std::cout << "]" << std::endl;
    result.push_back(current);
    return result;
  }

  int first_empty_position = 0;
  while (current.find(first_empty_position) != current.end()) {
    first_empty_position++;
  }
  // std::cout << "Entering position: " << first_empty_position << std::endl;
  for (int value = 0; value < n; ++value) {
    if ((current.find(value) == current.end()) && (first_empty_position != value)) {
      // std::cout << "   Setting: " << value << std::endl;
      current[first_empty_position] = value;
      current[value] = first_empty_position;

      for (const auto permutation : permute(n, current)) {
        result.push_back(permutation);
      }

      current.erase(first_empty_position);
      current.erase(value);
    }
  }
  return result;
}

int main() {
  int n = 6;
  std::unordered_map<int, int> current;
  std::vector<std::unordered_map<int, int>> results = permute(n, current);

  for (const auto permutation : results) {
    std::cout << "[ ";
    for (int i = 0; i < n; ++i) {
      std::cout << permutation.at(i) << ' ';
    }
    std::cout << "]" << std::endl;
  }
  return 0;
}