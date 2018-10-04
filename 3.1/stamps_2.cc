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
  int maxStamps, numDenominations;
  input >> maxStamps >> numDenominations;

  std::vector<int> stamps;
  int maxDenomination;
  for (int i = 0; i < numDenominations; ++i) {
    int denomination;
    input >> denomination;
    stamps.emplace_back(denomination);
    maxDenomination = std::max(maxDenomination, denomination);
  }

  // The last max-denomination solutions (min # of stamps).
  std::vector<int> dp(maxDenomination, 0);
  long total = 1;
  while (true) {
    int minStamps = maxStamps + 1;
    for (int denomination : stamps) {
      if (total - denomination < 0) continue;
      minStamps = std::min(minStamps, 1 + dp.at((total - denomination) % maxDenomination));
    }
    if (minStamps > maxStamps) break;
    dp[total % maxDenomination] = minStamps;
    total++;
  }

  output << total - 1 << std::endl;
  return 0;
}