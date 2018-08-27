/*
ID: stapark1
LANG: C++14
TASK: preface
*/

#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <unordered_map>

using counts_t = std::unordered_map<char, int>;

const std::array<char, 7> kRomanNumerals = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
const std::array<char, 4> kLowerUnit = {'I', 'X', 'C', 'M'};
const std::array<char, 3> kUpperUnit = {'V', 'L', 'D'};

counts_t totalCounts = {
  {'I', 0}, {'V', 0}, {'X', 0}, {'L', 0}, {'C', 0}, {'D', 0}, {'M', 0}
};

std::unordered_map<int, counts_t> savedCounts;

counts_t calculateCountsFor(int digit, int magnitude) {
  counts_t result = {
    {'I', 0}, {'V', 0}, {'X', 0}, {'L', 0}, {'C', 0}, {'D', 0}, {'M', 0}
  };
  if (digit == 0) return result;
  if (digit != 5) {
    result[kLowerUnit[magnitude]] += ((digit % 5) - 1) % 3 + 1;
  }
  if (digit > 3 && digit < 9) {
    result[kUpperUnit[magnitude]]++;
  }
  if (digit == 9) {
    result[kLowerUnit[magnitude + 1]]++;
  }
  return result;
}

counts_t countsFor(int digit, int magnitude) {
  int decimalNumber = digit * std::pow(10, magnitude);
  auto savedCount = savedCounts.find(decimalNumber);

  if (savedCount != savedCounts.end()) return savedCount->second;
  savedCounts[decimalNumber] = calculateCountsFor(digit, magnitude);

  return savedCounts[decimalNumber];
}

void addCountsForDigit(int digit, int magnitude) {
  counts_t counts = countsFor(digit, magnitude);
  for (const auto count : counts)
    totalCounts[count.first] += count.second;
}

int main() {
  std::ifstream input("preface.in");
  std::ofstream output("preface.out");

  int numPages;
  input >> numPages;

  for (int num = 1; num <= numPages; ++num) {
    int tempNum = num;
    for (int magnitude = 0; tempNum > 0; magnitude++, tempNum /= 10) {
      int digit = tempNum % 10;
      addCountsForDigit(digit, magnitude);
    }
  }

  for (const char romanNumeral : kRomanNumerals) {
    int count = totalCounts[romanNumeral];
    if (count > 0) {
      output << romanNumeral << ' ' << count << std::endl;
    }
  }

  return 0;
}