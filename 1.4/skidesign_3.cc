/*
ID: stapark1
LANG: C++14
TASK: skidesign
*/

#include <algorithm>
#include <fstream>
#include <vector>

int Cost(int pos, int new_elevation, int direction, std::vector<int>& elevations) {
  int result = 0;
  while (pos >= 0 && pos < elevations.size()) {
    int elevation_diff = new_elevation - elevations.at(pos);
    result += elevation_diff * elevation_diff;
    pos += direction;
  }
  return result;
}

int main() {
  std::ifstream input("skidesign.in");
  std::ofstream output("skidesign.out");

  int num_hills;
  input >> num_hills;

  std::vector<int> elevations;
  for (std::size_t i = 0; i < num_hills; ++i) {
    int elevation;
    input >> elevation;
    elevations.push_back(elevation);
  }
  std::sort(elevations.begin(), elevations.end());

  int min_pos = 0;
  int max_pos = num_hills - 1;
  int min_elevation = elevations.at(min_pos);
  int max_elevation = elevations.at(max_pos);
  int grow_cost = 0;
  int shrink_cost = 0;
  while (max_elevation - min_elevation > 17) {
    while (elevations.at(min_pos + 1) == min_elevation) min_pos++;
    while (elevations.at(max_pos - 1) == max_elevation) max_pos--;
    int next_grow_cost = Cost(min_pos, min_elevation + 1, -1, elevations);
    int next_shrink_cost = Cost(max_pos, max_elevation - 1, 1, elevations);
    if (next_grow_cost + shrink_cost < next_shrink_cost + grow_cost) {
      min_elevation++;
      grow_cost = next_grow_cost;
    } else {
      max_elevation--;
      shrink_cost = next_shrink_cost;
    }
  }

  output << (grow_cost + shrink_cost) << std::endl;
  return 0;
}