/*
ID: stapark1
LANG: C++14
TASK: lamps
*/

#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>

std::ifstream input("lamps.in");
std::ofstream output("lamps.out");
int numLamps;
std::unordered_map<int, bool> finalConfig;

std::bitset<6> pressButtons(std::vector<int> buttons) {
  std::bitset<6> state("111111");  // Initially all lights are on.
  for (const int button : buttons) {
    switch(button) {
      case 1: state.flip(); break;
      case 2: state ^= std::bitset<6>("101010"); break;
      case 3: state ^= std::bitset<6>("010101"); break;
      case 4: state ^= std::bitset<6>("100100"); break;
    }
  }
  return state;
}

bool matches(const std::bitset<6>& state) {
  for (const auto& config : finalConfig) {
    int bitPos = 5 - ((config.first - 1) % 6);
    if (state.test(bitPos) != config.second) return false;
  }
  return true;
}

int main() {
  int numLamps, numPresses;
  input >> numLamps >> numPresses;
  int lamp;
  while (input >> lamp && lamp != -1)
    finalConfig[lamp] = true;
  while (input >> lamp && lamp != -1)
    finalConfig[lamp] = false;

  std::queue<std::vector<int>> buttonSequences;
  if (numPresses > 0) {
    for (int i = 1; i < 5; ++i) {
      buttonSequences.emplace(std::vector<int> {i});
    }
  }
  if (numPresses != 1)
    buttonSequences.emplace(std::vector<int> {});
  if (numPresses > 1) {
    for (int i = 1; i < 4; ++i) {
      buttonSequences.emplace(std::vector<int> {i, 4});
    }
  }

  std::vector<std::string> matchingConfigs;
  while (!buttonSequences.empty()) {
    std::vector<int> sequence = buttonSequences.front();
    buttonSequences.pop();
    std::bitset<6> finalState = pressButtons(sequence);
    if (matches(finalState)) {
      matchingConfigs.emplace_back(finalState.to_string());
    }
  }

  if (matchingConfigs.empty()) {
    output << "IMPOSSIBLE\n";
  } else {
    std::sort(matchingConfigs.begin(), matchingConfigs.end());
    for (const auto& baseConfig : matchingConfigs) {
      for (int i = 0; i < numLamps / 6; ++i) {
        output << baseConfig;
      }
      output << baseConfig.substr(0, numLamps % 6) << std::endl;
    }
  }


  return 0;
}