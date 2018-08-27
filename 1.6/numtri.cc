/*
ID: stapark1
LANG: C++14
TASK: numtri
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <vector>

const int MAX_ROWS = 1000;

int main() {
  std::ifstream input("numtri.in");
  std::ofstream output("numtri.out");

  int total_rows;
  input >> total_rows;

  std::vector<std::array<int, MAX_ROWS>> numbers;
  int number;
  for (int row = 0; row < total_rows; ++row) {
    numbers.push_back(std::array<int, MAX_ROWS>{});
    for (int col = 0; col < row + 1; ++col) {
      input >> number;
      numbers[row][col] = number;
    }
  }

  for (int row = total_rows - 2; row >= 0; --row) {
    for (int col = 0; col < total_rows; ++col) {
      numbers[row][col] += std::max(numbers[row + 1][col], numbers[row + 1][col + 1]);
    }
  }
  output << numbers[0][0] << std::endl;

  return 0;
}