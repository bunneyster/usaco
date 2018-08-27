/*
ID: stapark1
LANG: C++11
TASK: skidesign
*/

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

// Cost of setting the i-th hill and those to the left (-1) or right (+1) to the given elevation.
int cost(int i, int new_elevation, int direction, std::vector<int>& elevations) {
  int result = 0;
  for (std::size_t j = i; (j >= 0) && (j < elevations.size()); j += direction) {
    result += std::pow(new_elevation - elevations[j], 2);
  }
  return result;
}

// Change the elevation of the i-th hill onwards in the left (-1) or right (+1) direction.
void renovate(int i, int elevation, int direction, std::vector<int>& elevations) {
  for (std::size_t j = i; (j >= 0) && (j < elevations.size()); j += direction) {
    elevations[j] = elevation;
  }
}

int main() {
  std::ifstream input("skidesign.in");
  std::ofstream output("skidesign.out");

  int hill_count;
  input >> hill_count;

  std::vector<int> elevations;
  int elevation;
  for (int i = 0; i < hill_count; ++i) {
    input >> elevation;
    elevations.push_back(elevation);
  }
  std::sort(elevations.begin(), elevations.end());

  int left_hill = 0;
  int right_hill = hill_count - 1;

  int left_cost = 0;
  int right_cost = 0;
  int left_cost_temp, right_cost_temp;
  std::vector<int> new_elevations = elevations;
  while (new_elevations[right_hill] - new_elevations[left_hill] > 17) {
    while (new_elevations[left_hill + 1] == new_elevations[left_hill]) {
      left_hill++;
    }
    while (new_elevations[right_hill - 1] == new_elevations[right_hill]) {
      right_hill--;
    }
    left_cost_temp = cost(left_hill, new_elevations[left_hill] + 1, -1, elevations);
    right_cost_temp = cost(right_hill, new_elevations[right_hill] - 1, 1, elevations);
    if (left_cost_temp + right_cost < left_cost + right_cost_temp) {
      left_cost = left_cost_temp;
      renovate(left_hill, new_elevations[left_hill] + 1, -1, new_elevations);
    } else {
      right_cost = right_cost_temp;
      renovate(right_hill, new_elevations[right_hill] - 1, 1, new_elevations);
    }
  }

  output << left_cost + right_cost << std::endl;

  return 0;
}