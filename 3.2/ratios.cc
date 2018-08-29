/*
ID: stapark1
LANG: C++14
TASK: ratios
*/

#include <array>
#include <fstream>
#include <queue>

using ratio_t = std::array<int, 3>;

std::ifstream input("ratios.in");
std::ofstream output("ratios.out");
ratio_t goal;
std::array<ratio_t, 3> mixtures;

ratio_t product(const ratio_t& multiplier) {
  ratio_t result {};
  for (int mixture = 0; mixture < 3; ++mixture) {
    for (int grain = 0; grain < 3; ++grain) {
      result[grain] += mixtures[mixture][grain] * multiplier[mixture];

    }
  }
  return result;
}

bool isEquivalent(const ratio_t& totalMixture) {
  for (int i = 1; i < 3; ++i) {
    if (totalMixture[i] < goal[i]) return false;
    if (totalMixture[i] == 0 || goal[i] == 0) {
      if (totalMixture[i] != goal[i]) return false;
    } else {
      auto r1 = (float)totalMixture[i] / goal[i];
      auto r2 = (float)totalMixture[i - 1] / goal[i - 1];
      if (r1 != r2)
        return false;
    }
  }
  return true;
}

const int kMaxMultiplier = 100;

int main() {
  int grain1, grain2, grain3;
  input >> grain1 >> grain2 >> grain3;
  goal = {grain1, grain2, grain3};

  for (int i = 0; i < 3; ++i) {
    input >> grain1 >> grain2 >> grain3;
    mixtures[i] = ratio_t {grain1, grain2, grain3};
  }

  std::queue<ratio_t> queue;
  queue.emplace(ratio_t {0, 0, 0});
  while (!queue.empty()) {
    auto multiplier = queue.front();
    queue.pop();

    auto totalMixture = product(multiplier);
    if (isEquivalent(totalMixture)) {
      for (int m : multiplier) {
        output << m << ' ';
      }
      output << (totalMixture[0] / goal[0]) << std::endl;
      return 0;
    }

    int lastMix = 2;
    while (multiplier[lastMix] == 0)
      lastMix--;

    for (int i = lastMix; i < 3; ++i) {
      ratio_t nextMultiplier = multiplier;
      if (multiplier[i] < kMaxMultiplier) {
        nextMultiplier[i]++;
        queue.emplace(nextMultiplier);
      }
    }
  }

  output << "NONE\n";
  return 0;
}