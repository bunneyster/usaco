/*
ID: stapark1
LANG: C++14
TASK: hamming
*/

#include <bitset>
#include <cmath>
#include <fstream>
#include <vector>

std::vector<int> results {0};
int kMinHammingDistance;

bool willItHamm(int newWord) {
  for (const int hammedWord : results) {
    const std::bitset<8> kDiffWord = newWord ^ hammedWord;
    if (kDiffWord.count() < kMinHammingDistance) return false;
  }
  return true;
}

int main() {
  std::ifstream input("hamming.in");
  std::ofstream output("hamming.out");

  int kNumWords, kNumBits;
  input >> kNumWords >> kNumBits >> kMinHammingDistance;

  const int kMaxWord = std::pow(2, kNumBits);
  for (int word = 1; (word < kMaxWord) && (results.size() < kNumWords); ++word) {
    if (willItHamm(word))
      results.push_back(word);
  }

  for (std::size_t i = 0; i < results.size(); ++i) {
    output << results[i];
    if ((i + 1) % 10 == 0 || i == results.size() - 1) {
      output << std::endl;
    } else {
      output << ' ';
    }
  }

  return 0;
}