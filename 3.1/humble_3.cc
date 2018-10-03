/*
ID: stapark1
LANG: C++14
TASK: humble
*/

#include <algorithm>
#include <fstream>
#include <limits>
#include <vector>

std::ifstream input("humble.in");
std::ofstream output("humble.out");

int main() {
  int numPrimes, finalIndex;
  input >> numPrimes >> finalIndex;

  std::vector<uint32_t> primes;
  for (int i = 0; i < numPrimes; ++i) {
    uint32_t prime;
    input >> prime;
    primes.emplace_back(prime);
  }

  std::vector<uint64_t> humbles = {1};
  std::vector<uint32_t> minHumbleIndex(numPrimes, 0);

  for (int i = 0; i < finalIndex; ++i) {
    uint64_t minHumble = std::numeric_limits<long long>::max();
    for (int p = 0; p < numPrimes; ++p) {
      while (primes[p] * humbles[minHumbleIndex[p]] <= humbles.back())
        minHumbleIndex[p]++;
      minHumble = std::min(minHumble, primes[p] * humbles[minHumbleIndex[p]]);
    }
    humbles.emplace_back(minHumble);
  }

  output << humbles.back() << std::endl;
  return 0;
}