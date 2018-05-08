/*
ID: stapark1
LANG: C++14
TASK: ariprog
*/

#include <array>
#include <fstream>
#include <vector>

int main() {
  std::ifstream input("ariprog.in");
  std::ofstream output("ariprog.out");

  int ariprog_length, max_pq;
  input >> ariprog_length >> max_pq;

  std::array<bool, 250 * 250 * 2 + 1> bisquare_lookup{};
  for (int p = 0; p <= max_pq; ++p) {
    for (int q = 0; q <= max_pq; ++q) {
      bisquare_lookup[(p * p) + (q * q)] = true;
    }
  }

  std::vector<int> bisquares;
  for (int i = 0; i < max_pq * max_pq * 2 + 1; ++i) {
    if (bisquare_lookup[i]) bisquares.push_back(i);
  }

  bool found_result = false;
  for (int b = 1; (ariprog_length - 1) * b <= 2 * max_pq * max_pq; ++b) {
    for (int bisquare = 0; bisquare < bisquares.size(); ++bisquare) {
      int n = 1;
      while (n < ariprog_length && bisquare_lookup[bisquares[bisquare] + (n * b)]) n++;
      if (n == ariprog_length) {
        output << bisquares[bisquare] << ' ' << b << std::endl;
        found_result = true;
      }
    }
  }

  if (!found_result) {
    output << "NONE" << std::endl;
  }
  return 0;
}