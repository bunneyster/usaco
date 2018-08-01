/*
ID: stapark1
LANG: C++14
TASK: cowtour
*/

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <limits>
#include <utility>
#include <vector>
#include <queue>
#include <unordered_map>

using coord_t = std::pair<int, int>;

std::vector<coord_t> pastures;
std::vector<std::vector<double>> distances;

double distance(int pasture1, int pasture2) {
  coord_t coord1 = pastures[pasture1];
  coord_t coord2 = pastures[pasture2];
  int xDistance = coord1.first - coord2.first;
  int yDistance = coord1.second - coord2.second;
  return std::sqrt(xDistance * xDistance + yDistance * yDistance);
}

double longestDistanceFrom(int pasture) {
  double result = 0;
  for (double d : distances[pasture]) {
    if (d != std::numeric_limits<double>::infinity())
      result = std::max(result, d);
  }
  return result;
}

int main() {
  std::ifstream input("cowtour.in");
  std::ofstream output("cowtour.out");

  int numPastures;
  input >> numPastures;

  for (int p = 0; p < numPastures; ++p) {
    int x, y;
    input >> x >> y;
    pastures.emplace_back(std::make_pair(x, y));
  }

  // Store adjacencies and initialize edge weights.
  std::vector<std::vector<bool>> adjacency;
  for (int pasture1 = 0; pasture1 < numPastures; ++pasture1) {
    distances.emplace_back(std::vector<double>(numPastures, 0));
    adjacency.emplace_back(std::vector<bool>(numPastures, false));
    std::string row;
    input >> row;
    for (int pasture2 = 0; pasture2 < numPastures; ++pasture2) {
      if (pasture1 == pasture2) {
        distances[pasture1][pasture2] = 0;
      } else if (row[pasture2] == '1') {
        distances[pasture1][pasture2] = distance(pasture1, pasture2);
        adjacency[pasture1][pasture2] = true;
      } else {
        distances[pasture1][pasture2] = std::numeric_limits<double>::infinity();
      }
    }
  }

  // Group pastures into connected components.
  std::vector<int> groupId(numPastures, -1);
  std::vector<std::vector<int>> groups;
  std::queue<int> unidentifiedPastures;
  for (int i = 0; i < numPastures; ++i) {
    if (groupId[i] >= 0) continue;
    unidentifiedPastures.push(i);
    groupId[i] = groups.size();
    groups.emplace_back(std::vector<int> {i});

    while (!unidentifiedPastures.empty()) {
      int k = unidentifiedPastures.front();
      unidentifiedPastures.pop();
      for (int j = 0; j < numPastures; ++j) {
        if (adjacency[k][j] && groupId[j] < 0) {
          groupId[j] = groupId[i];
          groups.back().emplace_back(j);
          unidentifiedPastures.push(j);
        }
      }
    }
  }

  // Compute all pairs shortest paths.
  for (int k = 0; k < numPastures; ++k) {
    for (int i = 0; i < numPastures; ++i) {
      if (distances[i][k] == std::numeric_limits<double>::infinity()) continue;
      for (int j = 0; j < numPastures; ++j) {
        if (distances[i][j] > distances[i][k] + distances[k][j])
          distances[i][j] = distances[i][k] + distances[k][j];
      }
    }
  }

  // Compute maximum distances from each pasture;
  std::vector<double> maxDistancePerPasture;
  for (int i = 0; i < numPastures; ++i) {
    maxDistancePerPasture.emplace_back(longestDistanceFrom(i));
  }

  // Compute maximum distances within each connected component.
  std::vector<double> maxDistancePerGroup;
  for (const auto& group : groups) {
    double maxDistance = 0;
    for (int pasture : group) {
      maxDistance = std::max(maxDistance, maxDistancePerPasture[pasture]);
    }
    maxDistancePerGroup.emplace_back(maxDistance);
  }

  // Compute minimum joint diameter.
  auto minDistance = std::numeric_limits<double>::infinity();
  for (std::size_t pasture1 = 0; pasture1 < numPastures; ++pasture1) {
    for (std::size_t pasture2 = 0; pasture2 < numPastures; ++pasture2) {
      if (distances[pasture1][pasture2] == std::numeric_limits<double>::infinity()) {
        double maxPasture1 = maxDistancePerPasture[pasture1];
        double maxPasture2 = maxDistancePerPasture[pasture2];
        double jointDistance = maxPasture1 + maxPasture2 + distance(pasture1, pasture2);
        double jointMax = std::max({
          maxDistancePerGroup[groupId[pasture1]],
          maxDistancePerGroup[groupId[pasture2]],
          jointDistance
        });
        minDistance = std::min(minDistance, jointMax);
      }
    }
  }

  output << std::fixed << std::setprecision(6) << minDistance << std::endl;
  return 0;
}