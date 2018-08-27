/*
ID: stapark1
LANG: C++14
TASK: ariprog
*/

#include <array>
#include <cmath>
#include <fstream>
#include <vector>

int main() {
  std::ifstream input("ariprog.in");
  std::ofstream output("ariprog.out");

  int N;  // progression length
  int M;  // upper bound on bisquare components
  input >> N >> M;

  std::array<bool, 125001> bisquare_bitmap{};
  std::vector<int> ordered_bisquares;
  int bisquare;
  for (int p = 0; p <= M; ++p) {
    for (int q = 0; q <= M; ++q) {
      bisquare = std::pow(p, 2) + std::pow(q, 2);
      bisquare_bitmap[bisquare] = true;
    }
  }
  for (std::size_t i = 0; i < bisquare_bitmap.size(); ++i) {
    if (bisquare_bitmap[i]) ordered_bisquares.push_back(i);
  }

  bool empty_solution = true;
  int max_bisquare = std::pow(M, 2) + std::pow(M, 2);
  int max_b = (max_bisquare / (N - 1)) + 1;
  for (int b = 1; b < max_b; ++b) {
    for (const auto a : ordered_bisquares) {
      int n = 0;
      for (; n < N; ++n) {
        int sequence = a + (n * b);
        if (sequence > 125000 || !bisquare_bitmap[sequence]) break;
      }

      if (n == N) {
        output << a << ' ' << b << std::endl;
        empty_solution = false;
      }
    }
  }
  if (empty_solution) output << "NONE" << std::endl;

  return 0;
}