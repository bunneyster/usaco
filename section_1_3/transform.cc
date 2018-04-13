/*
ID: stapark1
LANG: C++11
TASK: transform
*/

#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

typedef std::vector<std::vector<char>> square_t;

square_t read_square(int dimension, std::ifstream& input) {
  square_t result;
  std::string row;
  for (int i = 0; i < dimension; ++i) {
    input >> row;
    result.push_back(std::vector<char>());
    for (int j = 0; j < dimension; ++j) {
      result[i].push_back(row[j]);
    }
  }
  return result;
}

square_t rotated(const square_t& original) {
  square_t result = original;
  int dimension = original.size();
  for (int i = 0; i < dimension; ++i) {
    for (int j = 0; j < dimension; ++j) {
      result[j][dimension - 1 - i] = original[i][j];
    }
  }
  return result;
}

square_t mirrored(const square_t& original) {
  square_t result = original;
  int dimension = original.size();
  for (int i = 0; i < dimension; ++i) {
    for (int j = 0; j < dimension; ++j) {
      result[i][dimension - 1 - j] = original[i][j];
    }
  }
  return result;
}

int main() {
  std::ifstream input("transform.in");
  std::ofstream output("transform.out");

  int dimension;
  input >> dimension;

  square_t square_original = read_square(dimension, input);
  square_t square_final = read_square(dimension, input);
  square_t square_transformed = square_original;

  for (int rotation_count = 1; rotation_count < 4; ++rotation_count) {
    square_transformed = rotated(square_transformed);
    if (square_transformed == square_final) {
      output << rotation_count << std::endl;
      return 0;
    }
  }
  square_transformed = mirrored(square_original);
  if (square_transformed == square_final) {
    output << 4 << std::endl;
    return 0;
  }
  for (int rotation_count = 1; rotation_count < 4; ++rotation_count) {
    square_transformed = rotated(square_transformed);
    if (square_transformed == square_final) {
      output << 5 << std::endl;
      return 0;
    }
  }
  if (square_final == square_original) {
    output << 6 << std::endl;
    return 0;
  }
  output << 7 << std::endl;

  return 0;
}