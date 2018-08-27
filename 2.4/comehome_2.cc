/*
ID: stapark1
LANG: C++14
TASK: comehome
*/

#include <fstream>
#include <queue>
#include <unordered_map>
#include <utility>

std::ifstream input("comehome.in");
std::ofstream output("comehome.out");

int main() {
  int numPaths;
  input >> numPaths;

  std::unordered_map<char, std::unordered_map<char, int>> paths;
  for (int i = 0; i < numPaths; ++i) {
    char pasture1, pasture2;
    int length;
    input >> pasture1 >> pasture2 >> length;
    if (pasture1 == pasture2) continue;
    if (paths.find(pasture1) != paths.end()) {
      const auto it = paths[pasture1].find(pasture2);
      if (it != paths[pasture1].end() && it->second < length) continue;
    }
    paths[pasture1][pasture2] = length;
    paths[pasture2][pasture1] = length;
  }

  const long maxDistance = 10000001;
  std::pair<long, char> closest = std::make_pair(maxDistance, 'Z');
  char closestCow = 'Z';
  long closestDistance = maxDistance;
  std::unordered_map<char, long> distanceToBarn;
  for (const auto& path : paths) {
    distanceToBarn[path.first] = maxDistance;
  }
  distanceToBarn['Z'] = 0;
  std::priority_queue<std::pair<long, char>> unseenPastures;
  unseenPastures.emplace(std::make_pair(0, 'Z'));

  while (!unseenPastures.empty()) {
    long distance = unseenPastures.top().first;
    char pasture = unseenPastures.top().second;
    if (pasture - 'Z' < 0 && distance < closest.first)
      closest = unseenPastures.top();
    unseenPastures.pop();
    if (distance > distanceToBarn[pasture]) continue;

    for (const auto& neighbor : paths[pasture]) {
      long extension = distance + paths[pasture][neighbor.first];
      if (distanceToBarn[neighbor.first] > extension) {
        distanceToBarn[neighbor.first] = extension;
        unseenPastures.emplace(std::make_pair(extension, neighbor.first));
      }
    }
  }

  output << closest.second << ' ' << closest.first << std::endl;
  return 0;
}