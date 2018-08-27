/*
ID: stapark1
LANG: C++14
TASK: ariprog
*/

#include <array>
#include <fstream>
#include <vector>

bool valid_ariprog(int a, int b, int N, std::array<bool, 2 * 250 * 250 + 1>& bisquares) {
  int bisquare;
  for (int n = 1; n < N; ++n) {
    bisquare = a + (n * b);
    if (bisquare >= bisquares.size()) return false;
    if (!bisquares[bisquare]) return false;
  }
  return true;
}

int main() {
  std::ifstream input("ariprog.in");
  std::ofstream output("ariprog.out");

  int length, max_q;
  input >> length >> max_q;

  std::array<bool, 2 * 250 * 250 + 1> bisquares{};
  std::vector<int> sorted_bisquares;
  for (int p = 0; p <= max_q; ++p) {
    for (int q = 0; q <= max_q; ++q) {
      bisquares[(p * p) + (q * q)] = true;
    }
  }
  for (int i = 0; i < bisquares.size(); ++i) {
    if (bisquares.at(i)) sorted_bisquares.push_back(i);
  }

  bool found_result = false;
  for (int b = 1; (length - 1) * b <= (2 * max_q * max_q); ++b) {
    for (const auto bisquare : sorted_bisquares) {
      if (valid_ariprog(bisquare, b, length, bisquares)) {
        output << bisquare << ' ' << b << std::endl;
        found_result = true;
      }
    }
  }

  if (!found_result) { output << "NONE" << std::endl; }
  return 0;
}