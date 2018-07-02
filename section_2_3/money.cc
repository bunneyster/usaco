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
  int coinType;
  while (input >> coinType)
    coinTypes.emplace_back(coinType);

  // Element [i][j] is the number of ways to achieve a sum of j using the first
  // i coin types.
  std::vector<std::vector<long long>> solutions;
  solutions.emplace_back(totalValue + 1, 0);
  solutions[0][0] = 1;

  for (int i = 1; i <= numTypes; ++i) {
    solutions.emplace_back(totalValue + 1, 0);
    solutions[i][0] = 1;
    for (int j = 1; j <= totalValue; ++j) {
      solutions[i][j] = solutions[i - 1][j];
      if (j >= coinTypes[i])
          solutions[i][j] += solutions[i][j - coinTypes[i]];
    }
  }

  output << solutions[numTypes][totalValue] << std::endl;
  return 0;
}