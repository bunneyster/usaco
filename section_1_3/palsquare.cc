/*
ID: stapark1
LANG: C++11
TASK: palsquare
*/

#include <cmath>
#include <fstream>
#include <vector>

bool is_palindrome(std::vector<int>& digits) {
  for (std::size_t i = 0; i < digits.size(); ++i) {
    if (digits[i] != digits[digits.size() - 1 - i]) return false;
  }
  return true;
}

void convert_base(int num, int base, std::vector<int>& reversed_result) {
  if (num < base) {
    reversed_result.push_back(num);
    return;
  } else {
    reversed_result.push_back(num % base);
    convert_base(num / base, base, reversed_result);
  }
}

std::string readable_num(std::vector<int>& reversed_digits) {
  std::string result;
  for (auto it = reversed_digits.rbegin(); it != reversed_digits.rend(); ++it) {
    if (*it > 9) {
      result += (*it - 10 + 'A');
    } else {
      result += (*it + '0');
    }
  }
  return result;
}

int main() {
  std::ifstream input("palsquare.in");
  std::ofstream output("palsquare.out");

  int base;
  input >> base;

  for (int i = 1; i <= 300; ++i) {
    std::vector<int> square;
    convert_base(std::pow(i, 2), base, square);
    if (is_palindrome(square)) {
      std::vector<int> square_root;
      convert_base(i, base, square_root);
      output << readable_num(square_root) << ' ';
      output << readable_num(square) << std::endl;
    }
  }

  return 0;
}