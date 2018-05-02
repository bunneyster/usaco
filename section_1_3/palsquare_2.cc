/*
ID: stapark1
LANG: C++11
TASK: palsquare
*/

#include <fstream>

std::string convert_base(int number, int base) {
  std::string remainder;
  if (number % base < 10) {
    remainder = '0' + (number % base);
  } else {
    remainder = 'A' + (number % base) - 10;
  }

  int quotient = number / base;
  if (quotient == 0) {
    return remainder;
  } else {
    return convert_base(quotient, base) + remainder;
  }
}

bool palindromic(std::string number) {
  for (int i = 0; i < number.size(); ++i) {
    if (number[i] != number[number.size() - 1 - i]) return false;
  }
  return true;
}

int main() {
  std::ifstream input("palsquare.in");
  std::ofstream output("palsquare.out");

  int base;
  input >> base;

  std::string square;
  for (int i = 1; i <= 300; ++i) {
    square = convert_base(i * i, base);
    if (palindromic(square)) {
      output << convert_base(i, base) << ' ' << square << std::endl;
    }
  }
  return 0;
}
