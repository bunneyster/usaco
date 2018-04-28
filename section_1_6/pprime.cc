/*
ID: stapark1
LANG: C++14
TASK: pprime
*/

#include <cmath>
#include <fstream>
#include <vector>

int ten_power(int exponent) {
  if (exponent == 0) return 1;
  if (exponent == 1) return 10;
  return 10 * ten_power(exponent - 1);
}

int digit_count(int x) {
  int num_digits = 9;  // Max number of digits.
  while (x / ten_power(num_digits - 1) < 1) --num_digits;
  return num_digits;
}

int reverse(int number) {
  int result = 0;
  for (int position = 0; number / ten_power(position) > 0; ++position) {
    result = result * 10 + number / ten_power(position) % 10;
  }
  return result;
}

// All palindromes of length l.
std::vector<int> palindromes_of_length(int l) {
  std::vector<int> palindromes;
  for (int seed = ten_power((l - 1) / 2); seed < ten_power(((l - 1) / 2) + 1); ++seed) {
    palindromes.push_back(seed * ten_power(l / 2) + reverse(seed / ten_power(l % 2)));
  }
  return palindromes;
}

bool is_divisible(int dividend, int divisor) {
  float quotient = dividend / divisor;
  return quotient * divisor == dividend;
}

bool is_prime(int dividend, std::vector<int>& primes) {
  int sqrt = std::sqrt(dividend);
  for (const int divisor : primes) {
    if (divisor > sqrt) return true;
    if (is_divisible(dividend, divisor)) return false;
  }
  return true;
}

int main() {
  std::ifstream input("pprime.in");
  std::ofstream output("pprime.out");

  int min, max;
  input >> min >> max;

  std::vector<int> primes = {2};
  // Calculate prime numbers needed to verify primeness within given range.
  for (int number = 3; number <= std::sqrt(max); number += 2) {
    if (is_prime(number, primes)) {
      primes.push_back(number);
    }
  }

  // Generate palindromes within the given range.
  std::vector<int> palindromes;
  int min_digits = digit_count(min);
  int max_digits = digit_count(max);
  for (int d = min_digits; d <= max_digits; ++d) {
    palindromes = palindromes_of_length(d);
    for (const auto p : palindromes) {
      if (p < min || p > max) continue;
      if (is_prime(p, primes)) {
        output << p << std::endl;
      }
    }
  }

  return 0;
}