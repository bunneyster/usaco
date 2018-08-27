/*
ID: stapark1
LANG: C++14
TASK: holstein
*/

#include <fstream>
#include <vector>

using dosage_t = std::vector<int>;

dosage_t minRequirements;
int kNumVitamins, kNumFeeds;
std::vector<dosage_t> feeds;
std::vector<int> bestPath{};

bool isSufficientDosage(dosage_t& dosage) {
  for (std::size_t vitamin = 0; vitamin < kNumVitamins; ++vitamin) {
    if (dosage[vitamin] < minRequirements[vitamin]) return false;
  }
  return true;
}

void findBestCombo(int feedIndex, dosage_t dosage, std::vector<int> path) {
  path.push_back(feedIndex);
  for (std::size_t vitamin = 0; vitamin < kNumVitamins; ++vitamin) {
    dosage[vitamin] += feeds[feedIndex][vitamin];
  }
  if (isSufficientDosage(dosage)) {
    if (path.size() < bestPath.size()) bestPath = path;
    return;
  }
  for (std::size_t nextFeed = feedIndex + 1; nextFeed < kNumFeeds; ++nextFeed) {
    findBestCombo(nextFeed, dosage, path);
  }
}

int main() {
  std::ifstream input("holstein.in");
  std::ofstream output("holstein.out");

  // Read minimum vitamin requirements.
  input >> kNumVitamins;
  for (int i = 0; i < kNumVitamins; ++i) {
    int minRequirement;
    input >> minRequirement;
    minRequirements.push_back(minRequirement);
  }

  // Read feed types.
  input >> kNumFeeds;
  for (int feed = 0; feed < kNumFeeds; ++feed) {
    bestPath.push_back(feed);
    feeds.emplace_back(dosage_t{});
    for (int vitamin = 0; vitamin < kNumVitamins; ++vitamin) {
      int perScoop;
      input >> perScoop;
      feeds.back().push_back(perScoop);
    }
  }

  // Initialize path and dosage variables.
  std::vector<int> path;
  dosage_t dosage;
  for (std::size_t vitamin = 0; vitamin < kNumVitamins; ++vitamin)
    dosage.push_back(0);

  // Iterate through possible feed combinations, trying earlier ones first.
  for (std::size_t feed = 0; feed < kNumFeeds; ++feed) {
    findBestCombo(feed, dosage, path);
  }

  output << bestPath.size();
  for (const int feed : bestPath) output << ' ' << (feed + 1);
  output << std::endl;
  return 0;
}