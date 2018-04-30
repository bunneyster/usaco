/*
ID: stapark1
LANG: C++14
TASK: sprime
*/

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

const std::vector<int> last_digits = {1, 3, 5, 7, 9};

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

void enumerate(int prime, int length, int max_length, std::vector<int>& primes, std::ofstream& output) {
  int next_prime;
  for (const auto digit : last_digits) {
    next_prime = prime * 10 + digit;
    if (is_prime(next_prime, primes)) {
      if (length + 1 == max_length) {
        output << next_prime << std::endl;
      } else {
        enumerate(next_prime, length + 1, max_length, primes, output);
      }
    }
  }
}

int main() {
  std::ifstream input("sprime.in");
  std::ofstream output("sprime.out");

  int LENGTH;
  input >> LENGTH;

  std::vector<int> primes = {2};
  // Calculate prime numbers needed to verify primeness up to 8 digits.
  for (int number = 3; number <= std::sqrt(99999999); number += 2) {
    if (is_prime(number, primes)) {
      primes.push_back(number);
    }
  }

  std::vector<int> first_digits = {2, 3, 5, 7};
  for (const auto p : first_digits) {
    enumerate(p, 1, LENGTH, primes, output);
  }
  return 0;
}
