/*
ID: stapark1
LANG: C++14
TASK: humble
*/

#include <fstream>
#include <limits>
#include <set>
#include <vector>

int main() {
  std::ifstream input("humble.in");
  std::ofstream output("humble.out");

  int setSize, N;
  input >> setSize >> N;

  std::vector<int> primes;
  int prime;
  for (int i = 0; i < setSize; ++i) {
    input >> prime;
    primes.emplace_back(prime);
  }

  int32_t kthHumbleNumber;
  std::set<int32_t> queue {1};

  for (int k = 0; k < N; ++k) {
    kthHumbleNumber = *queue.begin();

    for (int prime = 0; prime < setSize; ++prime) {
      uint64_t adjNumber = (uint64_t)kthHumbleNumber * primes[prime];
      if (adjNumber > std::numeric_limits<int32_t>::max()) continue;
      if (queue.size() > N - k + 1) {
        if (adjNumber < *std::prev(queue.end())) {
          auto it = queue.insert(adjNumber);
          if (it.second)
            queue.erase(std::prev(queue.end()));
        }
      } else {
        queue.insert(adjNumber);
      }
    }
    queue.erase(queue.begin());
  }

  output << *queue.begin() << std::endl;

  return 0;
}