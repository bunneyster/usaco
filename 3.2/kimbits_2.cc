/*
ID: stapark1
LANG: C++14
TASK: kimbits
*/

#include <fstream>
#include <vector>

std::ifstream input("kimbits.in");
std::ofstream output("kimbits.out");

// [i][j] = # of i-bit strings with at most j set bits.
// uint32_t, not long, works on USACO.
std::vector<std::vector<uint32_t>> dp;

void printIthElement(int stringSize, int maxSetBits, uint32_t index) {
  if (stringSize == 0) return;
  uint32_t numElementsStartWith0 = dp[stringSize - 1][maxSetBits];
  if (index <= numElementsStartWith0) {
    output << '0';
    printIthElement(stringSize - 1, maxSetBits, index);
  } else {
    output << '1';
    printIthElement(stringSize - 1, maxSetBits - 1, index - numElementsStartWith0);
  }
}

int main() {
  int stringSize, maxSetBits;
  uint32_t finalIndex;
  input >> stringSize >> maxSetBits >> finalIndex;

  dp.emplace_back(std::vector<uint32_t>(maxSetBits + 1, 1));
  for (int i = 1; i <= stringSize; ++i) {
    dp.emplace_back(std::vector<uint32_t> {1});
    for (int j = 1; j <= maxSetBits; ++j) {
      dp.back().emplace_back(dp[i - 1][j] + dp[i - 1][j - 1]);
    }
  }

  printIthElement(stringSize, maxSetBits, finalIndex);
  output << std::endl;
  return 0;
}