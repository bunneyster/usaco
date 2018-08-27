/*
ID: stapark1
LANG: C++14
TASK: fracdec
*/

#include <fstream>
#include <unordered_map>

std::ifstream input("fracdec.in");
std::ofstream output("fracdec.out");

int main() {
  int num, den;
  input >> num >> den;

  std::string solution = std::to_string(num / den) + '.';

  std::unordered_map<int, int> seenRemainderIndex;
  std::string decimalValues = "";
  num %= den;
  while (num % den != 0) {
    if (seenRemainderIndex.find(num % den) != seenRemainderIndex.end()) {
      decimalValues.insert(seenRemainderIndex[num % den], "(");
      decimalValues += ')';
      break;
    }
    seenRemainderIndex[num % den] = decimalValues.size();
    num *= 10;
    int quotient = num / den;
    decimalValues += '0' + quotient;
    num %= den;
  }

  solution += decimalValues.empty() ? "0" : decimalValues;
  for (int i = 0; i < solution.size(); ++i) {
    output << solution[i];
    if ((i + 1) % 76 == 0 || i == solution.size() - 1)
      output << std::endl;
  }
  return 0;
}