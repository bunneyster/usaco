/*
ID: stapark1
LANG: C++11
TASK: milk2
*/

#include <algorithm>
#include <fstream>
#include <utility>
#include <vector>

int main() {
  std::ifstream input("milk2.in");
  std::ofstream output("milk2.out");

  int num_intervals;
  input >> num_intervals;

  std::vector<std::pair<int, int>> intervals;
  int start, end;
  for (int i = 0; i < num_intervals; ++i) {
    input >> start >> end;
    intervals.push_back(std::make_pair(start, end));
  }
  std::sort(intervals.begin(), intervals.end());

  int first_milk_time = intervals[0].first;
  int last_milk_time = intervals[0].second;
  int max_milk_time = last_milk_time - first_milk_time;
  int max_idle_time = 0;
  for (const auto interval : intervals) {
    if (interval.first > last_milk_time) {
      max_idle_time = std::max(max_idle_time, interval.first - last_milk_time);
      max_milk_time = std::max(max_milk_time, last_milk_time - first_milk_time);
      last_milk_time = interval.second;
      first_milk_time = interval.first;
    } else if (interval.second > last_milk_time) {
      last_milk_time = interval.second;
      max_milk_time = std::max(max_milk_time, last_milk_time - first_milk_time);
    }
  }

  output << max_milk_time << ' ' << max_idle_time << std::endl;
  return 0;
}