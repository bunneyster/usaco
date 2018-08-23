/*
ID: stapark1
LANG: C++14
TASK: castle
*/

#include <algorithm>
#include <fstream>
#include <vector>

std::ifstream input("castle.in");
std::ofstream output("castle.out");

std::vector<std::vector<int>> floorplan;
std::vector<std::vector<int>> rooms;
std::vector<int> roomSize;

void exploreRoom(int i, int j, int room) {
  if (rooms[i][j] != -1) return;
  rooms[i][j] = room;
  roomSize.back()++;
  if (!(floorplan[i][j] & 1))  // W wall open
    exploreRoom(i, j - 1, room);
  if (!(floorplan[i][j] & 2))  // N wall open
    exploreRoom(i - 1, j, room);
  if (!(floorplan[i][j] & 4))  // E wall open
    exploreRoom(i, j + 1, room);
  if (!(floorplan[i][j] & 8))  // S wall open
    exploreRoom(i + 1, j, room);
}

int main() {
  int width, height;
  input >> width >> height;

  for (int i = 0; i < height; ++i) {
    floorplan.emplace_back(std::vector<int> {});
    rooms.emplace_back(std::vector<int>(width, -1));
    for (int j = 0; j < width; ++j) {
      int square;
      input >> square;
      floorplan.back().emplace_back(square);
    }
  }

  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      if (rooms[i][j] != -1) continue;
      roomSize.emplace_back(0);
      exploreRoom(i, j, roomSize.size() - 1);
    }
  }

  int largestSingleSize = 0;
  int largestJointSize = 0;
  char wallDirection;
  int wallY, wallX;
  for (int x = 0; x < width; ++x) {
    for (int y = height - 1; y >= 0; --y) {
      int size = roomSize[rooms[y][x]];
      largestSingleSize = std::max(largestSingleSize, size);
      if (floorplan[y][x] & 2) {  // N wall
        if (y - 1 >= 0 && rooms[y - 1][x] != rooms[y][x]) {
          int newRoomSize = roomSize[rooms[y - 1][x]] + size;
          if (newRoomSize > largestJointSize) {
            largestJointSize = newRoomSize;
            wallDirection = 'N';
            wallY = y;
            wallX = x;
          }
        }
      }
      if (floorplan[y][x] & 4) {  // E wall
        if (x + 1 < width && rooms[y][x + 1] != rooms[y][x]) {
          int newRoomSize = roomSize[rooms[y][x + 1]] + size;
          if (newRoomSize > largestJointSize) {
            largestJointSize = newRoomSize;
            wallDirection = 'E';
            wallY = y;
            wallX = x;
          }
        }
      }
    }
  }

  output << roomSize.size() << std::endl;
  output << largestSingleSize << std::endl;
  output << largestJointSize << std::endl;
  output << (wallY + 1) << ' ' << (wallX + 1) << ' ' << wallDirection << std::endl;
  return 0;
}