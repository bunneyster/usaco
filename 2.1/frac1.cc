/*
ID: stapark1
LANG: C++14
TASK: frac1
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

using fraction = std::pair<int, int>;

struct smallerFraction {
  inline bool operator() (const fraction& lhs, fraction& rhs) {
    float leftFraction = (float)lhs.first / lhs.second;
    float rightFraction = (float)rhs.first / rhs.second;
    return leftFraction < rightFraction;
  }
};

int main() {
  std::ifstream input("frac1.in");
  std::ofstream output("frac1.out");

  int n;
  input >> n;

  std::unordered_map<float, bool> preciseValues;
  std::vector<fraction> fractions;
  fractions.emplace_back(std::make_pair(0, 1));
  fractions.emplace_back(std::make_pair(1, 1));
  for (int denominator = 2; denominator <= n; ++denominator) {
    for (int numerator = 1; numerator < denominator; ++numerator) {
      float preciseValue = (float)numerator / denominator;
      if (preciseValues.find(preciseValue) == preciseValues.end()) {
        preciseValues[preciseValue] = true;
        fractions.emplace_back(std::make_pair(numerator, denominator));
      }
    }
  }

  std::sort(fractions.begin(), fractions.end(), smallerFraction());

  for (auto frac : fractions) {
    output << frac.first << '/' << frac.second << std::endl;
  }
  return 0;
}
