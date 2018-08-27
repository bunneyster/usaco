/*
ID: stapark1
LANG: C++14
TASK: preface
*/

#include <array>
#include <cmath>
#include <fstream>
#include <unordered_map>
#include <vector>

std::array<char, 7> letters = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
std::array<int, 10> unitCounts = {0, 1, 2, 3, 1, 0, 1, 2, 3, 1};
std::array<int, 10> fiveCounts = {0, 0, 0, 0, 1, 1, 1, 1, 1, 0};
std::array<int, 10> tenCounts = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
std::array<std::array<int, 10>, 3> allCounts = {unitCounts, fiveCounts, tenCounts};
std::array<int, 4> unitIndex = {0, 2, 4, 6};

std::unordered_map<int, std::unordered_map<char, int>> letterCountLookup;
std::unordered_map<char, int> letterCountsForDigit(int digit, int exponent) {
  auto savedSolution = letterCountLookup.find(digit * std::pow(10, exponent));
  if (savedSolution != letterCountLookup.end())
    return savedSolution->second;

  std::unordered_map<char, int> solution;
  for (int denomination = 0; denomination < 3; ++denomination) {
    int count = allCounts[denomination][digit];
    char letter = letters[unitIndex[exponent] + denomination];
    if (count) solution[letter] = count;
  }
  return solution;
}

std::unordered_map<char, int> letterCounts;
void addCounts(const std::unordered_map<char, int>& counts) {
  for (const auto& count : counts) {
    letterCounts[count.first] += count.second;
  }
}

int main() {
  std::ifstream input("preface.in");
  std::ofstream output("preface.out");

  int numPages;
  input >> numPages;

  for (int number = 0; number <= numPages; ++number) {
    int i = 0;
    for (int temp = number; temp > 0; temp /= 10, ++i) {
      addCounts(letterCountsForDigit(temp % 10, i));
    }
  }

  for (char letter : letters) {
    const auto countIt = letterCounts.find(letter);
    if (countIt != letterCounts.end())
      output << countIt->first << ' ' << countIt->second << std::endl;
  }

  return 0;
}