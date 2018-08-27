/*
ID: stapark1
LANG: C++14
TASK: runround
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <vector>

using sequence_t = std::vector<int>;
using options_t = std::array<bool, 10>;  // n-th element indicates whether n has been taken.

sequence_t numToSequence(unsigned long number) {
  sequence_t result;
  for (int lastDigit = number % 10; number > 0; number /= 10, lastDigit = number % 10) {
    result.push_back(lastDigit);
  }
  std::reverse(result.begin(), result.end());
  return result;
}

bool isRunaround(unsigned long number) {
  sequence_t sequence = numToSequence(number);
  options_t options {};
  options[sequence[0]] = true;

  int numVerifiedDigits = 1;
  int position = sequence[0] % sequence.size();
  while (position != 0) {
    if (options[sequence[position]]) return false;
    options[sequence[position]] = true;

    position += sequence[position];
    position %= sequence.size();
    numVerifiedDigits++;
  }

  return numVerifiedDigits == sequence.size();
}

int main() {
  std::ifstream input("runround.in");
  std::ofstream output("runround.out");

  unsigned long M;
  input >> M;

  unsigned long result = M + 1;
  while (!isRunaround(result)) result++;

  output << result << std::endl;

  return 0;
}