/*
ID: stapark1
LANG: C++14
TASK: maze1
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <queue>
#include <utility>
#include <vector>

std::array<int, 4> xDiff = {0, 1, 0, -1};  // up, right, down, left
std::array<int, 4> yDiff = {-1, 0, 1, 0};  // up, right, down, left

std::ifstream input("maze1.in");
std::ofstream output("maze1.out");

int main() {
  int width, height;
  input >> width >> height;
  std::string newline;
  std::getline(input, newline);

  std::vector<std::pair<int, int>> exits;
  int maxLength = (2 * width) * (2 * height);
  std::vector<std::vector<int>> maze;
  for (int h = 0; h < 2 * height + 1; ++h) {
    maze.emplace_back(std::vector<int> {});
    std::string row;
    std::getline(input, row);
    row.resize(2 * width + 1, ' ');
    for (const char& col : row) {
      maze.back().emplace_back(col == ' ' ? maxLength : -1);
    }
  }

  std::queue<std::pair<int, int>> queue;
  for (int h = 0; h < 2 * height + 1; ++h) {
    for (int w = 0; w < 2 * width + 1; ++w) {
      if ((h == 0 || h == 2 * height || w == 0 || w == 2 * width) && maze[h][w] != -1) {
        queue.emplace(std::make_pair(h, w));
        maze[h][w] = 1;
      }
    }
  }

  while (!queue.empty()) {
    std::pair<int, int> square = queue.front();
    queue.pop();
    for (int direction = 0; direction < 4; ++direction) {
      int neighY = square.first + yDiff[direction];
      int neighX = square.second + xDiff[direction];
      if (neighY <= 0 || neighY >= 2 * height || neighX <= 0 || neighX >= 2 * width)
        continue;
      if (maze[neighY][neighX] > maze[square.first][square.second] + 1) {
        maze[neighY][neighX] = maze[square.first][square.second] + 1;
        queue.emplace(std::make_pair(neighY, neighX));
      }
    }
  }

  int result = 0;
  for (const auto& row : maze) {
    for (const int& square : row) {
      result = std::max(result, square);
    }
  }

  output << (result / 2) << std::endl;

  return 0;
}
