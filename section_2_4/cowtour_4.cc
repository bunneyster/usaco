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
int numPastures;
std::vector<std::pair<int, int>> pastures;
std::vector<std::vector<double>> paths;
std::vector<int> fields;

double dist(int pasture1, int pasture2) {
  int xDiff = pastures[pasture1].first - pastures[pasture2].first;
  int yDiff = pastures[pasture1].second - pastures[pasture2].second;
  return std::sqrt(xDiff * xDiff + yDiff * yDiff);
}

void labelField(int pasture, int field) {
  fields[pasture] = field;
  for (int i = 0; i < numPastures; ++i) {
    if (pasture == i) continue;
    if (paths[pasture][i] == std::numeric_limits<double>::infinity()) continue;
    if (fields[i] > -1) continue;
    labelField(i, field);
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
    for (int j = 0; j < numPastures; ++j) {
      if (row[j] == '1') {
        paths.back().emplace_back(dist(i, j));
      } else if (i == j) {
        paths.back().emplace_back(0);
      } else {
        paths.back().emplace_back(std::numeric_limits<double>::infinity());
      }
    }
  }

  for (int k = 0; k < numPastures; ++k) {
    for (int i = 0; i < numPastures; ++i) {
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
    if (fields[i] > -1) continue;
    labelField(i, numFields++);
  }

  std::vector<double> diameters(numFields, 0);
  std::vector<double> maxDistanceFromPasture(numPastures, 0);
  for (int i = 0; i < numPastures; ++i) {
    for (int j = 0; j < numPastures; ++j) {
      if (paths[i][j] == std::numeric_limits<double>::infinity()) continue;
      maxDistanceFromPasture[i] = std::max(maxDistanceFromPasture[i], paths[i][j]);
    }
    diameters[fields[i]] = std::max(diameters[fields[i]], maxDistanceFromPasture[i]);
  }

  double minDiameter = std::numeric_limits<double>::infinity();

  for (int i = 0; i < numPastures; ++i) {
    for (int j = 0; j < numPastures; ++j) {
      if (fields[i] == fields[j]) continue;
      double distance = maxDistanceFromPasture[i] + dist(i, j) + maxDistanceFromPasture[j];
      double diameter = std::max({distance, diameters[fields[i]], diameters[fields[j]]});
      minDiameter = std::min(minDiameter, diameter);
    }
  }

  output << std::fixed << std::setprecision(6) << minDiameter << std::endl;
  return 0;
}