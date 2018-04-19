#include <iostream>
#include <unordered_set>
#include <vector>

// Returns all permutations of length n, that start with 'starts_with'.
std::vector<std::vector<int>> permute(int n, std::vector<int>& starts_with, std::unordered_set<int>& taken) {
  std::vector<std::vector<int>> result;
  if (starts_with.size() == n) {
    result.push_back(starts_with);
    return result;
  }

  for (int i = 0; i < n; ++i) {
    if (taken.find(i) == taken.end()) {
      starts_with.push_back(i);
      taken.insert(i);

      for (const auto permutation : permute(n, starts_with, taken)) {
        result.push_back(permutation);
      }

      starts_with.pop_back();
      taken.erase(i);
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