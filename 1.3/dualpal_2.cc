/*
ID: stapark1
LANG: C++11
TASK: dualpal
*/

#include <fstream>
#include <vector>

std::vector<int> convert_base(int number, int base) {
  std::vector<int> result;
  int quotient = number / base;

  result.push_back(number % base);
  if (quotient != 0) {
    for (const int digit : convert_base(quotient, base)) {
      result.push_back(digit);
    }
  }
  return result;
}

bool is_pal(const std::vector<int>& number) {
  int size = number.size();
  for (std::size_t i = 0; i < size / 2; ++i) {
    if (number[i] != number[size - 1 - i]) return false;
  }
  return true;
}

bool is_dualpal(int number) {
  bool found_pal = false;
  std::vector<int> converted_number;
  for (int base = 2; base <= 10; ++base) {
    converted_number = convert_base(number, base);
    if (is_pal(converted_number)) {
      if (found_pal) return true;
      found_pal = true;
    }
  }
  return false;
}

int main() {
  std::ifstream input("dualpal.in");
  std::ofstream output("dualpal.out");

  int num_pals, lower_bound;
  input >> num_pals >> lower_bound;

  int dualpal_count = 0;
  for (int i = lower_bound + 1; dualpal_count < num_pals; ++i) {
    if (is_dualpal(i)) {
      dualpal_count++;
      output << i << std::endl;
    }
  }
  return 0;
}