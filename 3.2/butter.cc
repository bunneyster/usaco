/*
ID: stapark1
LANG: C++14
TASK: butter
*/

#include <array>
#include <fstream>
#include <limits>
#include <queue>
#include <unordered_map>
#include <vector>

std::ifstream input("butter.in");
std::ofstream output("butter.out");

int main() {
  int numCows, numPastures, numPaths;
  input >> numCows >> numPastures >> numPaths;

  std::unordered_map<int, int> populations;  // pasture => # cows in pasture
  for (int i = 0; i < numCows; ++i) {
    int pasture;
    input >> pasture;
    populations[pasture]++;
  }

  std::vector<std::vector<double>> distances;
  distances.emplace_back(std::vector<double>(numPastures + 1, 0));
  for (int i = 1; i <= numPastures; ++i) {
    distances.emplace_back(std::vector<double> {0});
    for (int j = 1; j <= numPastures; ++j) {
      if (i == j) {
        distances[i].emplace_back(0);
      } else {
        distances[i].emplace_back(std::numeric_limits<double>::infinity());
      }
    }
  }

  std::vector<std::vector<int>> neighbors(numPastures + 1, std::vector<int> {});
  for (int i = 0; i < numPaths; ++i) {
    int pasture1, pasture2, path;
    input >> pasture1 >> pasture2 >> path;
    distances[pasture1][pasture2] = path;
    distances[pasture2][pasture1] = path;
    neighbors[pasture1].emplace_back(pasture2);
    neighbors[pasture2].emplace_back(pasture1);
  }

  for (int source = 1; source <= numPastures; ++source) {
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> closestPastures;
    closestPastures.emplace(std::make_pair(0, source));
    while (!closestPastures.empty()) {
      int distance = closestPastures.top().first;
      int pasture = closestPastures.top().second;
      closestPastures.pop();

      if (distance > distances[source][pasture]) continue;
      distances[source][pasture] = distance;

      for (int neighbor : neighbors[pasture]) {
        double newDistance = distance + distances[pasture][neighbor];
        closestPastures.emplace(std::make_pair(newDistance, neighbor));
      }
    }
  }

  double minimumMileage = 500 * 1450 * 224 + 1;
  for (int pasture = 1; pasture <= numPastures; ++pasture) {
    double totalMileage = 0;
    for (const auto& population : populations) {
      totalMileage += population.second * distances[pasture][population.first];
    }
    minimumMileage = std::min(minimumMileage, totalMileage);
  }

  output << (uint64_t)minimumMileage << std::endl;

  return 0;
}