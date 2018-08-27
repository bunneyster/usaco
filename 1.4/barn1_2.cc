/*
ID: stapark1
LANG: C++11
TASK: barn1
*/

#include <algorithm>
#include <fstream>
#include <vector>

int main() {
  std::ifstream input("barn1.in");
  std::ofstream output("barn1.out");

  int max_boards, num_stalls, num_cows;
  input >> max_boards >> num_stalls >> num_cows;

  std::vector<int> occupied_stalls;
  int stall_number;
  for (int i = 0; i < num_cows; ++i) {
    input >> stall_number;
    occupied_stalls.push_back(stall_number);
  }
  std::sort(occupied_stalls.begin(), occupied_stalls.end());

  std::vector<int> gaps;
  int gap;
  for (std::size_t i = 1; i < occupied_stalls.size(); ++i) {
    gap = occupied_stalls[i] - occupied_stalls[i - 1] - 1;
    if (gap > 0) {
      gaps.push_back(gap);
    }
  }
  std::sort(gaps.begin(), gaps.end());

  int result = num_cows;
  if (max_boards <= gaps.size()) {
    for (int i = 0; i < gaps.size() - max_boards + 1; ++i) {
      result += gaps[i];
    }
  }

  output << result << std::endl;
  return 0;
}