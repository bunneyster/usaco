/*
ID: stapark1
LANG: C++14
TASK: hamming
*/

#include <fstream>
#include <vector>

int numWords, numBits, hammDist;
std::vector<int> solutions;

bool hamms(int word) {
  for (auto solution : solutions) {
    int setBits = word ^ solution;
    int numSetBits = 0;
    for (int bit = 0; bit < numBits; ++bit) {
      numSetBits += setBits & 1;
      setBits >>= 1;
    }
    if (numSetBits < hammDist) return false;
  }
  return true;
}

int main() {
  std::ifstream input("hamming.in");
  std::ofstream output("hamming.out");

  input >> numWords >> numBits >> hammDist;


  for (int i = 0; solutions.size() < numWords; ++i) {
    if (hamms(i)) solutions.emplace_back(i);
  }

  for (int i = 0; i < solutions.size() - 1; ++i) {
    output << solutions[i];
    ((i + 1) % 10 == 0) ? (output << std::endl) : (output << ' ');
  }
  output << solutions.back() << std::endl;

  return 0;
}