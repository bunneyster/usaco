/*
ID: stapark1
LANG: C++14
TASK: numtri
*/

#include <algorithm>
#include <fstream>
#include <vector>

int main() {
  std::ifstream input("numtri.in");
  std::ofstream output("numtri.out");

  int num_rows;
  input >> num_rows;

  std::vector<std::vector<int>> tree;
  int number;
  for (int row = 0; row < num_rows; ++row) {
    tree.push_back(std::vector<int>{});
    for (int col = 0; col < row + 1; ++col) {
      input >> number;
      tree[row].push_back(number);
    }
  }

  for (int row = num_rows - 2; row >= 0; --row) {
    for (int col = 0; col < row + 1; ++col) {
      tree[row][col] += std::max(tree[row + 1][col], tree[row + 1][col + 1]);
    }
  }

  output << tree[0][0] << std::endl;

  return 0;
}