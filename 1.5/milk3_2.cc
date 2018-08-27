/*
ID: stapark1
LANG: C++14
TASK: milk3
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <unordered_map>
#include <vector>

using state_t = std::array<int, 3>;

struct StateHash {
  std::size_t operator()(const state_t& state) const {
    return std::hash<int>()(state[0]) ^
           std::hash<int>()(state[1]) ^
           std::hash<int>()(state[2]);
  }
};

void find_all_states(state_t state, state_t max_state, std::unordered_map<state_t, bool, StateHash>& seen_states) {
  seen_states[state] = true;

  state_t next_state;
  int available_capacity, pour_amount;
  for (int pour_bucket = 0; pour_bucket < 3; ++pour_bucket) {
    if (state[pour_bucket] == 0) continue;
    for (int fill_bucket = 0; fill_bucket < 3; ++fill_bucket) {
      if (pour_bucket == fill_bucket) continue;
      available_capacity = max_state[fill_bucket] - state[fill_bucket];
      if (available_capacity > 0) {
        next_state = state;
        pour_amount = std::min(state[pour_bucket], available_capacity);
        next_state[pour_bucket] -= pour_amount;
        next_state[fill_bucket] += pour_amount;
        if (seen_states.find(next_state) == seen_states.end()) {
          find_all_states(next_state, max_state, seen_states);
        }
      }
    }
  }
}

int main() {
  std::ifstream input("milk3.in");
  std::ofstream output("milk3.out");

  int A, B, C;
  input >> A >> B >> C;

  std::unordered_map<state_t, bool, StateHash> seen_states;
  state_t initial_state = {0, 0, C};
  state_t max_state = {A, B, C};
  find_all_states(initial_state, max_state, seen_states);

  std::vector<int> results;
  for (const auto state : seen_states) {
    if (state.first[0] == 0) results.push_back(state.first[2]);
  }
  std::sort(results.begin(), results.end());

  output << results[0];
  for (int i = 1; i < results.size(); ++i) {
    output << ' ' << results[i];
  }
  output << std::endl;
  return 0;
}