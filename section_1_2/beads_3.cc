/*
ID: stapark1
LANG: C++14
TASK: beads
*/

#include <algorithm>
#include <fstream>

int numBeads;
std::string necklace;

int colorCount(char oppositeColor, int begin, int direction) {
  int count = 0;
  int position = (begin + numBeads) % numBeads;
  while (necklace[position] != oppositeColor && count < numBeads) {
    position = (position + numBeads + direction) % numBeads;
    count++;
  }
  return count;
}

int main() {
  std::ifstream input("beads.in");
  std::ofstream output("beads.out");

  input >> numBeads >> necklace;

  int maxCount = 0;
  for (int i = 0; i < numBeads; ++i) {
    int leftRed = colorCount('b', i - 1, -1);
    int leftBlue = colorCount('r', i - 1, -1);
    int rightRed = colorCount('b', i, 1);
    int rightBlue = colorCount('r', i, 1);

    int count = std::max(leftRed, leftBlue) + std::max(rightRed, rightBlue);
    maxCount = std::max(maxCount, count);
  }

  output << std::min(maxCount, numBeads) << std::endl;
  return 0;
}