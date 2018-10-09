/*
ID: stapark1
LANG: C++14
TASK: ratios
*/

#include <array>
#include <fstream>
#include <iostream>

using ratio_t = std::array<int, 3>;

std::ifstream input("ratios.in");
std::ofstream output("ratios.out");

ratio_t goal;
std::array<ratio_t, 3> mixtures;
int goalMultiple(const ratio_t& multipliers) {
  ratio_t totalMixture = {0, 0, 0};
  for (int grain = 0; grain < 3; ++grain) {
    for (int mixture = 0; mixture < 3; ++mixture) {
      totalMixture[grain] += multipliers[mixture] * mixtures[mixture][grain];
    }
  }

  for (int grain = 0; grain < 3; ++grain) {
    if (totalMixture[grain] < goal[grain]) return 0;
  }

  ratio_t goalMultiplier;
  for (int grain = 0; grain < 3; ++grain) {
    if (goal[grain] == 0) {
      if (totalMixture[grain] != 0) return 0;
      goalMultiplier[grain] = 0;
    } else {
      if (totalMixture[grain] % goal[grain] != 0) return 0;
      goalMultiplier[grain] = totalMixture[grain] / goal[grain];
    }
  }

  for (int grain = 1; grain < 3; ++grain) {
    if (goalMultiplier[grain] == 0 || goalMultiplier[grain - 1] == 0) continue;
    if (goalMultiplier[grain] != goalMultiplier[grain - 1]) return 0;
  }
  return goalMultiplier[0];
}

int main() {
  for (int i = 0; i < 3; ++i) {
    int amount;
    input >> amount;
    goal[i] = amount;
  }

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      int amount;
      input >> amount;
      mixtures[i][j] = amount;
    }
  }

  for (int grain1 = 0; grain1 < 101; ++grain1) {
    for (int grain2 = 0; grain2 < 101; ++grain2) {
      for (int grain3 = 0; grain3 < 101; ++grain3) {
        int multiple = goalMultiple(ratio_t {grain1, grain2, grain3});
        if (multiple > 0) {
          output << grain1 << ' ' << grain2 << ' ' << grain3 << ' ' << multiple << std::endl;
          return 0;
        }
      }
    }
  }

  output << "NONE\n";
  return 0;
}