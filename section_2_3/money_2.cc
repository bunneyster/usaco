/*
ID: stapark1
LANG: C++14
TASK: money
*/

#include <fstream>
#include <vector>

std::ifstream input("money.in");
std::ofstream output("money.out");

int main() {
  int numDenominations, totalValue;
  input >> numDenominations >> totalValue;

  std::vector<int> denominations;
  for (int i = 0; i < numDenominations; ++i) {
    int denomination;
    input >> denomination;
    denominations.emplace_back(denomination);
  }

  // j-th element is # of ways to construct j money.
  std::vector<long long> dp(totalValue + 1, 0);
  dp[0] = 1;
  for (int i = 0; i < numDenominations; ++i) {
    for (int j = 0; j <= totalValue; ++j) {
      if (j < denominations[i]) continue;
      dp[j] += dp[j - denominations[i]];
    }
  }

  output << dp.back() << std::endl;
  return 0;
}