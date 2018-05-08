/*
ID: stapark1
LANG: C++14
TASK: transform
*/

#include <algorithm>
#include <fstream>
#include <vector>

std::vector<std::vector<char>> Rotate(const std::vector<std::vector<char>>& original) {
  std::vector<std::vector<char>> result = original;
  int dimension = original.size();
  for (int row = 0; row < dimension; ++row) {
    for (int col = 0; col < dimension; ++col) {
      result[col][dimension - 1 - row] = original[row][col];
    }
  }
  return result;
}

std::vector<std::vector<char>> Reflect(const std::vector<std::vector<char>>& original) {
  std::vector<std::vector<char>> result = original;
  int dimension = original.size();
  for (int row = 0; row < dimension; ++row) {
    std::reverse(result[row].begin(), result[row].end());
  }
  return result;
}

std::vector<std::vector<char>> ReadMatrix(int size, std::ifstream& input) {
  std::vector<std::vector<char>> result;
  std::string row;
  for (int i = 0; i < size; ++i) {
    input >> row;
    result.emplace_back(std::vector<char>(row.cbegin(), row.cend()));
  }
  return result;
}

int main() {
  std::ifstream input("transform.in");
  std::ofstream output("transform.out");

  int N;
  input >> N;

  std::vector<std::vector<char>> initial = ReadMatrix(N, input);
  std::vector<std::vector<char>> transformed = ReadMatrix(N, input);

  auto intermediate = initial;
  for (int i = 1; i < 4; ++i) {
    intermediate = Rotate(intermediate);

    if (intermediate == transformed) {
      output << i << std::endl;
      return 0;
    }
  }

  intermediate = Reflect(initial);
  if (intermediate == transformed) {
    output << 4 << std::endl;
    return 0;
  }
  for (int i = 1; i < 4; ++i) {
    intermediate = Rotate(intermediate);
    if (intermediate == transformed) {
      output << 5 << std::endl;
      return 0;
    }
  }

  if (initial == transformed) {
    output << 6 << std::endl;
    return 0;
  }

  output << 7 << std::endl;

  return 0;
}