/*
ID: stapark1
LANG: C++14
TASK: ttwo
*/

#include <array>
#include <fstream>
#include <unordered_map>
#include <utility>

using coord_t = std::pair<int, int>;

std::array<int, 4> xMove = {0, 1, 0, -1};  // N, E, S, W
std::array<int, 4> yMove = {-1, 0, 1, 0};  // N, E, S, W
std::array<std::array<bool, 12>, 12> forest {};

class State {
  public:
    State(const coord_t& pos, int dir) : position{pos}, direction{dir} {}
    bool operator==(const State& other) const {
      return position == other.position && direction == other.direction;
    };
    int hash() const {
      int positionIndex = (position.first - 1) * 10 + position.second;
      return (positionIndex << 2) + direction;
    };
    coord_t position;
    int direction;
};

class TotalState {
  public:
    TotalState(const State& fState, const State& cState) : farmerState{fState}, cowState{cState} {}
    bool operator==(const TotalState& other) const {
      return farmerState == other.farmerState && cowState == other.cowState;
    };
    State farmerState;
    State cowState;
};

struct TotalStateHash {
  std::size_t operator()(const TotalState& totalState) const {
    int farmerHash = totalState.farmerState.hash();
    int cowHash = totalState.cowState.hash();
    return std::hash<int>()(farmerHash) ^ std::hash<int>()(cowHash);
  }
};

State nextStateFor(const State& state) {
  int direction = state.direction;
  int nextY = state.position.first + yMove[direction];
  int nextX = state.position.second + xMove[direction];

  State result(state.position, state.direction);
  if (forest[nextY][nextX]) {
    result.position = std::make_pair(nextY, nextX);
  } else {
    result.direction = (result.direction + 1) % 4;
  }
  return result;
};

std::ifstream input("ttwo.in");
std::ofstream output("ttwo.out");

int main() {
  std::pair<int, int> farmerPos, cowPos;
  int farmerDir, cowDir = 0;  // Initially facing N.
  for (int i = 1; i < 11; ++i) {
    for (int j = 1; j < 11; ++j) {
      char square;
      input >> square;
      if (square == 'F') {
        forest[i][j] = true;
        farmerPos = std::make_pair(i, j);
      } else if (square == 'C') {
        forest[i][j] = true;
        cowPos = std::make_pair(i, j);
      } else if (square == '.') {
        forest[i][j] = true;
      }
    }
  }

  State farmerState(farmerPos, farmerDir);
  State cowState(cowPos, cowDir);
  TotalState totalState(farmerState, cowState);

  std::unordered_map<TotalState, bool, TotalStateHash> seenStates;

  int minute = 0;
  while (seenStates.find(totalState) == seenStates.end() && farmerState.position != cowState.position) {
    seenStates[totalState] = true;
    farmerState = nextStateFor(farmerState);
    cowState = nextStateFor(cowState);
    totalState = {farmerState, cowState};
    minute++;
  }

  if (farmerState.position == cowState.position) {
    output << minute << std::endl;
  } else {
    output << 0 << std::endl;
  }
  return 0;
}