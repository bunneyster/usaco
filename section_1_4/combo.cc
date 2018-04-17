/*
ID: stapark1
LANG: C++11
TASK: combo
*/

#include <array>
#include <fstream>
#include <unordered_set>

std::unordered_set<int> valid_positions_for(int position, int max) {
  std::unordered_set<int> result;
  for (int i = -2; i < 3; ++i) {
    result.insert(((max + position + i - 1) % max) + 1);
  }
  return result;
}

int main() {
  std::ifstream input("combo.in");
  std::ofstream output("combo.out");

  int dial_max;
  input >> dial_max;

  std::unordered_set<int> valid_combos;
  std::array<std::unordered_set<int>, 3> valid_positions;

  int position;
  for (int official_combo = 0; official_combo < 2; ++official_combo) {
    for (int i = 0; i < 3; ++i) {
      input >> position;
      valid_positions[i] = valid_positions_for(position, dial_max);
    }
    for (const auto p1 : valid_positions[0]) {
      for (const auto p2 : valid_positions[1]) {
        for (const auto p3 : valid_positions[2]) {
          valid_combos.insert((100 * p1) + (10 * p2) + p3);
        }
      }
    }
  }

  output << valid_combos.size() << std::endl;
  return 0;
}
