/*
ID: stapark1
LANG: C++11
TASK: gift1
*/

#include <fstream>
#include <unordered_map>
#include <vector>

int main() {
  std::ifstream input("gift1.in");
  std::ofstream output("gift1.out");

  int friend_count;
  input >> friend_count;

  std::vector<std::string> names;
  std::unordered_map<std::string, int> balances;
  for (int i = 0; i < friend_count; ++i) {
    std::string name;
    input >> name;
    names.emplace_back(std::move(name));
    balances[name];
  }

  for (int i = 0; i < friend_count; ++i) {
    std::string giver;
    input >> giver;

    int total_gift, split;
    input >> total_gift >> split;

    if (split == 0) {
      continue;
    }
    int gift = total_gift / split;
    for (int j = 0; j < split; ++j) {
      std::string receiver;
      input >> receiver;
      balances[receiver] += gift;
    }
    balances[giver] -= gift * split;
  }

  for (const auto name : names) {
    output << name << " " << balances[name] << std::endl;
  }

  return 0;
}