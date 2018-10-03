/*
ID: stapark1
LANG: C++14
TASK: humble
*/

#include <algorithm>
#include <fstream>
#include <set>
#include <vector>

std::ifstream input("humble.in");
std::ofstream output("humble.out");

int main() {
  int setSize;
  uint32_t finalIndex;
  input >> setSize >> finalIndex;

  std::vector<uint32_t> primes;
  std::set<uint64_t> numbers;
  for (int i = 0; i < setSize; ++i) {
    uint32_t prime;
    input >> prime;
    primes.emplace_back(prime);
    numbers.insert(prime);
  }

  std::sort(primes.begin(), primes.end());

  for (uint32_t i = 0; i < finalIndex - 1; ++i) {
    uint64_t ithHumbleNumber = *numbers.begin();
    for (uint32_t prime : primes) {
      // Stop inserting if greatest possible value has been seen.
      if (numbers.size() >= finalIndex - i && ithHumbleNumber * prime > *std::prev(numbers.end())) break;
      numbers.insert(ithHumbleNumber * prime);
    }
    numbers.erase(numbers.begin());
  }

  output << *numbers.begin() << std::endl;
  return 0;
}