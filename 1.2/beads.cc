/*
ID: stapark1
LANG: C++11
TASK: beads
*/

#include <algorithm>
#include <fstream>
#include <iostream>  // Required to pass on USACO for some reason.
#include <vector>
#include <string>

class Segment {
  public:
    Segment(char c = 'w', int l = 0) : color(c), length(l) {}
    char color;
    int length;
};

bool operator==(const Segment& lhs, const Segment& rhs) {
  return (lhs.color == 'w') ||
         (rhs.color == 'w') ||
         (lhs.color == rhs.color);
}

Segment segment_at(int index, const std::vector<Segment>& necklace) {
  return necklace[index % necklace.size()];
}

int length_from(int i, const std::vector<Segment>& necklace, int direction) {
  int result = 0;
  char color = 'w';
  Segment segment;
  for (int offset = 0; (segment = segment_at(i + (offset * direction), necklace)) == color; ++offset) {
    if (segment.color != 'w') {
      color = segment.color;
    }
    result += segment.length;
  }
  return result;
}

int main() {
  std::ifstream input("beads.in");
  std::ofstream output("beads.out");

  int total_beads;
  std::string beads;
  input >> total_beads >> beads;

  // Store consecutive beads of the same color as a Segment in a vector.
  Segment current_segment = {beads[0], 0};
  std::vector<Segment> necklace {current_segment};
  for (char& bead: beads) {
    if (bead == necklace.back().color) {
      necklace.back().length++;
    } else {
      current_segment = {bead, 1};
      necklace.push_back(current_segment);
    }
  }

  // Return early for necklaces with fewer than 4 segments.
    if (necklace.size() == 1) {
    output << necklace[0].length << std::endl;
    return 0;
  } else if (necklace.size() < 4) {
    int result;
    for (auto segment : necklace) {
      result += segment.length;
    }
    output << result << std::endl;
    return 0;
  }


  // Merge segments at ends if same color.
  if (necklace[0].color == necklace.back().color) {
    necklace[0].length += necklace.back().length;
    necklace.pop_back();
  }

  int max_length = 0;
  for (std::size_t i = 0; i < necklace.size(); ++i) {
    int current_length = 0;
    current_length += length_from(i + 1, necklace, -1);
    current_length += length_from(i + 2, necklace, 1);
    max_length = std::max(max_length, current_length);
  }

  output << max_length << std::endl;

  return 0;
}