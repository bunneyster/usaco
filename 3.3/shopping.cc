/*
ID: stapark1
LANG: C++14
TASK: shopping
*/

#include <array>
#include <fstream>
#include <unordered_map>
#include <vector>

using basket_t = std::array<int, 5>;

std::ifstream input("shopping.in");
std::ofstream output("shopping.out");
std::vector<basket_t> bundles;
std::vector<int> bundlePrices;
std::unordered_map<int, int> regularPrices;
std::unordered_map<int, int> productIds;

struct BasketHasher {
  std::size_t operator()(const basket_t& basket) const {
    int hash = 0;
    for (int qty : basket) {
      hash = hash * 6 + qty;
    }
    return hash;
  }
};

int regularPrice(const basket_t& basket) {
  int price = 0;
  for (int i = 0; i < basket.size(); ++i) {
    price += regularPrices[i] * basket[i];
  }
  return price;
}

std::unordered_map<basket_t, int, BasketHasher> savedBaskets;
int bestPrice(const basket_t& basket) {
  if (savedBaskets.find(basket) != savedBaskets.end())
    return savedBaskets[basket];

  int minPrice = regularPrice(basket);

  for (int i = 0; i < bundles.size(); ++i) {
    basket_t smallBasket = basket;
    bool validBundle = true;
    for (int j = 0; j < bundles[i].size(); ++j) {
      if (smallBasket[j] < bundles[i][j]) {
        validBundle = false;
        break;
      }
      smallBasket[j] -= bundles[i][j];
    }
    if (validBundle)
      minPrice = std::min(minPrice, bestPrice(smallBasket) + bundlePrices[i]);
  }
  savedBaskets[basket] = minPrice;
  return minPrice;
}

int main() {
  int numOffers;
  input >> numOffers;
  for (int i = 0; i < numOffers; ++i) {
    int numProducts;
    input >> numProducts;
    bundles.emplace_back(basket_t {});
    for (int j = 0; j < numProducts; ++j) {
      int productId, productQty;
      input >> productId >> productQty;
      if (productIds.find(productId) == productIds.end())
        productIds[productId] = productIds.size();
      bundles.back()[productIds[productId]] = productQty;
    }
    int price;
    input >> price;
    bundlePrices.emplace_back(price);
    savedBaskets[bundles.back()] = price;
  }

  basket_t finalPurchase {};
  int numPurchasedProducts;
  input >> numPurchasedProducts;
  for (int i = 0; i < numPurchasedProducts; ++i) {
    int productId, productQty, price;
    input >> productId >> productQty >> price;
    if (productIds.find(productId) == productIds.end())
      productIds[productId] = productIds.size();
    finalPurchase[productIds[productId]] = productQty;
    regularPrices[productIds[productId]] = price;
  }

  output << bestPrice(finalPurchase) << std::endl;
  return 0;
}