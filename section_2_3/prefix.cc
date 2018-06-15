/*
ID: stapark1
LANG: C++14
TASK: prefix
*/

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

// The i-th element equals whether the subsequence from 0 to i can be completely
// covered by the given components. The empty sequence can be completely covered
// by the blank component.
std::vector<bool> fullPrefixes = {true};
std::unordered_map<std::string, bool> primitives;
std::string sequence;

bool fullyComponentized(int subseqEnd) {
  for (int primitiveLength = 1; primitiveLength < 11; ++primitiveLength) {
    if (subseqEnd - primitiveLength < 0) return false;

    int primitiveStart = subseqEnd - primitiveLength;
    std::string primitive = sequence.substr(primitiveStart, primitiveLength);
    if (primitives.find(primitive) != primitives.end() &&
        fullPrefixes[primitiveStart]) {
      return true;
    }
  }
  return false;
}

int main() {
  std::ifstream input("prefix.in");
  std::ofstream output("prefix.out");

  std::string primitive;
  while (input >> primitive && primitive != ".")
    primitives[primitive] = true;

  std::string line;
  while (input >> line) sequence += line;

  int maxPrefixLength = 0;
  for (int subseqEnd = 1; subseqEnd <= sequence.size(); ++subseqEnd) {
    bool isValidPrefix = fullyComponentized(subseqEnd);
    fullPrefixes.push_back(isValidPrefix);
    if (isValidPrefix && subseqEnd > maxPrefixLength)
      maxPrefixLength = subseqEnd;
  }

  output << maxPrefixLength << std::endl;
  return 0;
}