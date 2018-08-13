/*
ID: stapark1
LANG: C++14
TASK: prefix
*/

#include <algorithm>
#include <fstream>
#include <vector>

int main() {
  std::ifstream input("prefix.in");
  std::ofstream output("prefix.out");

  std::vector<std::string> primitives;
  std::string primitive;
  input >> primitive;
  while (primitive != ".") {
    primitives.emplace_back(primitive);
    input >> primitive;
  }
  int minPrimitiveLength = std::min_element(primitives.begin(), primitives.end())->size();
  int maxPrimitiveLength = std::max_element(primitives.begin(), primitives.end())->size();


  std::string sequence = "";
  std::string seqLine;
  while (input >> seqLine) {
    sequence += seqLine;
  }

  std::vector<bool> composablePrefixes(sequence.size() + 1, false);
  composablePrefixes[0] = true;
  int maxPrefixLength = 0;
  for (int i = minPrimitiveLength; i < sequence.size() + 1; ++i) {
    if (i > maxPrefixLength + maxPrimitiveLength) break;
    for (const auto& primitive : primitives) {
      if (primitive.size() > i) continue;
      auto subseq = sequence.substr(i - primitive.size(), primitive.size());
      bool composable = composablePrefixes[i - primitive.size()];
      if (subseq == primitive && composable) {
        composablePrefixes[i] = true;
        maxPrefixLength = std::max(maxPrefixLength, i);
        break;
      }
    }
  }

  output << maxPrefixLength << std::endl;
  return 0;
}