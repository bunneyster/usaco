/*
ID: stapark1
LANG: C++14
TASK: range
*/

#include <fstream>
#include <vector>

std::ifstream input("range.in");
std::ofstream output("range.out");

int main() {
  int dim;
  input >> dim;

  std::vector<std::vector<bool>> field;
  for (int i = 0; i < dim; ++i) {
    field.emplace_back(std::vector<bool> {});
    std::string row;
    input >> row;
    for (const char col : row) {
      field[i].emplace_back(col == '1');
    }
  }

  std::vector<int> frequencies(dim + 1, 0);
  for (int size = 2; size <= dim; ++size) {
    for (int i = 0; i < dim - size + 1; ++i) {
      for (int j = 0; j < dim - size + 1; ++j) {
        if (field[i][j] && field[i][j + 1] && field[i + 1][j + 1] && field[i + 1][j]) {
          frequencies[size]++;
        } else {
          field[i][j] = false;
        }
      }
    }
  }

  for (int i = 0; i < frequencies.size(); ++i) {
    if (frequencies[i])
      output << i << ' ' << frequencies[i] << std::endl;
  }

  return 0;
}