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

  if (max_boards >= num_cows) {
    output << num_cows << std::endl;
    return 0;
  }

  std::vector<int> occupied_stalls;
  for (std::size_t i = 0; i < num_cows; ++i) {
    int cow_stall;
    input >> cow_stall;
    occupied_stalls.emplace_back(cow_stall);
  }
  std::sort(occupied_stalls.begin(), occupied_stalls.end());

  std::vector<int> gaps;
  for (std::size_t i = 1; i < num_cows; ++i) {
    int gap = occupied_stalls[i] - occupied_stalls[i - 1] - 1;
    if (gap > 0) gaps.emplace_back(gap);
  }
  std::sort(gaps.begin(), gaps.end());

  int result = num_cows;
  for (std::size_t i = 0; i < gaps.size() - max_boards + 1; ++i)
    result += gaps[i];

  output << result << std::endl;
  return 0;
}