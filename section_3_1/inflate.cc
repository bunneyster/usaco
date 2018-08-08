/*
ID: stapark1
LANG: C++14
TASK: inflate
*/

#include <algorithm>
#include <fstream>
#include <vector>

int main() {
  std::ifstream input("inflate.in");
  std::ofstream output("inflate.out");

  int totalTime, numClasses;
  input >> totalTime >> numClasses;

  std::vector<int> points, times;
  for (int i = 0; i < numClasses; ++i) {
    int point, time;
    input >> point >> time;
    points.emplace_back(point);
    times.emplace_back(time);
  }

  std::vector<int> dp(totalTime + 1, 0);
  for (int i = 1; i < numClasses + 1; ++i) {
    // Skip this class if it can't improve the current solution.
    if (points[i - 1] < dp[times[i - 1]]) continue;
    for (int j = times[i - 1]; j < totalTime + 1; ++j) {
      int maxPoints = 0;
      for (int k = 0; k * times[i - 1] <= j; ++k) {
        int pointsForK = dp[j - k * times[i - 1]] + k * points[i - 1];
        maxPoints = std::max(maxPoints, pointsForK);
      }
      dp[j] = maxPoints;
    }
  }

  output << dp[totalTime] << std::endl;
  return 0;
}