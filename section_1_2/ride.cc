/*
ID: stapark1
LANG: C++11
TASK: ride
*/

#include <fstream>
#include <iostream>

int compute_hash(std::string::iterator begin, std::string::iterator end) {
  int product = 1;
  while (begin != end) {
     product *= *begin++ - 'A' + 1;
  }
  return product % 47;
}

int main() {
  std::ifstream input("ride.in");
  std::ofstream output("ride.out");

  std::string comet, group;
  getline(input, comet);
  getline(input, group);

  int comet_hash = compute_hash(comet.begin(), comet.end());
  int group_hash = compute_hash(group.begin(), group.end());
  comet_hash == group_hash ? output << "GO\n" : output << "STAY\n";
  return 0;
}