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

  int demand, farmer_count;
  input >> demand >> farmer_count;

  std::vector<std::pair<int, int>> supplies;
  int cost, amount;
  for (int i = 0; i < farmer_count; ++i) {
    input >> cost >> amount;
    supplies.push_back(std::make_pair(cost, amount));
  }
  std::sort(supplies.begin(), supplies.end());

  int accrued_cost = 0;  // Explicit initialization required to pass on USACO.
  int remaining_demand = demand;
  int purchase_amount;
  for (std::size_t i = 0; remaining_demand > 0; ++i) {
    purchase_amount = std::min(supplies[i].second, remaining_demand);
    accrued_cost += purchase_amount * supplies[i].first;
    remaining_demand -= purchase_amount;
  }
  output << accrued_cost << std::endl;
  return 0;
}