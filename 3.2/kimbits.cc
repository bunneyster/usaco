/*
ID: stapark1
LANG: C++14
TASK: kimbits
*/

#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <fstream>

std::ifstream input("kimbits.in");
std::ofstream output("kimbits.out");

// [i][j] = # of strings of length i with at most j set bits.
std::array<std::array<uint32_t, 32>, 32> dp {};

void printSolution(int i, int j, uint32_t rank) {
  if (i == 0) {
    output << std::endl;
    return;
  }

  uint32_t zeroCount = dp[i - 1][j];
  if (rank < zeroCount) {
    output << 0;
    printSolution(i - 1, j, rank);
  } else {
    output << 1;
    printSolution(i - 1, j - 1, rank - zeroCount);
  }
}

int main() {
  int stringLength, maxSetBitCount;
  uint32_t finalRank;
  input >> stringLength >> maxSetBitCount >> finalRank;

  std::fill(dp[0].begin(), dp[0].end(), 1);  // Empty string
  for (int i = 1; i <= stringLength; ++i) {
    dp[i][0] = 1;  // Zero counts as first result, e.g. "0", "00", "000"
    for (int j = 1; j <= maxSetBitCount; ++j) {
      dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
    }
  }

  // Rank is calculated using 0-based indexing.
  printSolution(stringLength, maxSetBitCount, finalRank - 1);
  return 0;
}
