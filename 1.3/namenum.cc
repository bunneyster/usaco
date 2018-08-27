/*
ID: stapark1
LANG: C++11
TASK: namenum
*/

#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

typedef std::unordered_map<double, std::vector<std::string>> name_dict_t;

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

double serialization_for(const std::string& name) {
  double result = 0;  // Explicit assignment necessary to pass on USACO.
  for (const char letter : name) {
    if (keypad.find(letter) != keypad.end()) {
      result = (result * 10) + keypad.at(letter);
    } else {
      return 0;  // Special value indicating unviable name.
    }
  }
  return result;
}

int main() {
  std::ifstream dict("dict.txt");
  std::ifstream input("namenum.in");
  std::ofstream output("namenum.out");

  double serial;
  input >> serial;

  std::string name;
  double serialized_name;
  name_dict_t names_by_number;
  while (dict >> name) {
    if ((serialized_name = serialization_for(name))) {
      names_by_number[serialized_name].push_back(name);
    }
  }

  if (names_by_number[serial].empty()) {
    output << "NONE" << std::endl;
  } else {
    for (const auto name : names_by_number[serial]) {
      output << name << std::endl;
    }
  }

  return 0;
}