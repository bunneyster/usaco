/*
ID: stapark1
LANG: C++14
TASK: fracdec
*/

#include <fstream>
#include <unordered_map>
#include <vector>

int main() {
  std::ifstream input("fracdec.in");
  std::ofstream output("fracdec.out");

  int numerator, denominator;
  input >> numerator >> denominator;

  // Initialize solution with integer value.
  std::string solution = std::to_string(numerator / denominator) + '.';
  numerator %= denominator;
  if (numerator % denominator == 0) solution.push_back('0');

  // Compute decimal values, if any.
  std::unordered_map<int, int> computedDividendIndex;
  while (numerator % denominator != 0) {
    numerator *= 10;
    const auto& it = computedDividendIndex.find(numerator);
    if (it != computedDividendIndex.end()) {
      solution.insert(it->second - 1, "(");
      solution.push_back(')');
      break;
    }
    solution.push_back('0' + (numerator / denominator));
    computedDividendIndex[numerator] = solution.size();
    numerator %= denominator;
  }

  for (std::size_t i = 0; i < solution.size(); ++i) {
    output << solution[i];
    if ((i + 1) % 76 == 0) output << std::endl;
  }
  output << std::endl;

  return 0;
}