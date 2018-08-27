/*
ID: stapark1
LANG: C++11
TASK: namenum
*/

#include <fstream>
#include <unordered_map>
#include <vector>

uint64_t codeForName(std::string& name) {
  std::unordered_map<char, int> keypad = {
    {'A', 2}, {'B', 2}, {'C', 2},
    {'D', 3}, {'E', 3}, {'F', 3},
    {'G', 4}, {'H', 4}, {'I', 4},
    {'J', 5}, {'K', 5}, {'L', 5},
    {'M', 6}, {'N', 6}, {'O', 6},
    {'P', 7}, {'R', 7}, {'S', 7},
    {'T', 8}, {'U', 8}, {'V', 8},
    {'W', 9}, {'X', 9}, {'Y', 9}
  };
  uint64_t code = 0;
  for (const char letter : name) {
    if (keypad.find(letter) == keypad.end()) return 0;
    code = code * 10 + keypad[letter];
  }
  return code;
}

int main() {
  std::ifstream dict("dict.txt");
  std::ifstream input("namenum.in");
  std::ofstream output("namenum.out");

  uint64_t queryCode;
  input >> queryCode;

  std::vector<std::string> matches;
  std::string name;
  while (dict >> name)
    if (codeForName(name) == queryCode) matches.emplace_back(name);

  if (matches.empty()) {
    output << "NONE\n";
  } else {
    for (const auto& match : matches) {
      output << match << std::endl;
    }
  }
  return 0;
}