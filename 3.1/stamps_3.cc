/*
ID: stapark1
LANG: C++14
TASK: stamps
*/

#include <algorithm>
#include <fstream>
#include <vector>

std::ifstream input("stamps.in");
std::ofstream output("stamps.out");

int main() {
  int numStamps, numValues;
  input >> numStamps >> numValues;

  std::vector<int> values;
  for (int i = 0; i < numValues; ++i) {
    int value;
    input >> value;
    values.emplace_back(value);
  }

  int maxTotalValue = *std::max_element(values.begin(), values.end()) * numStamps;
  std::vector<int> dp(maxTotalValue + 1, numStamps + 1);
  dp[0] = 0;

  for (int value : values) {
    for (int total = 1; total < dp.size(); ++total) {
      if (value > total) continue;
      int minNumStamps = dp[total];
      if (1 + dp[total - value] < dp[total])
        dp[total] = 1 + dp[total - value];
    }
  }

  int result = 0;
  while (result < dp.size() && dp.at(result) <= numStamps)
    result++;

  output << result - 1 << std::endl;
  return 0;
}