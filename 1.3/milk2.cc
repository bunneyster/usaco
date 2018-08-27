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

  int total_farmers;
  input >> total_farmers;

  std::vector<std::pair<int, int>> intervals;
  int start, end;
  for (int i = 0; i < total_farmers; ++i) {
    input >> start >> end;
    intervals.push_back(std::make_pair(start, end));
  }

  std::sort(intervals.begin(), intervals.end());

  start = intervals[0].first;
  end = intervals[0].second;
  int longest_milk = end - start;
  int longest_rest = 0;
  for (const auto i : intervals) {
    if (i.first <= end) {
      if (i.second >= end) {
        end = i.second;  // Extend current milking interval.
      }
    } else {
      longest_milk = std::max(longest_milk, end - start);
      longest_rest = std::max(longest_rest, i.first - end);
      start = i.first;
      end = i.second;
    }
  }

  output << longest_milk << ' ' << longest_rest << std::endl;
  return 0;
}