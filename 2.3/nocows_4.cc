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

  if (numCows % 2 == 0) {
    output << 0 << std::endl;
    return 0;
  }

  // [i][j] = # ways to make tree with i nodes and height j.
  std::array<std::array<int, 100>, 200> dp {};
  std::array<std::array<int, 100>, 200> cumulative {};  // i nodes, heights 0..j
  dp[1][1] = 1;  // 1 way to make tree with 1 node of height 1.
  cumulative[1][1] = 1;

  for (int i = 1; i <= numCows; i += 2) {
    for (int j = 1; j <= treeHeight; ++j) {
      cumulative[i][j] = cumulative[i][j - 1];
      for (int tallTreeCount = 1; tallTreeCount < i; tallTreeCount += 2) {
        int smallTreeCount = i - tallTreeCount - 1;
        dp[i][j] += (dp[tallTreeCount][j - 1] * cumulative[smallTreeCount][j - 2] * 2) % 9901;
        dp[i][j] += (dp[tallTreeCount][j - 1] * dp[smallTreeCount][j - 1]) % 9901;
        dp[i][j] %= 9901;
      }
      cumulative[i][j] += dp[i][j];
      cumulative[i][j] %= 9901;
    }
  }

  output << dp[numCows][treeHeight] << std::endl;
  return 0;
}