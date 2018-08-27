/*
ID: stapark1
LANG: C++14
TASK: beads
*/

#include <algorithm>
#include <fstream>

int beads_of_color(std::string beads, char color, int begin, int direction) {
  int result = 0;
  int size = beads.size();
  begin = (size + begin) % size;
  while (beads[begin] == color || beads[begin] == 'w') {
    result++;
    begin = (size + begin + direction) % size;
    if (result == size) break;
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

  int total_max = 0;
  for (int i = 0; i < num_beads; ++i) {
    int left_b = beads_of_color(beads, 'b', i - 1, -1);
    int left_r = beads_of_color(beads, 'r', i - 1, -1);
    int left_max = std::max(left_b, left_r);

    int right_b = beads_of_color(beads, 'b', i, 1);
    int right_r = beads_of_color(beads, 'r', i, 1);
    int right_max = std::max(right_b, right_r);

    total_max = std::max(total_max, left_max + right_max);
  }
  output << std::min(total_max, num_beads) << std::endl;
  return 0;
}