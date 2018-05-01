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
    balances[name] = 0;
  }

  std::string giver, receiver;
  int total_gift, num_friends, gift;
  for (int p = 0; p < num_people; ++p) {
    input >> giver >> total_gift >> num_friends;
    if (num_friends == 0) continue;
    gift = total_gift / num_friends;
    for (int f = 0; f < num_friends; ++f) {
      input >> receiver;
      balances[receiver] += gift;
    }
    balances[giver] -= num_friends * gift;
  }

  for (const auto name : names) {
    output << name << ' ' << balances[name] << std::endl;
  }

  return 0;
}
