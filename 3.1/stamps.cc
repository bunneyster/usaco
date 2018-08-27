/*
ID: stapark1
LANG: C++14
TASK: stamps
*/

#include <algorithm>
#include <fstream>
#include <vector>

int main() {
  std::ifstream input("stamps.in");
  std::ofstream output("stamps.out");

  int maxStamps, numStampValues;
  input >> maxStamps >> numStampValues;

  std::vector<int> stampValues;
  for (int i = 0; i < numStampValues; ++i) {
    int stampValue;
    input >> stampValue;
    stampValues.emplace_back(stampValue);
  }

  std::sort(stampValues.begin(), stampValues.end());

  int modulo = stampValues.back();

  // i-th element is the minimum number of stamps needed to produce i cents.
  std::vector<int> dp;
  dp.resize(modulo);
  dp[0] = 0;  // 0 stamps required to make 0 cents.
  int postage = 1;
  while (true) {
    int minValue = maxStamps + 1;
    for (int stampValue : stampValues) {
      if (stampValue > postage) break;
      minValue = std::min(minValue, dp[(postage + modulo - stampValue) % modulo] + 1);
    }
    if (minValue > maxStamps)
      break;
    dp[postage % modulo] = minValue;
    ++postage;
  }

  output << postage - 1 << std::endl;

  return 0;
}