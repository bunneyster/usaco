/*
ID: stapark1
LANG: C++14
TASK: holstein
*/

#include <fstream>
#include <vector>

int numVitamins;
int numFeedTypes;
std::vector<int> minRequirements;
std::vector<std::vector<int>> feeds;

bool meetsRequirements(std::vector<bool> feedProfile) {
  std::vector<int> totalNutrition(numVitamins, 0);
  for (int feed = 0; feed < feedProfile.size(); ++feed) {
    if (!feedProfile[feed]) continue;
    for (int vitamin = 0; vitamin < feeds[feed].size(); ++vitamin) {
      totalNutrition[vitamin] += feeds[feed][vitamin];
    }
  }

  for (int vitamin = 0; vitamin < numVitamins; ++vitamin) {
    if (totalNutrition[vitamin] < minRequirements[vitamin]) return false;
  }
  return true;
}

std::vector<std::vector<bool>> scoopVariations(int totalScoops, int remainingScoops, int nextScoop, std::vector<bool> variation) {
  std::vector<std::vector<bool>> results;

  if (remainingScoops == 0) {
    results.emplace_back(variation);
  } else {
    for (int i = nextScoop; i < numFeedTypes; ++i) {
      variation[i] = true;
      std::vector<std::vector<bool>> variations = scoopVariations(totalScoops, remainingScoops - 1, i + 1, variation);
      for (const auto& v : variations) {
        results.emplace_back(v);
      }
      variation[i] = false;
    }
  }

  return results;
}

int main() {
  std::ifstream input("holstein.in");
  std::ofstream output("holstein.out");

  input >> numVitamins;

  for (int i = 0; i < numVitamins; ++i) {
    int minAmount;
    input >> minAmount;
    minRequirements.emplace_back(minAmount);
  }

  input >> numFeedTypes;

  for (int feed = 0; feed < numFeedTypes; ++feed) {
    feeds.emplace_back(std::vector<int> {});
    for (int vitamin = 0; vitamin < numVitamins; ++vitamin) {
      int amount;
      input >> amount;
      feeds.back().emplace_back(amount);
    }
  }

  for (int numScoops = 1; numScoops < numFeedTypes + 1; ++numScoops) {
    std::vector<bool> blankProfile(numFeedTypes, 0);
    std::vector<std::vector<bool>> profiles = scoopVariations(numScoops, numScoops, 0, blankProfile);
    for (const auto& profile : profiles) {
      if (meetsRequirements(profile)) {
        output << numScoops;
        for (int feed = 0; feed < numFeedTypes; ++feed) {
          if (profile[feed]) output << ' ' << (feed + 1);
        }
        output << std::endl;
        return 0;
      }
    }
  }


  return 0;
}