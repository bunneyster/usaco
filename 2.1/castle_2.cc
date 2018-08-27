/*
ID: stapark1
LANG: C++14
TASK: castle
*/

#include <algorithm>
#include <array>
#include <bitset>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

std::array<int, 4> xMove = {-1, 0, 1, 0};  // W, N, E, S
std::array<int, 4> yMove = {0, -1, 0, 1};  // W, N, E, S

int width, height;
std::vector<std::vector<std::bitset<4>>> walls;
std::unordered_map<int, int> rooms;
std::vector<int> sizes;

void exploreRoom(int x, int y) {
  int moduleIndex = y * width + x;
  if (x < 0 || x >= width || y < 0 || y >= height) return;
  if (rooms.find(moduleIndex) != rooms.end()) return;

  int room = sizes.size() - 1;
  rooms[moduleIndex] = room;
  sizes[room]++;

  for (int direction = 0; direction < 4; ++direction) {
    if (!walls[y][x].test(direction))
      exploreRoom(x + xMove[direction], y + yMove[direction]);
  }
}

int main() {
  std::ifstream input("castle.in");
  std::ofstream output("castle.out");

  input >> width >> height;

  for (int row = 0; row < height; ++row) {
    walls.emplace_back(std::vector<std::bitset<4>> {});
    for (int col = 0; col < width; ++col) {
      int module;
      input >> module;
      walls.back().emplace_back(std::bitset<4>(module));
    }
  }

  for (std::size_t row = 0; row < height; ++row) {
    for (std::size_t col = 0; col < width; ++col) {
      if (rooms.find(row * width + col) != rooms.end()) continue;
      sizes.emplace_back(0);
      exploreRoom(col, row);
    }
  }

  int maxJointSize = 0;
  int maxRow, maxCol;
  char maxDirection;
  for (int col = 0; col < width; ++col) {
    for (int row = height - 1; row >= 0; --row) {
      int room1 = rooms[row * width + col];
      if (walls[row][col].test(1) && row > 0) {  // N wall
        int room2 = rooms[(row - 1) * width + col];
        if (room1 != room2) {
          int jointSize = sizes[room1] + sizes[room2];
          if (maxJointSize < jointSize) {
            maxJointSize = jointSize;
            maxRow = row;
            maxCol = col;
            maxDirection = 'N';
          }
        }
      }
      if (walls[row][col].test(2) && col < width - 1) {  // E wall
        int room2 = rooms[row * width + col + 1];
        if (room1 != room2) {
          int jointSize = sizes[room1] + sizes[room2];
          if (maxJointSize < jointSize) {
            maxJointSize = jointSize;
            maxRow = row;
            maxCol = col;
            maxDirection = 'E';
          }
        }
      }
    }
  }

  output << sizes.size() << std::endl;
  output << *std::max_element(sizes.begin(), sizes.end()) << std::endl;
  output << maxJointSize << std::endl;
  output << (maxRow + 1) << ' ' << (maxCol + 1) << ' ' << maxDirection << std::endl;

  return 0;
}