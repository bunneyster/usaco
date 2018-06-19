/*
ID: stapark1
LANG: C++14
TASK: nocows
*/

#include <fstream>
#include <vector>

// Element [h][c] is the number of pedigrees of height h and c nodes.
std::vector<std::vector<int>> variantCounts;
// Element [h][c] is the number of pedigrees of at most height h and c nodes.
std::vector<std::vector<int>> cumulativeCounts;

int main() {
  std::ifstream input("nocows.in");
  std::ofstream output("nocows.out");

  int numCows, treeHeight;
  input >> numCows >> treeHeight;

  if (numCows % 2 == 0) {
    output << 0 << std::endl;
    return 0;
  }

  // First empty row for height = 0.
  variantCounts.emplace_back(std::vector<int> {});
  variantCounts.back().resize(numCows + 1);
  cumulativeCounts.emplace_back(std::vector<int> {});
  cumulativeCounts.back().resize(numCows + 1);
  // Initialize values for height = 1;
  variantCounts.emplace_back(std::vector<int> {0, 1});  // 1 pedigree of size and height 1
  variantCounts.back().resize(numCows + 1);
  cumulativeCounts.emplace_back(std::vector<int> {0, 1});
  cumulativeCounts.back().resize(numCows + 1);
  for (int height = 2; height <= treeHeight; ++height) {
    variantCounts.emplace_back(std::vector<int> {0});
    cumulativeCounts.emplace_back(cumulativeCounts[height - 1]);
    for (int cows = 1; cows <= numCows; ++cows) {
      int count = 0;

      for (int lhc = 1; lhc < cows; lhc += 2) {
        int rhc = cows - 1 - lhc;

        int lhs = variantCounts[height - 1][lhc];
        int rhs = cumulativeCounts[height - 2][rhc];
        count += (lhs * rhs) % 9901;

        lhs = cumulativeCounts[height - 2][lhc];
        rhs = variantCounts[height - 1][rhc];
        count += (lhs * rhs) % 9901;

        lhs = variantCounts[height - 1][lhc];
        rhs = variantCounts[height - 1][rhc];
        count += (lhs * rhs) % 9901;
      }

      count %= 9901;
      variantCounts[height].emplace_back(count);
      cumulativeCounts[height][cows] += count;
    }
  }

  output << variantCounts[treeHeight][numCows] << std::endl;
  return 0;
}