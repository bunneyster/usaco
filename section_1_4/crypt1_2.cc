/*
ID: stapark1
LANG: C++11
TASK: crypt1
*/

#include <fstream>
#include <unordered_map>
#include <vector>

int main() {
  std::ifstream input("crypt1.in");
  std::ofstream output("crypt1.out");

  int num_digits;
  input >> num_digits;

  std::vector<int> digits;
  int digit;
  for (int i = 0; i < num_digits; ++i) {
    input >> digit;
    digits.push_back(digit);
  }

  // Map all possible multiplicands to a list of cryptarithmic partial products.
  std::unordered_map<int, std::vector<int>> triple_digits;
  for (const int digit1 : digits) {
    for (const int digit2 : digits) {
      for (const int digit3 : digits) {
        triple_digits[(100 * digit1) + (10 * digit2) + digit3] = std::vector<int>{};
      }
    }
  }

  int pp;  // partial_product
  for (const auto multiplicand : triple_digits) {
    for (const int multiplier : digits) {
      pp = multiplicand.first * multiplier;
      if (triple_digits.find(pp) != triple_digits.end()) {
        triple_digits[multiplicand.first].push_back(pp);
      }
    }
  }

  int cryptarithm_count = 0;
  int ppp;  // first 2 digits of partial product
  for (const auto multiplicand : triple_digits) {
    if (multiplicand.second.empty()) continue;
    for (const auto pp1 : multiplicand.second) {
      for (const auto pp2 : multiplicand.second) {
        ppp = pp1 / 10;
        if (triple_digits.find(ppp + pp2) != triple_digits.end()) {
          cryptarithm_count++;
        }
      }
    }
  }

  output << cryptarithm_count << std::endl;
  return 0;
}