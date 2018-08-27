/*
ID: stapark1
LANG: C++14
TASK: sprime
*/

#include <array>
#include <cmath>
#include <fstream>
#include <vector>

bool prime(int number, std::vector<int>& primes) {
  for (const int prime : primes) {
    if (prime > std::sqrt(number)) return true;
    if (number % prime == 0) return false;
  }
  return true;
}

int power10(int exponent) {
  int result = 1;
  while (exponent > 0) {
    result *= 10;
    exponent--;
  }
  return result;
}

std::array<int, 4> first_digits = {2, 3, 5, 7};
std::array<int, 4> other_digits = {1, 3, 7, 9};

void print_primes(int seed, int missing_length, std::vector<int>& primes, std::ofstream& output) {
  int number;
  if (missing_length == 0) {
    output << seed << std::endl;
  } else {
    for (std::size_t i = 0; i < other_digits.size(); ++i) {
      number = (seed * 10) + other_digits[i];
      if (prime(number, primes)) {
        print_primes(number, missing_length - 1, primes, output);
      }
    }
  }
}

int main() {
  std::ifstream input("sprime.in");
  std::ofstream output("sprime.out");

  int length;
  input >> length;

  std::vector<int> primes = {2};
  for (int i = 3; i < std::sqrt(power10(length)); ++i) {
    if (prime(i, primes)) primes.push_back(i);
  }

  for (std::size_t i = 0; i < first_digits.size(); ++i) {
    print_primes(first_digits[i], length - 1, primes, output);
  }
  return 0;
}