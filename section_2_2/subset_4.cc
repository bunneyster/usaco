/*
ID: stapark1
LANG: C++14
TASK: subset
*/

#include <fstream>
#include <vector>

std::ifstream input("subset.in");
std::ofstream output("subset.out");

int main() {
  int lastNumber;
  input >> lastNumber;

  int totalSum = 0;
  for (int i = 1; i <= lastNumber; ++i) {
    totalSum += i;
  }

  if (totalSum % 2 != 0) {
    output << 0 << std::endl;
    return 0;
  }

  int subsetSum = totalSum / 2;
  std::vector<uint32_t> dp(subsetSum + 1, 0);  // [j] = # ways to sum j
  dp[0] = 1;  // empty set sums to zero
  for (int i = 1; i <= lastNumber; ++i) {  // using numbers 1..i
    for (int j = subsetSum; j >= i; --j) {
      dp[j] += dp[j - i];
    }
  }


  output << dp.back() / 2 << std::endl;
  return 0;
}