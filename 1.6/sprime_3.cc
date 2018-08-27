/*
ID: stapark1
LANG: C++14
TASK: sprime
*/

#include <array>
#include <cmath>
#include <fstream>
#include <vector>

bool IsPrime(int number, std::vector<int>& primes) {
  for (int prime : primes) {
    if (prime > std::sqrt(number)) return true;
    if (number % prime == 0) return false;
  }
  return true;
}

std::vector<int> PrimesUpTo(int max) {
  std::vector<int> primes = {2};
  for (int number = primes.back() + 1; number < max; ++number) {
    if (IsPrime(number, primes)) primes.push_back(number);
  }
  return primes;
}

void DerivedPrimes(int basePrime, int missingLength, std::vector<int>& primes, std::ofstream& output) {
  if (missingLength == 0) {
    output << basePrime << std::endl;
  } else {
    const std::array<int, 4> kValidDigits = {1, 3, 7, 9};
    for (int digit : kValidDigits) {
      int nextNumber = basePrime * 10 + digit;
      if(IsPrime(nextNumber, primes)) {
        DerivedPrimes(nextNumber, missingLength - 1, primes, output);
      }
    }
  }
}

int PowerOfTen(int power) {
  int result = 1;
  while (power > 0) {
    result *= 10;
    power--;
  }
  return result;
}

int main() {
  std::ifstream input("sprime.in");
  std::ofstream output("sprime.out");

  int length;
  input >> length;

  std::vector<int> primes = PrimesUpTo(std::sqrt(PowerOfTen(length)));

  const std::array<int, 4> kFirstDigits = {2, 3, 5, 7};
  for (int digit : kFirstDigits) {
    DerivedPrimes(digit, length - 1, primes, output);
  }

  return 0;
}