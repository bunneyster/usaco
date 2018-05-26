/*
ID: stapark1
LANG: C++14
TASK: castle
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

int width, height;
std::vector<int> components;  // 1-based component index for each module
std::vector<int> roomSizes;  // Size of each component
std::vector<std::vector<unsigned int>> floorplan;

void floodFill(int component, int h, int w) {
  if (components[h * width + w] != 0) return;
  components[h * width + w] = component;
  roomSizes.back()++;
  if (!(floorplan[h][w] & 1) && w - 1 >= 0)  // W is open
    floodFill(component, h, w - 1);
  if (!(floorplan[h][w] & 2) && h - 1 >= 0)  // N is open
    floodFill(component, h - 1, w);
  if (!(floorplan[h][w] & 4) && w + 1 < width)  // E is open
    floodFill(component, h, w + 1);
  if (!(floorplan[h][w] & 8) && h + 1 < height)  // S is open
    floodFill(component, h + 1, w);
}

int main() {
  std::ifstream input("castle.in");
  std::ofstream output("castle.out");

  input >> width >> height;
  components.resize(width * height);

  for (std::size_t h = 0; h < height; ++h) {
    floorplan.push_back(std::vector<unsigned int>{});
    for (std::size_t w = 0; w < width; ++w) {
      unsigned int wallCount;
      input >> wallCount;
      floorplan[h].push_back(wallCount);
    }
  }

  int numComponents = 0;
  int maxRoomSize = 0;
  for (std::size_t h = 0; h < height; ++h) {
    for (std::size_t w = 0; w < width; ++w) {
      if (components[h * width + w] == 0) {
        numComponents++;
        roomSizes.push_back(0);
        floodFill(numComponents, h, w);
        maxRoomSize = std::max(maxRoomSize, roomSizes.back());
      }
    }
  }

  int maxDoubleRoomSize = 0;
  int maxH, maxW;
  char maxDirection;
  for (std::size_t w = 0; w < width; ++w) {
    for (std::size_t rh = 0; rh < height; ++rh) {
      int h = height - rh - 1;
      int component = components[h * width + w];
      if ((floorplan[h][w] & 2) && h - 1 >= 0) {  // break N wall
        int neighborComponent = components[(h - 1) * width + w];
        if (component != neighborComponent) {
          int doubleRoomSize = roomSizes[component - 1] + roomSizes[neighborComponent - 1];
          if (doubleRoomSize > maxDoubleRoomSize) {
            maxDoubleRoomSize = doubleRoomSize;
            maxH = h;
            maxW = w;
            maxDirection = 'N';
          }
        }
      }
      if ((floorplan[h][w] & 4) && w + 1 < width) {  // break E wall
        int neighborComponent = components[h * width + w + 1];
        if (component != neighborComponent) {
          int doubleRoomSize = roomSizes[component - 1] + roomSizes[neighborComponent - 1];
          if (doubleRoomSize > maxDoubleRoomSize) {
            maxDoubleRoomSize = doubleRoomSize;
            maxH = h;
            maxW = w;
            maxDirection = 'E';
          }
        }
      }
    }
  }

  output << numComponents << std::endl;
  output << maxRoomSize << std::endl;
  output << maxDoubleRoomSize << std::endl;
  output << (maxH + 1) << ' ' << (maxW + 1) << ' ' << maxDirection << std::endl;
  return 0;
}
