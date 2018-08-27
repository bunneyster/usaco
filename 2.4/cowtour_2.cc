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
#include <queue>
#include <utility>
#include <vector>

using pasture_t = std::pair<int, int>;

std::ifstream input("cowtour.in");
std::ofstream output("cowtour.out");
std::vector<pasture_t> pastures;
std::vector<std::vector<double>> paths;

double distance(const int pasture1, const int pasture2) {
  int xDiff = pastures[pasture1].first - pastures[pasture2].first;
  int yDiff = pastures[pasture1].second - pastures[pasture2].second;
  return std::sqrt(xDiff * xDiff + yDiff * yDiff);
}

double maxDistanceFrom(const int pasture) {
  double distance = 0;
  for (const double& path : paths[pasture]) {
    if (path == std::numeric_limits<double>::infinity()) continue;
    distance = std::max(distance, path);
  }
  return distance;
}

int main() {
  int numPastures;
  input >> numPastures;

  for (int i = 0; i < numPastures; ++i) {
    int x, y;
    input >> x >> y;
    pastures.emplace_back(std::make_pair(x, y));
  }

  for (int i = 0; i < numPastures; ++i) {
    paths.emplace_back(std::vector<double> {});
    std::string row;
    input >> row;
    for (int j = 0; j < row.size(); ++j) {
      if (row[j] == '1') {
        paths.back().emplace_back(distance(i, j));
      } else if (i == j) {
        paths.back().emplace_back(0);
      } else {
        paths.back().emplace_back(std::numeric_limits<double>::infinity());
      }
    }
  }

  // Initialize every pasture to component 0.
  std::vector<int> componentLookup(numPastures, -1);
  std::vector<std::vector<int>> components;
  for (int p = 0; p < numPastures; ++p) {
    if (componentLookup[p] >= 0) continue;  // Uncategorized pasture
    componentLookup[p] = components.size();
    components.emplace_back(std::vector<int> {p});
    std::queue<int> neighbors;
    neighbors.emplace(p);
    while (!neighbors.empty()) {
      int i = neighbors.front();
      neighbors.pop();
      for (int j = 0; j < numPastures; ++j) {
        if (paths[i][j] != std::numeric_limits<double>::infinity() &&
            componentLookup[j] < 0) {  // Uncategorized neighbor
          neighbors.emplace(j);
          componentLookup[j] = componentLookup[i];
          components.back().emplace_back(j);
        }
      }
    }
  }

  // Compute all-pairs shortest paths.
  for (int k = 0; k < numPastures; ++k) {
    for (int i = 0; i < numPastures; ++i) {
      if (paths[i][k] == std::numeric_limits<double>::infinity()) continue;
      for (int j = 0; j < numPastures; ++j) {
        if (paths[i][j] > paths[i][k] + paths[k][j])
          paths[i][j] = paths[i][k] + paths[k][j];
      }
    }
  }

  // Compute diameters per component.
  std::vector<double> diameters;
  for (const auto& componentPastures : components) {
    double diameter = 0;
    for (int i = 0; i < componentPastures.size(); ++i) {
      for (int j = i + 1; j < componentPastures.size(); ++j) {
        if (paths[i][j] == std::numeric_limits<double>::infinity()) continue;
        diameter = std::max(diameter, paths[i][j]);
      }
    }
    diameters.emplace_back(diameter);
  }

  // Find minimum new edge.
  double minJointDiameter = std::numeric_limits<double>::infinity();
  for (int component1 = 0; component1 < components.size(); ++component1) {
    for (int component2 = component1 + 1; component2 < components.size(); ++component2) {
      double minJointDistance = std::numeric_limits<double>::infinity();
      for (int pasture1 : components[component1]) {
        for (int pasture2 : components[component2]) {
          double maxDistFromPasture1 = maxDistanceFrom(pasture1);
          double maxDistFromPasture2 = maxDistanceFrom(pasture2);
          double jointDistance = maxDistFromPasture1 + distance(pasture1, pasture2) + maxDistFromPasture2;
          minJointDistance = std::min(minJointDistance, jointDistance);
        }
      }
      double jointDiameter = std::max({diameters[component1], diameters[component2], minJointDistance});
      minJointDiameter = std::min(minJointDiameter, jointDiameter);
    }
  }

  output << std::fixed << std::setprecision(6) << minJointDiameter << std::endl;

  return 0;
}