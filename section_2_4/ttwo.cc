/*
ID: stapark1
LANG: C++14
TASK: ttwo
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <unordered_map>
#include <utility>

using orientation = std::array<int, 3>;

std::array<std::array<bool, 10>, 10> grid{};

orientation getForwardPosition(const orientation& position) {
  orientation result = position;
  switch(position[2]) {
    case 0: result[0]--; break;  // north
    case 1: result[1]++; break;  // east
    case 2: result[0]++; break;  // south
    case 3: result[1]--; break;  // west
  }
  return result;
}

orientation getNextPosition(const orientation& position) {
  orientation forwardPosition = getForwardPosition(position);
  if (forwardPosition[0] < 0 ||
      forwardPosition[0] > 9 ||
      forwardPosition[1] < 0 ||
      forwardPosition[1] > 9 ||
      grid[forwardPosition[0]][forwardPosition[1]]) {
    orientation nextPosition = position;
    nextPosition[2] = (nextPosition[2] + 1) % 4;
    return nextPosition;
  } else {
    return forwardPosition;
  }
}

std::string fullConfiguration(orientation cowPos, orientation johnPos) {
  std::string cowConfig = std::to_string(cowPos[0] * 100 + cowPos[1] * 10 + cowPos[2]);
  std::string johnConfig = std::to_string(johnPos[0] * 100 + johnPos[1] * 10 + johnPos[2]);
  return cowConfig + johnConfig;
}

int main() {
  std::ifstream input("ttwo.in");
  std::ofstream output("ttwo.out");

  orientation cowPos, johnPos;
  for (int i = 0; i < 10; ++i) {
    std::string row;
    input >> row;
    for (int j = 0; j < 10; ++j) {
      if (row[j] == 'C') {
        cowPos = orientation {i, j, 0};
      } else if (row[j] == 'F') {
        johnPos = orientation {i, j, 0};
      }
      grid[i][j] = (row[j] == '*');
    }
  }

  std::unordered_map<std::string, bool> visitedConfigurations;
  int numMinutes;
  for (numMinutes = 0; (cowPos[0] != johnPos[0]) || (cowPos[1] != johnPos[1]); ++numMinutes) {
    std::string configLookupName = fullConfiguration(cowPos, johnPos);
    if (visitedConfigurations.find(configLookupName) != visitedConfigurations.end()) {
      output << 0 << std::endl;
      return 0;
    }
    visitedConfigurations[configLookupName] = true;
    cowPos = getNextPosition(cowPos);
    johnPos = getNextPosition(johnPos);
  }

  output << numMinutes << std::endl;
  return 0;
}