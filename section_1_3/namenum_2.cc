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

float serialize(std::string name) {
  float result = 0;
  for (const char c : name) {
    if (keypad.find(c) == keypad.end()) return 0;
    result = result * 10 + keypad.at(c);
  }
  return result;
}

int main() {
  std::ifstream dict("dict.txt");
  std::ifstream input("namenum.in");
  std::ofstream output("namenum.out");

  float serial;
  input >> serial;

  std::unordered_map<float, std::vector<std::string>> serializations;
  std::string name;
  float serialization;
  while (dict >> name) {
    serialization = serialize(name);
    if (serialization) {
      serializations[serialization];
      serializations[serialization].push_back(name);
    }
  }

  auto results = serializations[serial];
  if (results.empty()) {
    output << "NONE" << std::endl;
  } else {
    for (const auto result : results) {
      output << result << std::endl;
    }
  }
  return 0;
}