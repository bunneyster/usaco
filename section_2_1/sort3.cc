/*
ID: stapark1
LANG: C++14
TASK: sort3
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <vector>

int main() {
  std::ifstream input("sort3.in");
  std::ofstream output("sort3.out");

  int numRecords;
  input >> numRecords;

  std::array<int, 4> bucketSizes = {0, 0, 0, 0};  // First bucket is padding
  std::vector<int> records;
  for (int i = 0; i < numRecords; ++i) {
    int record;
    input >> record;
    bucketSizes[record]++;
    records.push_back(record);
  }

  // Frequency of record r (1..3) in bucket b is at position [b][r].
  std::array<std::array<int, 4>, 4> frequencies{};  // First row/column is padding
  int record = 0;
  for (std::size_t bucket = 1; bucket < bucketSizes.size(); ++bucket) {
    for (std::size_t item = 0; item < bucketSizes[bucket]; ++item, ++record) {
      frequencies[bucket][records[record]]++;
    }
  }

  const int k12MaxCount = std::max(frequencies[1][2], frequencies[2][1]);
  const int k12SwapCount = std::min(frequencies[1][2], frequencies[2][1]);
  const int k13SwapCount = std::min(frequencies[1][3], frequencies[3][1]);
  const int k23SwapCount = std::min(frequencies[2][3], frequencies[3][2]);
  const int kCyclicSwapCount = 2 * (k12MaxCount - k12SwapCount);

  int numSwaps = k12SwapCount + k13SwapCount + k23SwapCount + kCyclicSwapCount;
  output << numSwaps << std::endl;
  return 0;
}
