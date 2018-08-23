/*
ID: stapark1
LANG: C++14
TASK: preface
*/

#include <array>
#include <fstream>

std::ifstream input("preface.in");
std::ofstream output("preface.out");

std::array<char, 7> marks = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
std::array<int, 4> unitMarkIndex = {0, 2, 4, 6};

std::array<int, 3> marksForDigit(int digit, int power) {
  std::array<int, 3> markCounts;
  markCounts[0] = (digit == 4 || digit == 9) ? 1 : digit % 5;
  markCounts[1] = (digit > 3 && digit < 9);
  markCounts[2] = digit == 9;
  return markCounts;
}

int main() {
  int lastPage;
  input >> lastPage;

  std::array<int, 7> cumulativeMarks {};
  for (int page = 1; page <= lastPage; ++page) {
    for (int power = 1, number = page; number > 0; ++power, number /= 10) {
      std::array<int, 3> counts = marksForDigit(number % 10, power);
      int firstMarkIndex = unitMarkIndex[power - 1];
      for (int mark = 0; mark < 3; ++mark) {
        cumulativeMarks[firstMarkIndex + mark] += counts[mark];
      }
    }
  }

  for (int i = 0; i < 7; ++i) {
    if (cumulativeMarks[i] > 0)
      output << marks[i] << ' ' << cumulativeMarks[i] << std::endl;
  }

  return 0;
}