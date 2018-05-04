/*
ID: stapark1
LANG: C++11
TASK: skidesign
*/

#include <algorithm>
#include <fstream>
#include <vector>

int cost(int pos, int current_height, int change, std::vector<int>& elevations) {
  int result = 0;
  int diff;
  while (pos >= 0 && pos < elevations.size()) {
    diff = (current_height + change) - elevations.at(pos);
    result += diff * diff;
    pos -= change;
  }
  return result;
}

int main() {
  std::ifstream input("skidesign.in");
  std::ofstream output("skidesign.out");

  int num_hills;
  input >> num_hills;

  std::vector<int> elevations;
  int elevation;
  for (int i = 0; i < num_hills; ++i) {
    input >> elevation;
    elevations.push_back(elevation);
  }
  std::sort(elevations.begin(), elevations.end());

  int min_pos = 0;
  int max_pos = num_hills - 1;
  int min_height = elevations[min_pos];
  int max_height = elevations[max_pos];

  int min_cost = 0;
  int max_cost = 0;
  int mod_min_cost, mod_max_cost;
  while (max_height - min_height > 17) {
    while (elevations[min_pos + 1] == min_height) min_pos++;
    while (elevations[max_pos - 1] == max_height) max_pos--;
    mod_min_cost = cost(min_pos, min_height, 1, elevations);
    mod_max_cost = cost(max_pos, max_height, -1, elevations);
    if (mod_min_cost + max_cost < mod_max_cost + min_cost) {
      min_height += 1;
      min_cost = mod_min_cost;
    } else {
      max_height -= 1;
      max_cost = mod_max_cost;
    }
  }

  output << (min_cost + max_cost) << std::endl;
  return 0;
}