/*
ID: stapark1
LANG: C++14
TASK: inflate
*/

#include <algorithm>
#include <fstream>
#include <utility>
#include <vector>

std::ifstream input("inflate.in");
std::ofstream output("inflate.out");

int main() {
  int contestLength, numClasses;
  input >> contestLength >> numClasses;

  std::vector<std::pair<int, int>> classes;
  for (int i = 0; i < numClasses; ++i) {
    int numPoints, problemLength;
    input >> numPoints >> problemLength;
    classes.emplace_back(std::make_pair(numPoints, problemLength));
  }

  // [j] = max points using j minutes.
  std::vector<uint32_t> dp(contestLength + 1, 0);
  for (int i = 1; i <= numClasses; ++i) {
    if (classes[i - 1].first < dp[classes[i - 1].second]) continue;
    for (int j = contestLength; j > 0; --j) {
      uint32_t maxPoints = dp[j];
      for (int k = 0; j - k * classes[i - 1].second >= 0; ++k) {
        maxPoints = std::max(maxPoints, k * classes[i - 1].first + dp[j - k * classes[i - 1].second]);
      }
      dp[j] = maxPoints;
    }
  }

  output << dp.back() << std::endl;
  return 0;
}
