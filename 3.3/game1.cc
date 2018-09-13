/*
ID: stapark1
LANG: C++14
TASK: game1
*/

#include <fstream>
#include <utility>
#include <vector>

std::ifstream input("game1.in");
std::ofstream output("game1.out");

int main() {
  int boardSize;
  input >> boardSize;

  std::vector<int> board;
  for (int i = 0; i < boardSize; ++i) {
    int number;
    input >> number;
    board.emplace_back(number);
  }

  // [i][j] => (player 1 score, player 2 score) for board from index i to j.
  std::vector<std::vector<std::pair<int, int>>> scores;
  for (int i = 0; i < boardSize; ++i) {
    scores.emplace_back(std::vector<std::pair<int, int>>(boardSize, std::make_pair(-1, -1)));
    scores[i][i] = std::make_pair(board[i], 0);
  }

  for (int length = 1; length < boardSize; ++length) {
    for (int begin = 0; begin + length < boardSize; ++begin) {
      int end = begin + length;
      int leftPickScore = board[begin] + scores[begin + 1][end].second;
      int rightPickScore = board[end] + scores[begin][end - 1].second;
      if (leftPickScore > rightPickScore) {
        scores[begin][end].first = leftPickScore;
        scores[begin][end].second = scores[begin + 1][end].first;
      } else {
        scores[begin][end].first = rightPickScore;
        scores[begin][end].second = scores[begin][end - 1].first;
      }
    }
  }

  std::pair<int, int> finalScores = scores[0][boardSize - 1];
  output << finalScores.first << ' ' << finalScores.second << std::endl;
  return 0;
}
