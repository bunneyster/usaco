/*
ID: stapark1
LANG: C++14
TASK: lamps
*/

#include <algorithm>
#include <array>
#include <bitset>
#include <fstream>
#include <vector>

using lampState_t = std::bitset<100>;

int kNumLamps, kNumPresses;
std::vector<int> onPositions, offPositions;

std::vector<int> readPositions(std::ifstream& input) {
  std::vector<int> result;
  int position;
  input >> position;
  while (position != -1) {
    result.push_back(position);
    input >> position;
  }
  return result;
}

lampState_t flipEvery(lampState_t originalState, int start, int interval) {
  for (std::size_t i = start; i < originalState.size(); i += interval)
    originalState.flip(i);
  return originalState;
}

lampState_t pressButton(int buttonMask, lampState_t originalState) {
  switch(buttonMask) {
    case 1: return originalState.flip();            // Flip all
    case 2: return flipEvery(originalState, 0, 2);  // Flip evens
    case 4: return flipEvery(originalState, 1, 2);  // Flip odds
    case 8: return flipEvery(originalState, 0, 3);  // Flip thirds
    default: return originalState;
  }
}

lampState_t pressButtons(int buttonConfig, lampState_t originalState) {
  lampState_t finalState = originalState;
  for (int mask = 1; mask < 16; mask <<= 1)
    if (buttonConfig & mask) finalState = pressButton(mask, finalState);
  return finalState;
}

bool matchesRequiredStates(lampState_t state) {
  for (const int position : onPositions)  // position value should be 1
    if (!state.test(state.size() - position)) return false;
  for (const int position : offPositions)  // position value should be 0
    if (state.test(state.size() - position)) return false;
  return true;
}

std::vector<std::array<bool, 17>> reachability;

bool canBeReached(int numPresses, int buttonConfig) {
  if (numPresses == 0) return buttonConfig == 0;
  for (int mask = 1; mask < 16; mask <<= 1) {
    if (reachability[numPresses - 1][buttonConfig ^ mask]) return true;
  }
  return false;
}

int main() {
  std::ifstream input("lamps.in");
  std::ofstream output("lamps.out");

  input >> kNumLamps >> kNumPresses;

  onPositions = readPositions(input);
  offPositions = readPositions(input);

  std::vector<std::string> states;
  lampState_t originalState;
  originalState.flip();
  for (int numPresses = 0; numPresses <= kNumPresses; ++numPresses) {
    reachability.push_back(std::array<bool, 17> {});
    for (int buttonConfig = 0; buttonConfig < 16; ++buttonConfig)
      reachability.back()[buttonConfig] = canBeReached(numPresses, buttonConfig);
  }

  for (int buttonConfig = 0; buttonConfig < 16; ++buttonConfig) {
    if (reachability[kNumPresses][buttonConfig]) {
      lampState_t finalLampState = pressButtons(buttonConfig, originalState);
      if (matchesRequiredStates(finalLampState))
        states.push_back(finalLampState.to_string().substr(0, kNumLamps));
    }
  }

  std::sort(states.begin(), states.end());

  if (states.empty()) {
    output << "IMPOSSIBLE" << std::endl;
  } else {
    for (auto state : states) output << state << std::endl;
  }
  return 0;
}