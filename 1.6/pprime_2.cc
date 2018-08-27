/*
ID: stapark1
LANG: C++14
TASK: pprime
*/

#include <cmath>
#include <fstream>
#include <vector>

bool prime(int num, std::vector<int>& primes) {
  for (const auto prime : primes) {
    if (prime == num) return true;
    if (num % prime == 0) return false;
  }
  return true;
}

std::vector<int> primes_upto(int max) {
  std::vector<int> primes = {2};
  for (int num = 3; num <= max; num += 2) {
    if (prime(num, primes)) primes.push_back(num);
  }
  return primes;
}

int power10(int exponent) {
  int result = 1;
  while (exponent > 0) {
    result *= 10;
    exponent--;
  }
  return result;
}

int digits_in(int number) {
  int count = 1;
  while (number / 10 >= 1) {
    number /= 10;
    count++;
  }
  return count;
}

// Order digits from right to left.
int digit_at(int number, int digit) {
  for (int i = 0; i < digit; ++i) {
    number /= 10;
  }
  return number % 10;
}

std::vector<int> palindromes_of_length(int length) {
  std::vector<int> result;
  const int mid_digit = (length + 1) / 2;
  int palindrome;
  for (int seed = power10(mid_digit - 1); seed < power10(mid_digit); ++seed) {
    palindrome = seed * power10(length / 2);
    for (int digit = 0; digit < length / 2; ++digit) {
      palindrome += digit_at(seed, mid_digit - 1 - digit) * power10(digit);
    }
    result.push_back(palindrome);
  }
  return result;
}

int main() {
  std::ifstream input("pprime.in");
  std::ofstream output("pprime.out");

  int min, max;
  input >> min >> max;

  std::vector<int> primes = primes_upto(std::sqrt(max));

  std::vector<int> palindromes;
  for (int length = digits_in(min); length <= digits_in(max); ++length) {
    palindromes = palindromes_of_length(length);
    for (const int palindrome : palindromes) {
      if (palindrome < min || palindrome > max) continue;
      if (prime(palindrome, primes)) {
        output << palindrome << std::endl;
      }
    }
  }

  return 0;
}