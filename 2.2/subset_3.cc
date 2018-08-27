/*
ID: stapark1
LANG: C++14
TASK: subset
*/

#include <fstream>
#include <iostream>
#include <vector>

std::ifstream input("subset.in");
std::ofstream output("subset.out");

int main() {
  int lastNumber;
  input >> lastNumber;

  int totalSum = 0;
  for (int i = 1; i <= lastNumber; ++i) {
    totalSum += i;
  }

  if (totalSum % 2 != 0) {
    output << 0 << std::endl;
    return 0;
  }

  int partitionSum = totalSum / 2;

  std::vector<unsigned long long> dp(partitionSum + 1, 0);
  dp[0] = 1;
  for (int subsetEnd = 1; subsetEnd <= lastNumber; ++subsetEnd) {
    for (int sum = partitionSum; sum >= subsetEnd; --sum) {
      dp[sum] += dp[sum - subsetEnd];
    }
  }

  output << (int)(dp[partitionSum] / 2) << std::endl;
  return 0;
}