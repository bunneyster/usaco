/*
ID: stapark1
LANG: C++14
TASK: contact
*/

#include <algorithm>
#include <fstream>
#include <map>
#include <queue>
#include <unordered_map>

std::ifstream input("contact.in");
std::ofstream output("contact.out");

struct PatternSort {
  bool operator()(std::string lhs, std::string rhs) {
    if (lhs.size() == rhs.size()) {
      return lhs < rhs;
    } else {
      return lhs.size() < rhs.size();
    }
  }
} patternSort;

int main() {
  int minLength, maxLength, numFrequencies;
  input >> minLength >> maxLength >> numFrequencies;

  std::string pattern;
  std::string line;
  while (input >> line) {
    pattern.append(line);
  }

  std::unordered_map<std::string, int> frequencies;
  for (int i = 0; i < pattern.size(); ++i) {
    for (int length = minLength; length <= maxLength && i + length <= pattern.size(); ++length) {
      frequencies[pattern.substr(i, length)]++;
    }
  }

  std::map<int, std::vector<std::string>, std::greater<int>> patternsByFreq;
  for (const auto& it : frequencies) {
    patternsByFreq[it.second].emplace_back(it.first);
  }

  for (const auto& it : patternsByFreq) {
    std::sort(patternsByFreq[it.first].begin(), patternsByFreq[it.first].end(), patternSort);
  }

  int index = 0;
  for (const auto& it : patternsByFreq) {
    if (index++ == numFrequencies) break;
    output << it.first << std::endl;

    for (int i = 0; i < it.second.size(); ++i) {
      output << it.second[i];
      if (i % 6 == 5 || i == it.second.size() - 1) {
        output << std::endl;
      } else {
        output << ' ';
      }
    }
  }
  return 0;
}
