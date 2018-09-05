/*
ID: stapark1
LANG: C++14
TASK: camelot
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <queue>
#include <utility>
#include <vector>

using coord_t = std::pair<int, int>;
using board_t = std::vector<std::vector<int>>;

std::ifstream input("camelot.in");
std::ofstream output("camelot.out");

std::array<int, 8> yOffset = {-2, -2, -1, 1, 2, 2, 1, -1};
std::array<int, 8> xOffset = {-1, 1, 2, 2, 1, -1, -2, -2};

int numKingMoves(const coord_t& start, const coord_t& dest) {
  int yDiff = std::abs(dest.first - start.first);
  int xDiff = std::abs(dest.second - start.second);
  return std::max(yDiff, xDiff);
}

int numRows, numCols;
board_t bfs(const coord_t& source) {
  board_t board;
  for (int i = 0; i < numRows; ++i) {
    board.emplace_back(std::vector<int> {});
    for (int j = 0; j < numCols; ++j) {
      board.back().emplace_back(-1);
    }
  }
  board[source.first][source.second] = 0;
  std::queue<std::pair<int, coord_t>> destinations;
  destinations.emplace(std::make_pair(0, source));
  while (!destinations.empty()) {
    int numMoves = destinations.front().first;
    coord_t coord = destinations.front().second;
    destinations.pop();

    for (int i = 0; i < 8; ++i) {
      int nextY = coord.first + yOffset[i];
      int nextX = coord.second + xOffset[i];
      if (nextY < 0 || nextY >= numRows || nextX < 0 || nextX >= numCols)
        continue;
      if (board[nextY][nextX] == -1) {
        board[nextY][nextX] = numMoves + 1;
        destinations.emplace(std::make_pair(numMoves + 1, std::make_pair(nextY, nextX)));
      }
    }
  }
  return board;
}

int main() {
  input >> numRows >> numCols;

  char col;
  int row;
  input >> col >> row;
  coord_t king = std::make_pair(row - 1, col - 'A');
  std::vector<coord_t> knights;
  while (input >> col >> row) {
    knights.emplace_back(std::make_pair(row - 1, col - 'A'));
  }

  std::vector<std::vector<board_t>> shortestPaths;
  for (int i = 0; i < numRows; ++i) {
    shortestPaths.emplace_back(std::vector<board_t> {});
    for (int j = 0; j < numCols; ++j) {
      coord_t source = std::make_pair(i, j);
      shortestPaths.back().emplace_back(bfs(source));
    }
  }

  const int kMaxDistance = knights.size() * (numRows - 1) * (numCols - 1) + numRows + numCols + 1;
  int minMoveCount = kMaxDistance;
  for (int i = 0; i < numRows; ++i) {
    for (int j = 0; j < numCols; ++j) {
      coord_t dest = std::make_pair(i, j);

      int totalKnightMoves = 0;
      for (const coord_t& knight : knights) {
        totalKnightMoves += shortestPaths[knight.first][knight.second][i][j];
      }
      if (totalKnightMoves < 0) continue;
      int totalSoloMoveCount = totalKnightMoves + numKingMoves(king, dest);
      if (totalSoloMoveCount < minMoveCount)
        minMoveCount = totalSoloMoveCount;

      int minExtraDist = kMaxDistance;
      for (int k = 0; k < knights.size(); ++k) {
        coord_t knight = knights[k];
        for (int m = king.first - 2; m < king.first + 3; ++m) {
          if (m < 0 || m >= numRows) continue;
          for (int n = king.second - 2; n < king.second + 3; ++n) {
            if (n < 0 || n >= numCols) continue;
            coord_t intermed = std::make_pair(m, n);
            int knightFirstLeg = shortestPaths[knight.first][knight.second][m][n];
            int knightSecondLeg = shortestPaths[m][n][i][j];
            if (knightFirstLeg < 0 || knightSecondLeg < 0) continue;
            int poolCount = numKingMoves(king, intermed) + knightFirstLeg + knightSecondLeg;
            int totalPoolMoveCount = totalKnightMoves - shortestPaths[knight.first][knight.second][i][j] + poolCount;
            minMoveCount = std::min(minMoveCount, totalPoolMoveCount);
          }
        }
      }
    }
  }

  output << minMoveCount << std::endl;
  return 0;
}