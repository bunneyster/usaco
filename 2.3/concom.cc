/*
ID: stapark1
LANG: C++14
TASK: concom
*/

#include <array>
#include <fstream>
#include <queue>
#include <utility>

int main() {
  std::ifstream input("concom.in");
  std::ofstream output("concom.out");

  int numOwnerships;
  input >> numOwnerships;

  std::array<std::array<int, 101>, 101> ownership{};
  std::queue<std::pair<int, int>> newControls;
  for (int i = 0; i < numOwnerships; ++i) {
    int owner, ownee, percentage;
    input >> owner >> ownee >> percentage;
    if (owner == ownee) continue;
    ownership[owner][ownee] = percentage;
    if (percentage > 50) {
      newControls.emplace(std::make_pair(owner, ownee));
    }
  }

  while (!newControls.empty()) {
    int controller = newControls.front().first;
    int intermediateControllee = newControls.front().second;
    newControls.pop();
    for (int controllee = 1; controllee < 101; ++controllee) {
      if (controller == controllee) continue;
      int indirectOwnership = ownership[intermediateControllee][controllee];
      if (!indirectOwnership) continue;
      if (ownership[controller][controllee] > 50) continue;
      ownership[controller][controllee] += indirectOwnership;
      if (ownership[controller][controllee] > 50) {
        newControls.emplace(std::make_pair(controller, controllee));
      }
    }
  }

  for (std::size_t h = 1; h < 101; ++h) {
    for (std::size_t s = 1; s < 101; ++s) {
      if (ownership[h][s] > 50) {
        output << h << ' ' << s << std::endl;
      }
    }
  }

  return 0;
}