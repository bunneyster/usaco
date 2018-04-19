#include <array>
#include <iostream>
#include <unordered_set>
#include <vector>

// Returns all permutations of length n, that start with 'starts_with'.
std::vector<std::vector<int>> permute(int n, std::vector<int> starts_with, std::unordered_set<int> taken) {
  std::vector<std::vector<int>> result;
  if (starts_with.size() == n) {
    result.emplace_back(std::move(starts_with));
    return result;
  }

  for (std::size_t i = 0; i < n; ++i) {
    if (taken.find(i) == taken.end()) {
      std::vector<int> next_starts_with = starts_with;
      next_starts_with.push_back(i);
      std::unordered_set<int> next_taken = taken;
      next_taken.insert(i);
      auto new_permutations =
          permute(n, std::move(next_starts_with), std::move(next_taken));
      for (auto permutation : new_permutations) {
        result.emplace_back(std::move(permutation));
      }
    }
  }
  return result;
}

int main() {
  int n = 5;
  std::vector<int> starts_with;
  std::unordered_set<int> taken;
  std::vector<std::vector<int>> results = permute(n, starts_with, taken);

  for (const auto permutation : results) {
    std::cout << "[ ";
    for (const auto i : permutation) {
      std::cout << i << ' ';
    }
    std::cout << "]" << std::endl;
  }
  return 0;
}