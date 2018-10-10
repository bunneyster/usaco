/*
ID: stapark1
LANG: C++14
TASK: msquare
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <unordered_map>
#include <utility>
#include <queue>

using sheet_t = std::array<int, 8>;
using sequence_t = std::string;

std::ifstream input("msquare.in");
std::ofstream output("msquare.out");

struct ArrayHash {
  std::size_t operator() (const sheet_t& sheet) const {
    long hash = 1;
    for (int i : sheet) {
      hash = hash * 10 + i;
    }
    return hash - 12345678;
  }
};

sheet_t transform(const sheet_t& config, int transformation) {
  sheet_t result;
  std::array<int, 8> newPositions;
  switch (transformation) {
    case 0: newPositions = {7, 6, 5, 4, 3, 2, 1, 0}; break;
    case 1: newPositions = {3, 0, 1, 2, 5, 6, 7, 4}; break;
    case 2: newPositions = {0, 6, 1, 3, 4, 2, 5, 7}; break;
  }
  for (int i = 0; i < 8; ++i) {
    result[i] = config[newPositions[i]];
  }
  return result;
}

int main() {
  sheet_t target;
  for (int i = 0; i < 8; ++i) {
    int color;
    input >> color;
    target[i] = color;
  }

  sheet_t start = {1, 2, 3, 4, 5, 6, 7, 8};
  std::unordered_map<sheet_t, bool, ArrayHash> seenSheets;
  std::queue<std::pair<sheet_t, sequence_t>> queue;
  queue.emplace(std::make_pair(start, ""));
  seenSheets[start] = true;
  while (queue.front().first != target) {
    for (int i = 0; i < 3; ++i) {
      sheet_t nextSheet = transform(queue.front().first, i);
      if (seenSheets.find(nextSheet) != seenSheets.end()) continue;
      sequence_t nextSequence = queue.front().second;
      nextSequence += 'A' + i;
      queue.emplace(std::make_pair(nextSheet, nextSequence));
      seenSheets[nextSheet] = true;
    }
    queue.pop();
  }

  output << queue.front().second.size() << std::endl;
  output << queue.front().second << std::endl;
  return 0;
}