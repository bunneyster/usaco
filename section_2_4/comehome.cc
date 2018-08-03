/*
ID: stapark1
LANG: C++14
TASK: comehome
*/

#include <fstream>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

std::unordered_map<char, uint32_t> distances;

using distance_t = std::pair<uint32_t, char>;

int main() {
  std::ifstream input("comehome.in");
  std::ofstream output("comehome.out");

  int numEdges;
  input >> numEdges;

  std::unordered_map<char, std::vector<distance_t>> adjacencyList;
  for (int i = 0; i < numEdges; ++i) {
    char pasture1, pasture2;
    int distance;
    input >> pasture1 >> pasture2 >> distance;
    if (pasture1 == pasture2) continue;
    adjacencyList[pasture1].emplace_back(std::make_pair(distance, pasture2));
    adjacencyList[pasture2].emplace_back(std::make_pair(distance, pasture1));
  }

  std::priority_queue<distance_t> queue;
  for (const auto& adjacency : adjacencyList) {
    distances[adjacency.first] = 10000 * 1000 + 1;
  }
  distances['Z'] = 0;
  queue.emplace(std::make_pair(0, 'Z'));

  while (!queue.empty()) {
    auto closestPasture = queue.top();
    queue.pop();

    if (closestPasture.first > distances[closestPasture.second]) continue;

    for (const auto& adjEdge : adjacencyList[closestPasture.second]) {
      uint32_t newDistance = closestPasture.first + adjEdge.first;
      if (newDistance < distances[adjEdge.second]) {
        distances[adjEdge.second] = newDistance;
        queue.emplace(std::make_pair(newDistance, adjEdge.second));
      }
    }
  }

  std::pair<char, uint32_t> fastestCow = std::make_pair('1', 10000 * 1000 + 1);
  for (const auto& distance : distances) {
    if (distance.first - 'A' < 25 && distance.second < fastestCow.second) {
      fastestCow = distance;
    }
  }

  output << fastestCow.first << ' ' << fastestCow.second << std::endl;
  return 0;
}