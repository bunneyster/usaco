#include <limits>
#include <queue>
#include <utility>
#include <vector>

using path = std::pair<double, int>;  // (distance, vertex index)

int numVertices;
std::vector<std::vector<path>> adjList;  // (edge weight, vertex index)

int main() {
  int source = 0;
  std::priority_queue<path> queue;
  queue.emplace(std::make_pair(0, source));

  std::vector<double> distances(numVertices, std::numeric_limits<double>::infinity());
  distances[source] = 0;

  while (!queue.empty()) {
    auto u = queue.top();
    queue.pop();

    if (u.first > distances[u.second]) continue;

    for (auto v : adjList[u.second]) {
      double edge = v.first;
      if (distances[v.second] > distances[u.second] + edge) {
        distances[v.second] = distances[u.second] + edge;
        queue.emplace(std::make_pair(distances[v.second], v.first));
      }
    }
  }
  return 0;
}