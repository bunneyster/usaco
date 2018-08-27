/*
ID: stapark1
LANG: C++14
TASK: nocows
*/

#include <array>
#include <fstream>

std::ifstream input("nocows.in");
std::ofstream output("nocows.out");

int main() {
  int numCows, treeHeight;
  input >> numCows >> treeHeight;

  std::array<std::array<int, 200>, 100> dp {};
  std::array<std::array<int, 200>, 100> dpCumulative {};
  dp[1][1] = 1;
  dpCumulative[1][1] = 1;

  for (int i = 2; i <= treeHeight; ++i) {
    dpCumulative[i] = dpCumulative[i - 1];
    for (int j = 3; j <= numCows; j += 2) {
      for (int k = 1; k < j; k += 2) {
        dp[i][j] += (dp[i - 1][k] * dpCumulative[i - 2][j - k - 1]) * 2 % 9901;
        dp[i][j] += dp[i - 1][k] * dp[i - 1][j - k - 1] % 9901;
        dp[i][j] %= 9901;
      }
      dpCumulative[i][j] += dp[i][j];
      dpCumulative[i][j] %= 9901;
    }
  }

  output << dp[treeHeight][numCows] << std::endl;
  return 0;
}