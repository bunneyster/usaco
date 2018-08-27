/*
ID: stapark1
LANG: C++11
TASK: dualpal
*/

#include <fstream>
#include <vector>

// Copied directly from palsquare.cc.
bool is_palindrome(std::vector<int>& digits) {
  for (std::size_t i = 0; i < digits.size(); ++i) {
    if (digits[i] != digits[digits.size() - 1 - i]) return false;
  }
  return true;
}

// Copied directly from palsquare.cc.
void convert_base(int num, int base, std::vector<int>& reversed_result) {
  if (num < base) {
    reversed_result.push_back(num);
    return;
  } else {
    reversed_result.push_back(num % base);
    convert_base(num / base, base, reversed_result);
  }
}

bool is_palindrome(int num, int base) {
  std::vector<int> reversed_result;
  convert_base(num, base, reversed_result);
  return is_palindrome(reversed_result);
}

bool has_2_palindromes(int num) {
  int palindrome_count = 0;
  for (int base = 2; base < 11; ++base) {
    if (is_palindrome(num, base)) {
      palindrome_count++;
      if (palindrome_count == 2) return true;
    }
  }
  return false;
}

int main() {
  std::ifstream input("dualpal.in");
  std::ofstream output("dualpal.out");

  int quota, lower_bound;
  input >> quota >> lower_bound;

  std::vector<int> results;
  int result_count;
  for (int i = lower_bound + 1; result_count < quota; ++i) {
    if (has_2_palindromes(i)) {
      output << i << std::endl;
      result_count++;
    }
  }

  return 0;
}