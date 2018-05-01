/*
ID: stapark1
LANG: C++11
TASK: beads
*/

#include <algorithm>
#include <fstream>

int sum(std::string beads, char color, int index, int bound, int direction) {
  int result = 0;
  int size = beads.size();
  index = (size + index) % size;
  bound = (size + bound) % size;
  while (beads[index] == color || beads[index] == 'w') {
    result++;
    index = (size + index + direction) % size;
    if (index == bound) break;
  }
  return result;
}

int main() {
  std::ifstream input("beads.in");
  std::ofstream output("beads.out");

  int num_beads;
  input >> num_beads;

  std::string beads;
  input >> beads;

  int left_b, left_r, right_b, right_r;
  int left_max, right_max;
  int total_max = 0;
  for (int i = 0; i < num_beads; ++i) {
    left_b = sum(beads, 'b', i - 1, i - 1, -1);
    left_r = sum(beads, 'r', i - 1, i - 1, -1);
    left_max = std::max(left_b, left_r);
    if (left_max == num_beads) {
      output << num_beads << std::endl;
      return 0;
    }
    right_b = sum(beads, 'b', i, i - left_max, 1);
    right_r = sum(beads, 'r', i, i - left_max, 1);
    right_max = std::max(right_b, right_r);
    total_max = std::max(total_max, left_max + right_max);
  }
  output << total_max << std::endl;
  return 0;
}