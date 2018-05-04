/*
ID: stapark1
LANG: C++11
TASK: wormhole
*/

#include <fstream>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <vector>

enum class State { unvisited, visited, visiting };
using hole_t = std::pair<int, int>;
using pairing_t = std::unordered_map<int, int>;

std::vector<pairing_t> permutations(pairing_t& current, std::unordered_set<int>& waitlist) {
  std::vector<pairing_t> result;

  if (waitlist.empty()) {
    result.push_back(current);
  } else {
    int lhs = *waitlist.begin();
    waitlist.erase(lhs);
    std::unordered_set<int> next_waitlist;
    for (auto it = waitlist.begin(); it != waitlist.end(); ++it) {
      next_waitlist = waitlist;
      next_waitlist.erase(*it);
      current[lhs] = *it;
      current[*it] = lhs;

      for (const auto permutation : permutations(current, next_waitlist)) {
        result.push_back(permutation);
      }
    }
  }

  return result;
}

bool cyclic(int position, const pairing_t& ins, const pairing_t& outs, std::vector<State>& states) {
  if (states[position] == State::visiting) return true;
  if (states[position] == State::visited) return false;

  states[position] = State::visiting;

  bool result;
  auto next_in = outs.find(ins.at(position));
  if (next_in == outs.end()) {
    result = false;
  } else {
    result = cyclic(next_in->second, ins, outs, states);
  }

  states[position] = State::visited;
  return result;
}

int main() {
  std::ifstream input("wormhole.in");
  std::ofstream output("wormhole.out");

  int num_holes;
  input >> num_holes;

  pairing_t outs;  // Map outs to ins.
  pairing_t ins;  // Map ins to outs.

  std::vector<hole_t> holes;
  std::vector<State> states;
  int x, y;
  for (int i = 0; i < num_holes; ++i) {
    input >> x >> y;
    holes.emplace_back(x, y);
    states.push_back(State::unvisited);
  }

  // Populate outs indices map with exit holes that lead to another entrance hole.
  for (std::size_t out = 0; out < holes.size(); ++out) {
    for (std::size_t in = 0; in < holes.size(); ++in) {
      // 'in' hole is to the right of 'out' hole
      if (holes[out].second == holes[in].second && holes[in].first > holes[out].first) {
        auto current_pair = outs.find(out);
        // no entry in 'outs' map, or 'in' hole is better match
        if ((current_pair == outs.end()) || (holes[in].first < holes[current_pair->second].first)) {
          outs[out] = in;
        }
      }
    }
  }

  // Generate all permutations of the ins map.
  int result = 0;
  pairing_t temp{};
  std::unordered_set<int> waitlist{};
  for (int i = 0; i < num_holes; ++i) { waitlist.insert(i); }
  for (const auto ins_variant : permutations(temp, waitlist)) {
    for (int i = 0; i < num_holes; ++i) { states[i] = State::unvisited; }  // reset states
    for (int first_entry = 0; first_entry < num_holes; ++first_entry) {
      if (cyclic(first_entry, ins_variant, outs, states)) {
        result++;
        break;
      }
    }
  }

  output << result << std::endl;

  return 0;
}