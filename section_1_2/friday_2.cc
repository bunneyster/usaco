/*
ID: stapark1
LANG: C++11
TASK: friday
*/

#include <fstream>
#include <array>

std::array<int, 7> frequencies{};  // Sat, Sun, Mon, Tues, Wed, Thurs, Fri
std::array<int, 12> days_in_month = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool is_leap_year(int year) {
  if (year % 100 == 0) {
    return year % 400 == 0;
  } else {
    return year % 4 == 0;
  }
}

int days_this_month(int month, int year) {
  if (month == 1) {  // February
    return is_leap_year(year) ? 29 : 28;
  } else {
    return days_in_month[month];
  }
}

int main() {
  std::ifstream input("friday.in");
  std::ofstream output("friday.out");

  int years;
  input >> years;

  int friday = 0;  // Saturday, 1900
  for (int year = 1900; year < 1900 + years; ++year) {
    for (int month = 0; month < 12; ++month) {
      frequencies[friday]++;
      friday = (friday + days_this_month(month, year) - 28) % 7;
    }
  }

  output << frequencies[0];
  for (int i = 1; i < 7; ++i) {
    output << ' ' << frequencies[i];
  }
  output << std::endl;
  return 0;
}