/*
ID: stapark1
LANG: C++14
TASK: wormhole
*/

#include <fstream>
#include <iostream>
#include <utility>
#include <unordered_map>
#include <vector>

using pairing_t = std::unordered_map<int, int>;

std::vector<pairing_t> EntrancePaths(pairing_t temp, std::vector<int> holeOptions) {
  std::vector<pairing_t> result;

  if (holeOptions.empty()) {
    result.push_back(temp);
  } else {
    int hole1 = holeOptions.back();
    holeOptions.pop_back();

    for (int i = 0; i < holeOptions.size(); ++i) {
      int hole2 = holeOptions[i];
      std::vector<int> nextHoleOptions = holeOptions;
      nextHoleOptions.erase(nextHoleOptions.begin() + i);

      temp[hole1] = hole2;
      temp[hole2] = hole1;
      for (pairing_t entrancePath : EntrancePaths(temp, nextHoleOptions)) {
        result.push_back(entrancePath);
      }

      temp.erase(hole2);
    }
  }
  return result;
}

bool HasCycle(int currentHole, pairing_t& entrancePaths, pairing_t& exitPaths, std::vector<bool>& visitedHoles, std::vector<bool>& seenHoles) {
  if (seenHoles[currentHole]) return true;
  visitedHoles[currentHole] = true;
  seenHoles[currentHole] = true;

  int exitHole = entrancePaths.find(currentHole)->second;
  auto exitPath = exitPaths.find(exitHole);
  if (exitPath == exitPaths.end()) return false;

  int nextEntrance = entrancePaths.find(exitPath->second)->first;
  return HasCycle(nextEntrance, entrancePaths, exitPaths, visitedHoles, seenHoles);
}

int main() {
  std::ifstream input("wormhole.in");
  std::ofstream output("wormhole.out");

  int numHoles;
  input >> numHoles;

  std::vector<std::pair<int, int>> holes;
  for (int i = 0; i < numHoles; ++i) {
    int x, y;
    input >> x >> y;
    holes.emplace_back(std::make_pair(x, y));
  }

  std::unordered_map<int, int> exitPaths;
  for (int hole1 = 0; hole1 < numHoles; ++hole1) {
    for (int hole2 = 0; hole2 < numHoles; ++hole2) {
      if (hole1 == hole2) continue;
      if (holes[hole1].second == holes[hole2].second && holes[hole1].first < holes[hole2].first) {
        auto pair = exitPaths.find(hole1);
        if (pair == exitPaths.end() || holes[hole2].first < holes[pair->second].first) {
          exitPaths[hole1] = hole2;
        }
      }
    }
  }

  int result = 0;
  pairing_t temp{};
  std::vector<int> holeOptions;
  for (int i = 0; i < numHoles; ++i) holeOptions.push_back(i);
  for (auto entrancePaths : EntrancePaths(temp, holeOptions)) {
    std::vector<bool> visitedHoles, seenHoles;
    for (int i = 0; i < numHoles; ++i) {
      visitedHoles.push_back(false);
      seenHoles.push_back(false);
    }

    for (int i = 0; i < numHoles; ++i) {
      if (visitedHoles[i]) continue;
      if (HasCycle(i, entrancePaths, exitPaths, visitedHoles, seenHoles)) {
        result++;
        break;
      }
      for (int i = 0; i < numHoles; ++i) seenHoles[i] = false;
    }
  }

  output << result << std::endl;
  return 0;
}