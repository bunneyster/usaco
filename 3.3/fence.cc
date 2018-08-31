/*
ID: stapark1
LANG: C++14
TASK: fence
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

std::ifstream input("fence.in");
std::ofstream output("fence.out");

std::unordered_map<int, std::vector<int>> adjList;
std::vector<int> path;

void deleteAdjacency(int node, int neighbor) {
  for (int i = 0; i < adjList[node].size(); ++i) {
    if (adjList[node][i] == neighbor) {
      adjList[node].erase(adjList[node].begin() + i);
      return;
    }
  }
}

void deleteFence(int intersect1, int intersect2) {
  deleteAdjacency(intersect1, intersect2);
  deleteAdjacency(intersect2, intersect1);
}

void getPath(int intersect) {
  while (!adjList[intersect].empty()) {
    int neighbor = adjList[intersect][0];
    deleteFence(intersect, neighbor);
    getPath(neighbor);
  }
  path.emplace_back(intersect);
}

int main() {
  int numFences;
  input >> numFences;

  int lowestIntersect = 501;
  for (int i = 0; i < numFences; ++i) {
    int intersect1, intersect2;
    input >> intersect1 >> intersect2;
    adjList[intersect1].emplace_back(intersect2);
    adjList[intersect2].emplace_back(intersect1);
    lowestIntersect = std::min({lowestIntersect, intersect1, intersect2});
  }

  int start = 501;
  for (const auto& neighbors : adjList) {
    if (neighbors.second.size() % 2 == 1)
      start = std::min(start, neighbors.first);
  }
  if (start == 501)
    start = lowestIntersect;

  for (auto it = adjList.begin(); it != adjList.end(); ++it) {
    std::sort(it->second.begin(), it->second.end());
  }

  getPath(start);
  for (auto it = path.rbegin(); it != path.rend(); ++it) {
    output << *it << std::endl;
  }
  return 0;
}