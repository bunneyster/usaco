/*
ID: stapark1
LANG: C++14
TASK: pprime
*/

#include <algorithm>
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

std::vector<int> GetPrimesUpTo(int max) {
  std::vector<int> primes = {2, 3};
  for (int number = primes.back() + 1; number <= max; ++number) {
    if (IsPrime(number, primes)) primes.push_back(number);
  }
  return primes;
}

int PowerOfTen(int power) {
  int result = 1;
  while (power > 0) {
    result *= 10;
    power--;
  }
  return result;
}

int LengthOf(int number) {
  int result = 1;
  while (number / 10 > 0) {
    result++;
    number /= 10;
  }
  return result;
}

std::vector<int> PalindromesOfLength(int length) {
  std::vector<int> result;
  int kSeedPower = (length - 1) / 2;
  for (int seed = PowerOfTen(kSeedPower); seed < PowerOfTen(kSeedPower + 1); ++seed) {
    std::string palindrome = std::to_string(seed);
    for (int digit = length / 2 - 1; digit >= 0; --digit) {
      palindrome.push_back(palindrome.at(digit));
    }
    result.emplace_back(std::stoi(palindrome));
  }
  return result;
}

int main() {
  std::ifstream input("pprime.in");
  std::ofstream output("pprime.out");

  int min, max;
  input >> min >> max;

  std::vector<int> primes = GetPrimesUpTo(std::sqrt(max));

  for (int length = LengthOf(min); length <= LengthOf(max); ++length) {
    for (int palindrome : PalindromesOfLength(length)) {
      if (palindrome < min || palindrome > max) continue;
      if (IsPrime(palindrome, primes)) {
        output << palindrome << std::endl;
      }
    }
  }

  return 0;
}