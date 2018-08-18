/*
ID: stapark1
LANG: C++14
TASK: nocows
*/

#include <fstream>
#include <unordered_map>
#include <vector>

// # nodes => # trees with height index i
std::unordered_map<int, std::vector<int>> numTrees;
// # nodes => # trees with height at most index i
std::unordered_map<int, std::vector<int>> numTreesPerMaxHeight;

int main() {
  std::ifstream input("nocows.in");
  std::ofstream output("nocows.out");

  int finalNumNodes, finalHeight;
  input >> finalNumNodes >> finalHeight;

  if (finalNumNodes % 2 == 0) {
    output << 0 << std::endl;
    return 0;
  }

  for (int n = 1; n <= finalNumNodes; n += 2) {
    numTrees[n] = std::vector<int>(finalHeight + 1, 0);
    numTreesPerMaxHeight[n] = std::vector<int>(finalHeight + 1, 0);
  }
  // 1 tree with 1 node of height 1.
  numTrees[1][1] = 1;
  numTreesPerMaxHeight[1][1] = 1;

  // Compute tree counts by increasing node counts, then by increasing height.
  for (int n = 1; n <= finalNumNodes; n += 2) {
    for (int h = 2; h <= finalHeight; ++h) {
      int count = 0;
      for (int leftTree = n - 2; leftTree > 0; leftTree -= 2) {
        int rightTree = n - 1 - leftTree;
        // height of left tree fixed/greater
        count += numTrees[leftTree][h - 1] * numTreesPerMaxHeight[rightTree][h - 2];
        // height of right tree fixed/greater
        count += numTrees[rightTree][h - 1] * numTreesPerMaxHeight[leftTree][h - 2];
        // height of left tree equals height of right tree
        count += numTrees[leftTree][h - 1] * numTrees[rightTree][h - 1];
        count %= 9901;
      }
      numTrees[n][h] = count;
      numTreesPerMaxHeight[n][h] = (numTreesPerMaxHeight[n][h - 1] + count) % 9901;
    }
  }

  output << numTrees[finalNumNodes][finalHeight] << std::endl;

  return 0;
}