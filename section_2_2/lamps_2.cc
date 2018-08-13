/*
ID: stapark1
LANG: C++14
TASK: lamps
*/

#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

std::vector<bool> pressButton(std::vector<bool> initialState, int button) {
  for (int lamp = 0; lamp < initialState.size(); ++lamp) {
    if (button == 1 ||
       (button == 2 && lamp % 2 == 0) ||
       (button == 3 && lamp % 2 == 1) ||
       (button == 4 && (lamp + 1) % 3 == 1)) {
      initialState[lamp] = !initialState[lamp];
    };
  }
  return initialState;
}

std::unordered_map<int, bool> finalLampState;
bool matchesFinalState(const std::vector<bool>& lampState) {
  for (const auto& finalLamp : finalLampState) {
    if (lampState.at(finalLamp.first - 1) != finalLamp.second) return false;
  }
  return true;
}

std::string printLamps(const std::vector<bool>& lampState) {
  std::string result = "";
  for (const bool& state : lampState) {
    result += state ? '1' : '0';
  }
  return result;
}

int main() {
  std::ifstream input("lamps.in");
  std::ofstream output("lamps.out");

  int numLamps, numPresses;
  input >> numLamps >> numPresses;

  int lamp;
  input >> lamp;
  while (lamp > 0) {
    finalLampState[lamp] = true;
    input >> lamp;
  }
  input >> lamp;
  while (lamp > 0) {
    finalLampState[lamp] = false;
    input >> lamp;
  }

  std::vector<bool> initialState(numLamps, true);

  std::vector<std::string> matchingStates;
  std::unordered_map<std::string, bool> seenMatchingStates;
  if (numPresses != 1 && matchesFinalState(initialState)) {
    std::string lampBits = printLamps(initialState);
    matchingStates.emplace_back(lampBits);
    seenMatchingStates[lampBits] = true;
  }

  std::queue<std::pair<std::vector<int>, std::vector<bool>>> queue;
  queue.emplace(std::make_pair(std::vector<int> {}, initialState));

  while (!queue.empty()) {
    auto buttons = queue.front().first;
    auto lamps = queue.front().second;
    queue.pop();
    std::string lampBits = printLamps(lamps);
    if (matchesFinalState(lamps)) {
      if (seenMatchingStates.find(lampBits) == seenMatchingStates.end()) {
        matchingStates.emplace_back(lampBits);
        seenMatchingStates[lampBits] = true;
      }
    }
    if (buttons.size() == std::min(numPresses, 3)) continue;

    int firstButton = buttons.empty() ? 1 : buttons.back() + 1;
    for (int nextButton = firstButton; nextButton < 5; ++nextButton) {
      std::vector<int> nextButtons = buttons;
      nextButtons.emplace_back(nextButton);
      std::vector<bool> nextLamps = pressButton(lamps, nextButton);
      queue.emplace(std::make_pair(nextButtons, nextLamps));
    }
  }

  if (matchingStates.empty()) {
    output << "IMPOSSIBLE\n";
  } else {
    std::sort(matchingStates.begin(), matchingStates.end());
    for (const auto& state : matchingStates) {
      output << state << std::endl;
    }
  }
  return 0;
}