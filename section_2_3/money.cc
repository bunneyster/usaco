/*
ID: stapark1
LANG: C++14
TASK: money
*/

#include <fstream>
#include <vector>

int main() {
  std::ifstream input("money.in");
  std::ofstream output("money.out");

  int numTypes, totalValue;
  input >> numTypes >> totalValue;

  std::vector<int> coinTypes = {0};
  for (std::size_t type = 0; type < numTypes; ++type) {
    int coinType;
    input >> coinType;
    coinTypes.emplace_back(coinType);
  }

  // Element [i][j] is the number of ways to achieve a sum of j using the first
  // i coin types.
  std::vector<std::vector<long long>> solutions;
  solutions.emplace_back(std::vector<long long> {1});
  solutions.back().resize(totalValue + 1);

  for (std::size_t i = 1; i <= numTypes; ++i) {
    solutions.emplace_back(std::vector<long long> {1});
    for (int j = 1; j <= totalValue; ++j) {
      long long useNone = solutions[i - 1][j];
      long long useSome = (j >= coinTypes[i]) ?
          solutions[i][j - coinTypes[i]] : 0;
      solutions.back().emplace_back(useNone + useSome);
    }
  }

  output << solutions[numTypes][totalValue] << std::endl;
  return 0;
}