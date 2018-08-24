/*
ID: stapark1
LANG: C++14
TASK: ttwo
*/

#include <array>
#include <fstream>
#include <utility>

std::ifstream input("ttwo.in");
std::ofstream output("ttwo.out");
std::array<int, 4> yDelta = {-1, 0, 1, 0};  // N, E, S, W
std::array<int, 4> xDelta = {0, 1, 0, -1};  // N, E, S, W
std::array<std::array<bool, 12>, 12> grid {};

struct Orientation {
  std::pair<int, int> coord;
  int direction;
} farmer, cow;

Orientation nextState(const Orientation& state) {
  int nextY = state.coord.first + yDelta[state.direction];
  int nextX = state.coord.second + xDelta[state.direction];
  Orientation result = state;
  if (grid[nextY][nextX]) {
    result.coord = std::make_pair(nextY, nextX);
  } else {
    result.direction = (state.direction + 1) % 4;
  }
  return result;
}

int main() {
  farmer.direction = 0;
  cow.direction = 0;
  for (int i = 1; i <= 10; ++i) {
    for (int j = 1; j <= 10; ++j) {
      char square;
      input >> square;
      if (square == '*') continue;
      if (square == 'F') {
        farmer.coord = std::make_pair(i, j);
      } else if (square == 'C') {
        cow.coord = std::make_pair(i, j);
      }
      grid[i][j] = true;
    }
  }

  int minute = 0;
  while (minute < 1600) {
    if (farmer.coord == cow.coord) break;
    farmer = nextState(farmer);
    cow = nextState(cow);
    minute++;
  }

  output << minute % 1600 << std::endl;
  return 0;
}