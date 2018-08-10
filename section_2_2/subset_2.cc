/*
ID: stapark1
LANG: C++14
TASK: subset
*/

#include <fstream>
#include <vector>

int main() {
  std::ifstream input("subset.in");
  std::ofstream output("subset.out");

  int cap;
  input >> cap;

  int totalSum = 0;
  for (int i = 1; i <= cap; ++i) totalSum += i;
  if (totalSum % 2 != 0) {
    output << 0 << std::endl;
    return 0;
  }

  std::vector<double> dp((totalSum / 2) + 1, 0);
  dp[0] = 1;
  std::vector<double> dpPrev = dp;
  for (int lastNumber = 1; lastNumber <= cap; ++lastNumber) {
    for (int sum = lastNumber; sum <= totalSum / 2; ++sum) {
      dp[sum] += dpPrev[sum - lastNumber];
    }
    dpPrev = dp;
  }

  int result = dp[totalSum / 2] / 2;
  output << result << std::endl;
  return 0;
}