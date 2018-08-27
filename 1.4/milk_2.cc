/*
ID: stapark1
LANG: C++11
TASK: milk
*/

#include <algorithm>
#include <fstream>
#include <utility>
#include <vector>

int main() {
  std::ifstream input("milk.in");
  std::ofstream output("milk.out");

  int quota, num_farmers;
  input >> quota >> num_farmers;

  std::vector<std::pair<int, int>> farms;
  int price, availability;
  for (int i = 0; i < num_farmers; ++i) {
    input >> price >> availability;
    farms.push_back(std::make_pair(price, availability));
  }
  std::sort(farms.begin(), farms.end());

  int money_spent = 0;
  int milk_bought;
  for (std::size_t i = 0; quota > 0; ++i) {
    milk_bought = std::min(quota, farms[i].second);
    money_spent += farms[i].first * milk_bought;
    quota -= milk_bought;
  }

  output << money_spent << std::endl;
  return 0;
}