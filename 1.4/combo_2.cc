/*
ID: stapark1
LANG: C++11
TASK: combo
*/

#include <array>
#include <fstream>
#include <unordered_map>

struct ComboHash {
  std::size_t operator()(const std::array<int, 3>& combo) const {
    return std::hash<int>()(combo[0]) ^
           std::hash<int>()(combo[1]) ^
           std::hash<int>()(combo[2]);
  }
};

int dial_value(int number, int dial_max) {
  return ((dial_max + number - 1) % dial_max) + 1;
}

int main() {
  std::ifstream input("combo.in");
  std::ofstream output("combo.out");

  int dial_max;
  input >> dial_max;

  std::array<int, 3> official_combo;
  std::array<int, 3> new_combo;
  std::unordered_map<std::array<int, 3>, bool, ComboHash> valid_combos;
  int dial;
  for (int base_combo = 0; base_combo < 2; ++base_combo) {
    for (int i = 0; i < 3; ++i) {
      input >> dial;
      official_combo[i] = dial;
    }

    for (int error1 = -2; error1 < 3; ++error1) {
      for (int error2 = -2; error2 < 3; ++error2) {
        for (int error3 = -2; error3 < 3; ++error3) {
          new_combo = {
            dial_value(official_combo[0] + error1, dial_max),
            dial_value(official_combo[1] + error2, dial_max),
            dial_value(official_combo[2] + error3, dial_max)
          };
          valid_combos[new_combo] = true;
        }
      }
    }
  }

  output << valid_combos.size() << std::endl;
  return 0;
}