/*
ID: stapark1
LANG: C++11
TASK: wormhole
*/

#include <fstream>
#include <unordered_map>
#include <vector>

enum class State { unvisited, visiting, visited };

class Hole {
  public:
    Hole();
    Hole(int xcoord, int ycoord)
        : x{xcoord}, y{ycoord}, state{State::unvisited} {}
    int x;
    int y;
    bool is_visited() { return state == State::visited; }
    bool is_visiting() { return state == State::visiting; }
    void enter() { state = State::visiting; }
    void leave() { state = State::visited; }
    void reset() { state = State::unvisited; }
  private:
    State state;
};

using pairing = std::unordered_map<int, int>;

// Return the index of the wormhole into which wormhole i leads. Return -1 if
// wormhole i leads to a dead end.
int next_entrance(int i, pairing& entrances, pairing& exits) {
  auto next_i = exits.find(entrances[i]);
  if (next_i == exits.end()) {
    return -1;
  } else {
    return next_i->second;
  }
}

// Return whether entering wormhole i results in a cycle.
bool has_cycle(int i, std::vector<Hole>& holes, pairing& entrances, pairing& exits) {
  if (holes[i].is_visiting()) return true;

  holes[i].enter();
  int next_i = next_entrance(i, entrances, exits);
  if ((next_i >= 0) && (!holes[next_i].is_visited()) && (has_cycle(next_i, holes, entrances, exits))) {
    return true;
  }
  holes[i].leave();
  return false;
}

// Returns all permutations of length n, such that a value and its index form a
// cycle.
std::vector<pairing> permute(int n, pairing& current) {
  std::vector<pairing> result;
  if (current.size() == n) {
    result.push_back(current);
    return result;
  }

  int first_empty_position = 0;
  while (current.find(first_empty_position) != current.end()) {
    first_empty_position++;
  }
  for (int value = 0; value < n; ++value) {
    if ((current.find(value) == current.end()) && (first_empty_position != value)) {
      current[first_empty_position] = value;
      current[value] = first_empty_position;

      for (const auto permutation : permute(n, current)) {
        result.push_back(permutation);
      }

      current.erase(first_empty_position);
      current.erase(value);
    }
  }
  return result;
}

int main() {
  std::ifstream input("wormhole.in");
  std::ofstream output("wormhole.out");

  int total_portals;
  input >> total_portals;

  std::vector<Hole> holes;
  int x, y;
  for (int i = 0; i < total_portals; ++i) {
    input >> x >> y;
    auto hole = new Hole{x, y};
    holes.push_back(*hole);
  }

  // Maps each wormhole exit to its corresponding entrance. Missing entries
  // indicate a dead end.
  pairing exits;
  for (std::size_t i = 0; i < holes.size(); ++i) {
    for (std::size_t j = 0; j < holes.size(); ++j) {
      if ((holes[i].y == holes[j].y) && (holes[i].x < holes[j].x)) {  // Same row.
        const auto current_pair = exits.find(i);
        if (current_pair == exits.end() || holes[j].x < holes[current_pair->second].x) {
          exits[i] = j;
        }
      }
    }
  }

  int result = 0;
  pairing temp_pairing;
  std::vector<pairing> all_pairings = permute(total_portals, temp_pairing);
  for (auto entrances : all_pairings) {
    for (std::size_t i = 0; i < holes.size(); ++i) {
      if (!holes[i].is_visited() && has_cycle(i, holes, entrances, exits)) {
        result++;
        break;
      }
    }
    for (auto pair : entrances) {
      holes[pair.first].reset();
    }
  }
  output << result << std::endl;

  return 0;
}