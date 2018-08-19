/*
ID: stapark1
LANG: C++14
TASK: zerosum
*/

#include <array>
#include <fstream>
#include <iostream>

std::array<char, 3> operations = {' ', '+', '-'};
std::ifstream input("zerosum.in");
std::ofstream output("zerosum.out");
int finalDigit;

int eval(const std::string& sequence) {
  int sum = 0;
  int term = 0;
  int sign = 1;
  for (char s : sequence) {
    switch(s) {
      case '+':
      case '-':
        sum += sign * term;  // Account for term collected until this character.
        term = 0;  // Reset term for upcoming digit character.
        sign = (s == '+') ? 1 : -1;  // Set sign for upcoming term.
        break;
      case ' ': break;
      default: // Digit character
        term = term * 10 + (s - '0');
    }
  }
  sum += sign * term;  // Account for last term in the sequence.
  return sum;
}

void search(const std::string& sequence, int nextDigit) {
  if (nextDigit > finalDigit) {
    if (eval(sequence) == 0)
      output << sequence << std::endl;
  } else {
    for (char operation : operations) {
      search(sequence + operation + (char)('0' + nextDigit), nextDigit + 1);
    }
  }
}

int main() {
  input >> finalDigit;
  search("1", 2);
  return 0;
}