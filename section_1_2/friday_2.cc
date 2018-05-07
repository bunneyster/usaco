/*
ID: stapark1
LANG: C++14
TASK: friday
*/

#include <fstream>
#include <array>

bool IsLeapYear(int year) {
  if (year % 100 == 0) {
    return year % 400 == 0;
  } else {
    return year % 4 == 0;
  }
}

int DaysInMonth(int month, int year) {
  std::array<const int, 12> kDaysInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (month == 1 && IsLeapYear(year)) {  // February on leap year
    return 29;
  } else {
    return kDaysInMonth[month];
  }
}

int main() {
  std::ifstream input("friday.in");
  std::ofstream output("friday.out");

  int years;
  input >> years;

  // Frequency of the 13th, in the order specified for the output.
  std::array<int, 7> frequencies{};  // Sat, Sun, Mon, Tues, Wed, Thurs, Fri
  int thirteenth = 0;  // January 13, 1990 is a Saturday.
  for (int year = 1900; year < 1900 + years; ++year) {
    for (int month = 0; month < 12; ++month) {
      frequencies[thirteenth]++;
      thirteenth = (thirteenth + DaysInMonth(month, year) - 28) % 7;
    }
  }

  output << frequencies[0];
  for (int i = 1; i < 7; ++i) {
    output << ' ' << frequencies[i];
  }
  output << std::endl;
  return 0;
}