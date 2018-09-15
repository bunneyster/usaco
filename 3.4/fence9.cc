/*
ID: stapark1
LANG: C++14
TASK: fence9
*/

#include <algorithm>
#include <cmath>
#include <fstream>

std::ifstream input("fence9.in");
std::ofstream output("fence9.out");

uint32_t pointsWithinFence(long double fenceY) {
  long double integer;
  return (std::modf(fenceY, &integer) > 0) ? integer : integer - 1;
}

int main() {
  long double lattice1X, lattice1Y, lattice2X;
  input >> lattice1X >> lattice1Y >> lattice2X;

  uint32_t cowCount = 0;
  if (lattice1X <= lattice2X) {
    for (int x = 1; x < lattice1X; ++x) {
      long double fenceY = lattice1Y / lattice1X * x;
      cowCount += pointsWithinFence(fenceY);
    }
    for (int x = std::max(1, (int)lattice1X); x < lattice2X; ++x) {
      long double fenceSlope = lattice1Y / (lattice1X - lattice2X);
      long double fenceYIntercept = -1 * fenceSlope * lattice2X;
      long double fenceY = fenceSlope * x + fenceYIntercept;
      cowCount += pointsWithinFence(fenceY);
    }
  } else {
    for (int x = 1; x < lattice2X; ++x) {
      long double fenceY = lattice1Y / lattice1X * x;
      cowCount += pointsWithinFence(fenceY);
    }
    for (int x = lattice2X; x < lattice1X; ++x) {
      long double fence1Y = lattice1Y / lattice1X * x;
      long double fence2Slope = lattice1Y / (lattice1X - lattice2X);
      long double fence2YIntercept = -1 * fence2Slope * lattice2X;
      long double fence2Y = fence2Slope * x + fence2YIntercept;
      for (int y = 1; y < lattice1Y; ++y) {
        if (y > fence2Y && y < fence1Y) cowCount++;
      }
    }
  }

  output << cowCount << std::endl;
  return 0;
}