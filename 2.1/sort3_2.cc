/*
ID: stapark1
LANG: C++14
TASK: sort3
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <vector>

int main() {
  std::ifstream input("sort3.in");
  std::ofstream output("sort3.out");

  int length;
  input >> length;

  std::array<int, 3> keyCounts {0};
  std::vector<int> sequence;
  for (int i = 0; i < length; ++i) {
    int record;
    input >> record;
    sequence.emplace_back(record);
    keyCounts[record - 1]++;
  }

  int pos = 0;
  std::array<std::array<int, 3>, 3> misKeyCounts {0};
  for (int key = 0; key < keyCounts.size(); ++key) {
    for (int count = 0; count < keyCounts[key]; ++count, ++pos) {
      misKeyCounts[key][sequence[pos] - 1]++;
    }
  }

  int oneTwoSwaps = std::min(misKeyCounts[0][1], misKeyCounts[1][0]);
  int oneThreeSwaps = std::min(misKeyCounts[0][2], misKeyCounts[2][0]);
  int twoThreeSwaps = std::min(misKeyCounts[1][2], misKeyCounts[2][1]);
  int doubleSwaps = std::max(misKeyCounts[0][1], misKeyCounts[1][0]) - oneTwoSwaps;

  int totalSwaps = oneTwoSwaps + oneThreeSwaps + twoThreeSwaps + 2 * doubleSwaps;

  output << totalSwaps << std::endl;

  return 0;
}