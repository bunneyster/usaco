/*
ID: stapark1
LANG: C++14
TASK: agrinet
*/

#include <fstream>
#include <vector>

int numFarms;

int closestFarm(const std::vector<bool>& connectedFarms, const std::vector<int>& distanceToNetwork) {
  int closestFarm = 0;
  for (int i = 0; i < numFarms; ++i) {
    if (connectedFarms[i]) continue;
    if (distanceToNetwork[i] < distanceToNetwork[closestFarm])
      closestFarm = i;
  }
  return closestFarm;
}

int main() {
  std::ifstream input("agrinet.in");
  std::ofstream output("agrinet.out");

  input >> numFarms;

  std::vector<std::vector<int>> distances;
  for (int farm1 = 0; farm1 < numFarms; ++farm1) {
    distances.emplace_back(std::vector<int> {});
    for (int farm2 = 0; farm2 < numFarms; ++farm2) {
      int distance;
      input >> distance;
      distances.back().emplace_back(distance);
    }
  }

  std::vector<int> distanceToNetwork(numFarms, 100001);
  std::vector<bool> connectedFarms(numFarms, false);

  int cost = 0;
  int networkSize = 1;
  connectedFarms[0] = true;

  for (int i = 1; i < numFarms; ++i) {
    distanceToNetwork[i] = distances[0][i];
  }

  while (networkSize < numFarms) {
    int farm = closestFarm(connectedFarms, distanceToNetwork);
    networkSize++;
    cost += distanceToNetwork[farm];
    connectedFarms[farm] = true;
    distanceToNetwork[farm] = 100001;

    for (int j = 1; j < numFarms; ++j) {
      if (j == farm) continue;
      if (distanceToNetwork[j] > distances[farm][j]) {
        distanceToNetwork[j] = distances[farm][j];
      }
    }
  }

  output << cost << std::endl;
  return 0;
}