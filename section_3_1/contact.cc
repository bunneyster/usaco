/*
ID: stapark1
LANG: C++14
TASK: contact
*/

#include <algorithm>
#include <fstream>
#include <map>
#include <unordered_map>
#include <vector>

struct patternSort {
  bool operator()(std::string lhs, std::string rhs) {
    if (lhs.size() == rhs.size()) return lhs < rhs;
    return lhs.size() < rhs.size();
  }
} patternCompare;

int main() {
  std::ifstream input("contact.in");
  std::ofstream output("contact.out");

  int minLength, maxLength, numFrequencies;
  input >> minLength >> maxLength >> numFrequencies;

  std::string sequence = "";
  std::string seqLine;
  while (input >> seqLine) sequence += seqLine;

  std::unordered_map<std::string, int> patterns;
  for (int i = 0; i < sequence.size(); ++i) {
    for (int j = minLength; j <= maxLength && sequence.size() - i >= j; ++j) {
      std::string subseq = sequence.substr(i, j);
      patterns[subseq]++;
    }
  }

  std::map<int, std::vector<std::string>> frequencies;
  for (const auto& patternCount : patterns) {
    frequencies[patternCount.second].emplace_back(patternCount.first);
  }

  int printCount = 0;
  for (auto it = frequencies.rbegin(); it != frequencies.rend(); ++it) {
    if (printCount == numFrequencies) break;

    output << it->first << std::endl;
    std::sort(it->second.begin(), it->second.end(), patternCompare);
    for (int j = 0; j < it->second.size(); ++j) {
      output << it->second[j];
      if ((j + 1) % 6 == 0 || j == it->second.size() - 1) {
        output << std::endl;
      } else {
        output << ' ';
      }
    }
    printCount++;
  }
  return 0;
}