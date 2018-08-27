/*
ID: stapark1
LANG: C++14
TASK: zerosum
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <vector>

using operations_t = std::array<char, 8>;

int sequenceLength;
std::vector<std::string> solutions;
std::array<char, 3> kOperations = {'+', '-', ' '};

int parse(operations_t operations) {
  int result = 0;
  int signToken = 1;
  int numberToken = 1;
  for (int operation = 0; operation < sequenceLength - 1; ++operation) {
    int nextDigit = operation + 2;
    switch(operations[operation]) {
      case '+': {
        result += signToken * numberToken;
        signToken = 1;
        numberToken = nextDigit;
        break;
      }
      case '-': {
        result += signToken * numberToken;
        signToken = -1;
        numberToken = nextDigit;
        break;
      }
      case ' ': {
        numberToken = (numberToken * 10) + nextDigit;
        break;
      }
    }
  }

  return result + (signToken * numberToken);
}

std::string printSequence(operations_t operations) {
  std::string result = "1";
  for (int operation = 0; operation < sequenceLength - 1; ++operation) {
    result += operations[operation];
    result += '0' + (operation + 2);
  }
  return result;
}

std::vector<std::string> zeroSumSequences(operations_t currentOperations, int nextPosition) {
  std::vector<std::string> solutions;
  if (nextPosition == sequenceLength - 1) {
    if (parse(currentOperations) == 0)
      solutions.push_back(printSequence(currentOperations));
  } else {
    for (const char operation : kOperations) {
      currentOperations[nextPosition] = operation;
      for (const auto sequence : zeroSumSequences(currentOperations, nextPosition + 1)) {
        solutions.emplace_back(sequence);
      }
    }
  }
  return solutions;
}

int main() {
  std::ifstream input("zerosum.in");
  std::ofstream output("zerosum.out");

  input >> sequenceLength;

  operations_t rootSequence {};
  std::vector<std::string> solutions = zeroSumSequences(operations_t {}, 0);
  std::sort(solutions.begin(), solutions.end());
  for (const auto solution : solutions) {
    output << solution << std::endl;
  }
  return 0;
}
