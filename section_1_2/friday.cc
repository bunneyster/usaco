/*
ID: stapark1
LANG: C++11
TASK: friday
*/

#include <array>
#include <fstream>
#include <unordered_map>

int days_in_month(int month, int year) {
  const std::array<int, 12> offsets = {1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1};
  if (month == 1) {  // February
    if (year % 100 == 0) {
      return (year % 400 == 0) ? 29 : 28;
    } else {
      return (year % 4 == 0) ? 29 : 28;
    }
  } else {
    return 30 + offsets[month];
  }
}

int main() {
  std::ifstream input("friday.in");
  std::ofstream output("friday.out");

  int years;
  input >> years;

  const std::array<char, 7> days = {'S', 'U', 'M', 'T', 'W', 'R', 'F'};
  std::unordered_map<char, int> counter;
  const int starting_year = 1900;
  int thirteenth_day = 0;  // Saturday
  for (int y = starting_year; y < starting_year + years; ++y) {
    for (int m = 0; m < 12; ++m) {
      counter[days[thirteenth_day]]++;
      thirteenth_day = (thirteenth_day + days_in_month(m, y)) % 7;
    }
  }

  output << counter[days[0]];
  for (auto it = days.begin() + 1; it < days.end(); ++it) {
    output << ' ' << counter[*it];
  }
  output << std::endl;
  return 0;
}