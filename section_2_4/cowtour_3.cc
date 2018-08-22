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

std::ifstream input("cowtour.in");
std::ofstream output("cowtour.out");

std::vector<std::pair<int, int>> pastures;
double distance(const int pasture1, const int pasture2) {
  int xDiff = pastures[pasture1].first - pastures[pasture2].first;
  int yDiff = pastures[pasture1].second - pastures[pasture2].second;
  return std::sqrt(xDiff * xDiff + yDiff * yDiff);
}

int numPastures;
std::vector<int> fields;  // connected components
std::vector<std::vector<double>> paths;
void identifyField(int pasture, int field) {
  fields[pasture] = field;
  for (int i = 0; i < numPastures; ++i) {
    if (paths[pasture][i] == std::numeric_limits<double>::infinity()) continue;
    if (fields[i] != -1) continue;
    identifyField(i, field);
  }
}

int main() {
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

  for (int k = 0; k < numPastures; ++k) {
    for (int i = 0; i < numPastures; ++i) {
      // Magic optimization needed to pass on USACO server.
      if (paths[i][k] == std::numeric_limits<double>::infinity()) continue;
      for (int j = 0; j < numPastures; ++j) {
        if (paths[i][j] > paths[i][k] + paths[k][j])
          paths[i][j] = paths[i][k] + paths[k][j];
      }
    }
  }

  fields.resize(numPastures, -1);
  int numFields = 0;
  for (int i = 0; i < numPastures; ++i) {
    if (fields[i] != -1) continue;
    identifyField(i, numFields++);
  }

  std::vector<double> diameters(numFields, 0);
  std::vector<double> maxDistFromPasture(numPastures, 0);
  for (int i = 0; i < numPastures; ++i) {
    for (int j = 0; j < numPastures; ++j) {
      if (paths[i][j] == std::numeric_limits<double>::infinity()) continue;
      maxDistFromPasture[i] = std::max(maxDistFromPasture[i], paths[i][j]);
    }
    diameters[fields[i]] = std::max(diameters[fields[i]], maxDistFromPasture[i]);
  }

  double newDiameter = std::numeric_limits<float>::infinity();
  for (int i = 0; i < numPastures; ++i) {
    for (int j = 0; j < numPastures; ++j) {
      if (fields[i] == fields[j]) continue;
      double newDistance = maxDistFromPasture[i] + maxDistFromPasture[j] + distance(i, j);
      double diameter = std::max({newDistance, diameters[fields[i]], diameters[fields[j]]});
      newDiameter = std::min(newDiameter, diameter);
    }
  }

  output << std::fixed << std::setprecision(6) << newDiameter << std::endl;
  return 0;
}