/*
ID: stapark1
LANG: C++14
TASK: spin
*/

#include <array>
#include <bitset>
#include <fstream>
#include <utility>
#include <vector>

using wedge_t = std::pair<int, int>;
using state_t = std::array<std::vector<wedge_t>, 5>;

std::ifstream input("spin.in");
std::ofstream output("spin.out");
std::array<int, 5> speeds;

state_t nextState(const state_t& state) {
  std::array<std::vector<wedge_t>, 5> result = state;
  for (int wheel = 0; wheel < 5; ++wheel) {
    for (int wedge = 0; wedge < result[wheel].size(); ++wedge) {
      int startDegree = result[wheel][wedge].first;
      result[wheel][wedge].first = (startDegree + speeds[wheel]) % 360;
    }
  }
  return result;
}

bool aligns(const state_t& state) {
  std::bitset<360> totalState;
  totalState.flip();
  for (int wheel = 0; wheel < 5; ++wheel) {
    std::bitset<360> wheelState;
    for (wedge_t wedge : state[wheel]) {
      for (int degree = 0; degree <= wedge.second; ++degree) {
        wheelState[(wedge.first + degree) % 360] = true;
      }
    }
    totalState &= wheelState;
  }
  return totalState.any();
}

int main() {
  state_t wedges;
  for (int i = 0; i < 5; ++i) {
    int speed, numWedges;
    input >> speed >> numWedges;
    speeds[i] = speed;
    for (int j = 0; j < numWedges; ++j) {
      int start, extent;
      input >> start >> extent;
      wedges[i].emplace_back(std::make_pair(start, extent));
    }
  }

  state_t next = wedges;
  int second = 0;
  while (!aligns(next)) {
    next = nextState(next);
    second++;
    if (next == wedges) break;
  }

  if (aligns(next)) {
    output << second << std::endl;
  } else {
    output << "none" << std::endl;
  }
  return 0;
}