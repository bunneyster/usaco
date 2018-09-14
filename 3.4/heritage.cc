/*
ID: stapark1
LANG: C++14
TASK: heritage
*/

#include <fstream>
#include <utility>
#include <vector>

std::ifstream input("heritage.in");
std::ofstream output("heritage.out");

void buildTree(const std::string& inOrder, const std::string& preOrder) {
  if (inOrder.empty()) return;
  if (inOrder.size() == 1) {
    output << inOrder[0];
    return;
  }
  int rootIndex = inOrder.find(preOrder[0]);
  std::string leftSubTree = inOrder.substr(0, rootIndex);
  std::string rightSubTree = inOrder.substr(rootIndex + 1);
  buildTree(leftSubTree, preOrder.substr(1, leftSubTree.size()));
  buildTree(rightSubTree, preOrder.substr(1 + leftSubTree.size(), rightSubTree.size()));
  output << preOrder[0];
}

int main() {
  std::string inOrder, preOrder;
  input >> inOrder >> preOrder;

  buildTree(inOrder, preOrder);
  output << std::endl;
  return 0;
}