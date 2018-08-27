/*
ID: stapark1
LANG: C++11
TASK: barn1
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

class Gap {
  public:
    Gap(int s, int e) : start(s), end(e), length(e - s) {}
    int start;
    int end;
    int length;
};

bool greater_length(const Gap& lhs, const Gap& rhs) {
  return lhs.length > rhs.length;
}
bool starts_before(const Gap& lhs, const Gap& rhs) {
  return lhs.start < rhs.start;
}

int main() {
  std::ifstream input("barn1.in");
  std::ofstream output("barn1.out");

  int board_max, total_stalls, total_cows;
  input >> board_max >> total_stalls >> total_cows;

  std::vector<int> occupied_stalls;
  std::vector<Gap> gaps;
  int next_stall;
  for (int i = 0; i < total_cows; ++i) {
    input >> next_stall;
    occupied_stalls.push_back(next_stall);
  }
  std::sort(occupied_stalls.begin(), occupied_stalls.end());

  Gap gap = {occupied_stalls[0], occupied_stalls[1]};
  gaps.push_back(gap);
  for (std::size_t i = 1; i < occupied_stalls.size(); ++i) {
    gap = {gaps.back().end, occupied_stalls[i]};
    gaps.push_back(gap);
  }

  int boards_used = std::min(board_max, total_cows);
  auto last_gap_it = gaps.begin() + boards_used - 1;
  std::partial_sort(gaps.begin(), last_gap_it, gaps.end(), greater_length);
  std::sort(gaps.begin(), last_gap_it, starts_before);

  int covered_stalls = 1;
  int last_stall = occupied_stalls[0];
  auto gap_it = gaps.begin();
  for (const auto stall : occupied_stalls) {
    if ((stall == gap_it->end) && (gap_it != last_gap_it)) {
      covered_stalls++;
      gap_it++;
    } else {
      covered_stalls += stall - last_stall;
    }
    last_stall = stall;
  }

  output << covered_stalls << std::endl;
  return 0;
}
