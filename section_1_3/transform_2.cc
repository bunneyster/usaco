/*
ID: stapark1
LANG: C++11
TASK: transform
*/

#include <fstream>
#include <vector>

std::vector<std::vector<char>> rotate(const std::vector<std::vector<char>>& original) {
  std::vector<std::vector<char>> result = original;
  int dimension = original.size();
  for (int row = 0; row < dimension; ++row) {
    for (int col = 0; col < dimension; ++col) {
      result[col][dimension - 1 - row] = original[row][col];
    }
  }
  return result;
}

std::vector<std::vector<char>> reflect(const std::vector<std::vector<char>>& original) {
  std::vector<std::vector<char>> result = original;
  int dimension = original.size();
  for (int row = 0; row < dimension; ++row) {
    for (int col = 0; col < dimension; ++col) {
      result[row][dimension - 1 - col] = original[row][col];
    }
  }
  return result;
}

int main() {
  std::ifstream input("transform.in");
  std::ofstream output("transform.out");

  int N;
  input >> N;

  std::vector<std::vector<char>> initial;
  std::vector<std::vector<char>> transformed;
  std::string row;
  for (int i = 0; i < N; ++i) {
    initial.push_back(std::vector<char>{});
    input >> row;
    for (int j = 0; j < N; ++j) {
      initial[i].push_back(row[j]);
    }
  }
  for (int i = 0; i < N; ++i) {
    transformed.push_back(std::vector<char>{});
    input >> row;
    for (int j = 0; j < N; ++j) {
      transformed[i].push_back(row[j]);
    }
  }

  auto intermediate = initial;
  for (int i = 1; i < 4; ++i) {
    intermediate = rotate(intermediate);

    if (intermediate == transformed) {
      output << i << std::endl;
      return 0;
    }
  }

  intermediate = reflect(initial);
  if (intermediate == transformed) {
    output << 4 << std::endl;
    return 0;
  }
  for (int i = 1; i < 4; ++i) {
    intermediate = rotate(intermediate);
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