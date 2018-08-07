/*
ID: stapark1
LANG: C++14
TASK: frac1
*/

#include <fstream>
#include <iostream>

int maxDenominator;

void print(std::ofstream& ofstream, int ln, int ld, int rn, int rd) {
  if (ld + rd > maxDenominator) return;

  print(ofstream, ln, ld, ln + rn, ld + rd);
  ofstream << (ln + rn) << '/' << (ld + rd) << std::endl;
  print(ofstream, ln + rn, ld + rd, rn, rd);
}

int main() {
  std::ifstream input("frac1.in");
  std::ofstream output("frac1.out");

  input >> maxDenominator;

  output << "0/1\n";
  print(output, 0, 1, 1, 1);
  output << "1/1\n";

  return 0;
}

