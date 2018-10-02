/*
ID: stapark1
LANG: C++14
TASK: rockers
*/

#include <algorithm>
#include <fstream>
#include <vector>

std::ifstream input("rockers.in");
std::ofstream output("rockers.out");

int maxNumSongs(const std::vector<int> disks, const std::vector<int> songs) {
  if (disks.empty() || songs.empty()) {
    return 0;
  }
  std::vector<int> nextSongs = songs;
  nextSongs.erase(nextSongs.begin());
  int excludeSong = maxNumSongs(disks, nextSongs);

  std::vector<int> nextDisks = disks;
  while (nextDisks.front() < songs.front() && !nextDisks.empty()) {
    nextDisks.erase(nextDisks.begin());
  }
  if (nextDisks.empty()) {
    return excludeSong;
  } else {
    nextDisks.front() -= songs.front();
    int includeSong = 1 + maxNumSongs(nextDisks, nextSongs);
    return std::max(includeSong, excludeSong);
  }
}

int main() {
  int numSongs, diskSize, numDisks;
  input >> numSongs >> diskSize >> numDisks;

  std::vector<int> songs;
  for (int i = 0; i < numSongs; ++i) {
    int songSize;
    input >> songSize;
    songs.emplace_back(songSize);
  }

  std::vector<int> disks(numDisks, diskSize);
  output << maxNumSongs(disks, songs) << std::endl;

  return 0;
}