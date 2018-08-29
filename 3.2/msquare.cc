/*
ID: stapark1
LANG: C++14
TASK: msquare
*/

#include <array>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <utility>

using sheet_t = std::array<int, 8>;

std::ifstream input("msquare.in");
std::ofstream output("msquare.out");

struct SheetHash {
  std::size_t operator()(const sheet_t& sheet) const {
    uint32_t integer = 0;
    for (int square : sheet) {
      integer = integer * 10 + square;
    }
    return std::hash<uint32_t>()(integer);
  }
};
std::unordered_map<sheet_t, std::string, SheetHash> seenSheets;

sheet_t a(const sheet_t& sheet) {
  sheet_t result = sheet;
  for (int i = 0; i < 8; ++i) {
    result[i] = sheet[7 - i];
  }
  return result;
}

sheet_t b(const sheet_t& sheet) {
  std::array<int, 8> newIndices {{3, 0, 1, 2, 5, 6, 7, 4}};
  sheet_t result;
  for (int i = 0; i < 8; ++i) {
    result[i] = sheet[newIndices[i]];
  }
  return result;
}

sheet_t c(const sheet_t& sheet) {
  sheet_t result = sheet;
  result[1] = sheet[6];
  result[2] = sheet[1];
  result[5] = sheet[2];
  result[6] = sheet[5];
  return result;
}

int main() {
  sheet_t initialSheet {{ 1, 2, 3, 4, 5, 6, 7, 8 }};
  sheet_t goalSheet;
  for (int i = 0; i < 8; ++i) {
    int square;
    input >> square;
    goalSheet[i] = square;
  }

  int maxOperations = 1;
  for (int i = 2; i <= 8; ++i) {
    maxOperations *= i;
  }

  std::queue<std::pair<std::string, sheet_t>> queue;
  queue.emplace(std::make_pair("", initialSheet));
  while (!queue.empty()) {
    auto sequence = queue.front().first;
    auto sheet = queue.front().second;
    queue.pop();

    if (sheet == goalSheet) {
      output << sequence.size() << std::endl;
      for (int i = 0; i < sequence.size(); ++i) {
        output << sequence[i];
        if (i % 60 == 59 && i != sequence.size() - 1)
          output << std::endl;
      }
      output << std::endl;
      return 0;
    }

    if (sequence.size() == maxOperations) break;

    std::array<sheet_t, 3> nextSheets {{ a(sheet), b(sheet), c(sheet) }};
    std::string operations = "ABC";
    for (int i = 0; i < 3; ++i) {
      if (seenSheets.find(nextSheets[i]) != seenSheets.end()) continue;
      queue.emplace(std::make_pair(sequence + operations[i], nextSheets[i]));
      seenSheets[nextSheets[i]] = sequence + operations[i];
    }
  }

  return 0;
}