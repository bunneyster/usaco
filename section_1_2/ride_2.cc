/*
ID: stapark1
LANG: C++11
TASK: ride
*/

#include <fstream>
#include <iostream>
#include <string>

int hash(std::string name) {
  int result = 1;
  for (char letter : name) {
    result *= (letter - 'A' + 1);
  }
  return result % 47;
}

int main() {
  std::ifstream input("ride.in");
  std::ofstream output("ride.out");

  std::string comet, group;
  input >> comet >> group;

  std::string result = hash(comet) == hash(group) ? "GO" : "STAY";
  output << result << std::endl;

  return 0;
}