/*
ID: stapark1
LANG: C++14
TASK: subset
*/

#include <fstream>
#include <vector>

// The i-th element is the number of subsets whose sum is i.
std::vector<double> numSubsetsPerSum;
std::vector<double> numSubsetsPerSumCopy;

int main() {
  std::ifstream input("subset.in");
  std::ofstream output("subset.out");

  int kSize;
  input >> kSize;
  numSubsetsPerSum.push_back(1);
  int maxSum = 0;
  for (int i = 1; i <= kSize; ++i) maxSum += i;

  if (maxSum % 2 != 0) {
    output << 0 << std::endl;
    return 0;
  }

  numSubsetsPerSum.resize(maxSum + 1);
  numSubsetsPerSumCopy = numSubsetsPerSum;

  int firstBlankSum = 1;
  for (int size = 1; size <= kSize; ++size) {
    int sum = size;
    while (sum < firstBlankSum + size) {
      numSubsetsPerSum[sum] += numSubsetsPerSumCopy[sum - size];
      sum++;
    }
    firstBlankSum = sum;
    numSubsetsPerSumCopy = numSubsetsPerSum;
  }

  const int kEqualSum = maxSum / 2;
  const int kResult = numSubsetsPerSum[kEqualSum] / 2;
  output << kResult << std::endl;
  return 0;
}