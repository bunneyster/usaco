/*
ID: stapark1
LANG: C++11
TASK: namenum
*/

#include <fstream>
#include <unordered_map>
#include <vector>

const std::unordered_map<char, int> keypad = {
  {'A', 2}, {'B', 2}, {'C', 2},
  {'D', 3}, {'E', 3}, {'F', 3},
  {'G', 4}, {'H', 4}, {'I', 4},
  {'J', 5}, {'K', 5}, {'L', 5},
  {'M', 6}, {'N', 6}, {'O', 6},
  {'P', 7}, {'R', 7}, {'S', 7},
  {'T', 8}, {'U', 8}, {'V', 8},
  {'W', 9}, {'X', 9}, {'Y', 9}
};

uint64_t serialize(std::string name) {
  uint64_t result = 0;
  for (const char& c : name) {
    auto it = keypad.find(c);
    if (it == keypad.end()) return 0;
    result = result * 10 + it->second;
  }
  return result;
}

int main() {
  std::ifstream dict("dict.txt");
  std::ifstream input("namenum.in");
  std::ofstream output("namenum.out");

  uint64_t serial;
  input >> serial;

  std::vector<std::string> results;
  std::string name;
  while (dict >> name) {
    uint64_t serialization = serialize(name);
    if (serialization && serialization == serial) {
      results.push_back(name);
    }
  }

  if (results.empty()) {
    output << "NONE" << std::endl;
  } else {
    for (const auto result : results) {
      output << result << std::endl;
    }
  }
  return 0;
}