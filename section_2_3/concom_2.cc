/*
ID: stapark1
LANG: C++14
TASK: concom
*/

#include <array>
#include <fstream>
#include <utility>
#include <queue>

std::ifstream input("concom.in");
std::ofstream output("concom.out");

int main() {
  int numOwnerships;
  input >> numOwnerships;

  std::queue<std::pair<int, int>> queue;
  std::array<std::array<int, 101>, 101> ownerships {};
  for (int i = 0; i < numOwnerships; ++i) {
    int owner, ownee, percentage;
    input >> owner >> ownee >> percentage;
    ownerships[owner][ownee] = percentage;
    if (percentage > 50)
      queue.emplace(std::make_pair(owner, ownee));
  }

  while (!queue.empty()) {
    int owner = queue.front().first;
    int intermediate = queue.front().second;
    queue.pop();
    for (int ownee = 1; ownee < 101; ++ownee) {
      if (ownee == owner) continue;
      if (ownerships[owner][ownee] > 50) continue;
      ownerships[owner][ownee] += ownerships[intermediate][ownee];
      if (ownerships[owner][ownee] > 50)
        queue.emplace(std::make_pair(owner, ownee));
    }
  }

  for (int i = 0; i < ownerships.size(); ++i) {
    for (int j = 0; j < ownerships[i].size(); ++j) {
      if (ownerships[i][j] > 50 && i != j)
        output << i << ' ' << j << std::endl;
    }
  }
  return 0;
}