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

  int num_people;
  input >> num_people;

  std::unordered_map<std::string, int> balances;
  std::vector<std::string> names;
  std::string name;
  for (int p = 0; p < num_people; ++p) {
    input >> name;
    names.push_back(name);
  }

  for (int p = 0; p < num_people; ++p) {
    int declared_gift_amount, num_friends;
    std::string giver, receiver;
    input >> giver >> declared_gift_amount >> num_friends;
    if (num_friends == 0) continue;

    int gift_per_friend = declared_gift_amount / num_friends;
    for (int f = 0; f < num_friends; ++f) {
      input >> receiver;
      balances[receiver] += gift_per_friend;
    }
    balances[giver] -= num_friends * gift_per_friend;
  }

  for (const auto name : names) {
    output << name << ' ' << balances[name] << std::endl;
  }

  return 0;
}
