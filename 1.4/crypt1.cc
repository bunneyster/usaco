/*
ID: stapark1
LANG: C++11
TASK: crypt1
*/

#include <cmath>
#include <fstream>
#include <vector>

bool has_valid_digits(int number, std::vector<int>& valid_digits) {
  int first_digits = number / 10;
  int last_digit = number % 10;
  if (first_digits < 1) {
    return (std::find(valid_digits.begin(), valid_digits.end(), last_digit) != valid_digits.end());
  } else {
    return has_valid_digits(first_digits, valid_digits) &&
           has_valid_digits(last_digit, valid_digits);
  }
}

bool has_at_most_x_digits(int number, int x) {
  return number / std::pow(10, x) < 1;
}

int main() {
  std::ifstream input("crypt1.in");
  std::ofstream output("crypt1.out");

  int n;
  input >> n;
  std::vector<int> digits;
  int digit;
  for (int i = 0; i < n; ++i) {
    input >> digit;
    digits.push_back(digit);
  }

  int result = 0;
  std::vector<int> partial_products;
  int multiplicand, partial_product, product;
  for (auto m1 : digits) {
    for (auto m10 : digits) {
      for (auto m100 : digits) {
        multiplicand = (100 * m100) + (10 * m10) + m1;
        for (auto x : digits) {
          partial_product = multiplicand * x;
          if (has_valid_digits(partial_product, digits) &&
              has_at_most_x_digits(partial_product, 3)) {
            partial_products.push_back(partial_product);
          }
        }
        for (const auto pp1 : partial_products) {
          for (const auto pp2 : partial_products) {
            product = pp1 + (10 * pp2);
            if (has_valid_digits(product, digits) &&
                has_at_most_x_digits(product, 4)) {
              result++;
            }
          }
        }
        partial_products.clear();
      }
    }
  }

  output << result << std::endl;
  return 0;
}