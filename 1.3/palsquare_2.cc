/*
ID: stapark1
LANG: C++11
TASK: palsquare
*/

#include <algorithm>
#include <fstream>

std::string convert_base(int number, int base) {
  const char kDigits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  std::string result;
  while (number != 0) {
    result.push_back(kDigits[number % base]);
    number /= base;
  }
  std::reverse(result.begin(), result.end());
  return result;
}

bool IsPalindrome(const std::string& input) {
  for (int i = 0; i < input.size(); ++i) {
    if (input[i] != input[input.size() - 1 - i]) return false;
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
    if (IsPalindrome(square)) {
      output << convert_base(i, base) << ' ' << square << std::endl;
    }
  }
  return 0;
}
