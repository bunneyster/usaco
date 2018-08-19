/*
ID: stapark1
LANG: C++14
TASK: zerosum
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <numeric>
#include <vector>

int lastDigit;
std::vector<std::string> results;
std::array<char, 3> operations = {'+', '-', ' '};

int join(int lhs, int rhs) {
  bool negative = lhs < 0;
  negative ? lhs *= -10 : lhs *= 10;
  while (lhs < rhs) lhs *= 10;
  int result = lhs + rhs;
  return negative ? -1 * result : result;
}

void getAllExpressions(const std::string& base, const std::vector<int>& baseNumbers) {
  if (base.size() == lastDigit * 2 - 1) {
    if (std::accumulate(baseNumbers.begin(), baseNumbers.end(), 0) == 0)
      results.emplace_back(base);
  } else {
    char nextChar = base.back() + 1;
    int nextDigit = nextChar - '0';

    std::vector<int> numbers = baseNumbers;
    numbers.emplace_back(nextDigit);
    getAllExpressions(base + '+' + nextChar, numbers);

    numbers.back() *= -1;
    getAllExpressions(base + '-' + nextChar, numbers);

    numbers.pop_back();
    numbers.back() = join(numbers.back(), nextDigit);
    getAllExpressions(base + ' ' + nextChar, numbers);
  }
}

int main() {
  std::ifstream input("zerosum.in");
  std::ofstream output("zerosum.out");

  input >> lastDigit;

  getAllExpressions("1", std::vector<int> {1});

  std::sort(results.begin(), results.end());
  for (const auto& result : results) {
    output << result << std::endl;
  }

  return 0;
}