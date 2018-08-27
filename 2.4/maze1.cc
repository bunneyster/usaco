/*
ID: stapark1
LANG: C++14
TASK: maze1
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#include <utility>

using coord_t = std::pair<int, int>;

std::array<int, 4> xOffsets = {-1, 0, 1, 0};
std::array<int, 4> yOffsets = {0, -1, 0, 1};

int width, height;
std::vector<std::vector<int>> maze;

int initialValue(int y, int x, char symbol) {
  if (symbol != ' ') return -1;
  return (x == 0 || x == width * 2 || y == 0 || y == height * 2) ? 1 : 0;
}

void printMaze() {
  for (const auto& row : maze) {
    for (const int col : row) {
      if (col == -1) {
        std::cout << '*';
      } else {
        std::cout << col;
      }
    }
    std::cout << std::endl;
  }
  std::cout << "\n\n";
}

int main() {
  std::ifstream input("maze1.in");
  std::ofstream output("maze1.out");

  input >> width >> height;


  std::queue<coord_t> unexpandedCoords;
  std::string row;
  std::getline(input, row);  // Read first newline.
  for (int h = 0; h < height * 2 + 1; ++h) {
    std::getline(input, row);
    row.resize(width * 2 + 1, ' ');
    maze.emplace_back(std::vector<int>{});
    for (int w = 0; w < width * 2 + 1; ++w) {
      int iv = initialValue(h, w, row[w]);
      if (iv > 0)
        unexpandedCoords.push(std::make_pair(h, w));
      maze.back().emplace_back(initialValue(h, w, row[w]));
    }
  }

  int maxLength = 0;
  while (!unexpandedCoords.empty()) {
    coord_t coord = unexpandedCoords.front();
    unexpandedCoords.pop();
    for (std::size_t i = 0; i < 4; ++i) {
      int neighborY = coord.first + yOffsets[i];
      int neighborX = coord.second + xOffsets[i];
      if (neighborX > 0 && neighborX < width * 2 && neighborY > 0 && neighborY < height * 2 && maze[neighborY][neighborX] == 0) {
        maze[neighborY][neighborX] = maze[coord.first][coord.second] + 1;
        maxLength = std::max(maxLength, maze[neighborY][neighborX]);
        unexpandedCoords.push(std::make_pair(neighborY, neighborX));
      }
    }
    // printMaze();
  }

  output << (maxLength / 2) << std::endl;
  return 0;
}