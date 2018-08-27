/*
ID: stapark1
LANG: C++14
TASK: fact4
*/

#include <fstream>

std::ifstream input("fact4.in");
std::ofstream output("fact4.out");

int main() {
  int base;
  input >> base;

  int truncProduct = 1;
  for (int i = 2; i <= base; ++i) {
    int product = truncProduct * i;
    while (product % 10 == 0) {
      product /= 10;
    }
    truncProduct = product % 1000;
  }

  output << truncProduct % 10 << std::endl;
  return 0;
}