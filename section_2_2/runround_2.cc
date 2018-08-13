/*
ID: stapark1
LANG: C++14
TASK: runround
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <vector>

std::vector<int> breakdown(unsigned long number) {
  std::vector<int> result;
  while (number > 0) {
    result.emplace_back(number % 10);
    number /= 10;
  }
  std::reverse(result.begin(), result.end());
  return result;
}

bool isRunround(unsigned long number) {
  std::vector<int> digits = breakdown(number);
  std::array<bool, 10> seenDigits {false};
  int position = digits[0] % digits.size();
  int seenDigitCount = 0;
  while (!seenDigits[digits[position]] && digits[position] != 0) {
    seenDigits[digits[position]] = true;
    position = (position + digits[position]) % digits.size();
    seenDigitCount++;
  }
  return seenDigitCount == digits.size();
}

int main() {
  std::ifstream input("runround.in");
  std::ofstream output("runround.out");

  unsigned long lowerBound;
  input >> lowerBound;

  unsigned long result = lowerBound + 1;
  while (!isRunround(result))
    ++result;
  output << result << std::endl;

  return 0;
}