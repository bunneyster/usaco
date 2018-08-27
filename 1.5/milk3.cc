/*
ID: stapark1
LANG: C++14
TASK: milk3
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>

using state_t = std::array<int, 3>;

struct StateHash {
  std::size_t operator()(const state_t& s) const {
    return std::hash<int>()(s[0]) ^
           std::hash<int>()(s[1]) ^
           std::hash<int>()(s[2]);
  }
};

std::vector<state_t> next_states_for(const state_t state, const state_t capacity) {
  std::vector<state_t> result;
  state_t next_state;
  int current_amount, max_amount, pour_amount;
  for (int pour_bucket = 0; pour_bucket < 3; ++pour_bucket) {
    if (state[pour_bucket] == 0) continue;
    for (int receive_bucket = 0; receive_bucket < 3; ++receive_bucket) {
      if (pour_bucket == receive_bucket) continue;
      current_amount = state[receive_bucket];
      max_amount = capacity[receive_bucket];
      if (current_amount < max_amount) {
        next_state = state;
        pour_amount = std::min(state[pour_bucket], max_amount - current_amount);
        next_state[pour_bucket] -= pour_amount;
        next_state[receive_bucket] += pour_amount;
        result.push_back(next_state);
      }
    }
  }
  return result;
}

int main() {
  std::ifstream input("milk3.in");
  std::ofstream output("milk3.out");

  int a, b, c;
  input >> a >> b >> c;
  state_t full_capacity_state = {a, b, c};

  std::vector<int> result;
  std::unordered_map<state_t, bool, StateHash> seen_states;
  std::queue<state_t> unverified_states;
  state_t state = {0, 0, c};
  unverified_states.push(state);
  seen_states[state] = true;
  while (unverified_states.size() > 0) {
    state = unverified_states.front();
    unverified_states.pop();
    if (state[0] == 0) result.push_back(state[2]);
    for (const auto next_state : next_states_for(state, full_capacity_state)) {
      if (seen_states.find(next_state) == seen_states.end()) {
        unverified_states.push(next_state);
        seen_states[next_state] = true;
      }
    }
  }

  std::sort(result.begin(), result.end());
  output << result.front();
  for (int i = 1; i < result.size(); ++i) {
    output << ' ' << result[i];
  }
  output << std::endl;

  return 0;
}