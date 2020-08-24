#include <ctime>
#include <fstream>
#include <vector>

#include "fdc/fdc.h"
#include "gtest/gtest.h"

using namespace std;
using namespace fdc;

const auto datasets = vector<string>({
    "../../dataset/Complete Data/balance-scale.json",
    "../../dataset/Complete Data/iris.json",
    "../../dataset/Complete Data/letter.json",
    "../../dataset/Complete Data/adult.json",
    "../../dataset/Complete Data/chess.json",
    "../../dataset/Complete Data/nursery.json",
    "../../dataset/Complete Data/abalone.json",
    "../../dataset/Complete Data/lineitem.json",
    "../../dataset/Complete Data/fd_reduced.json",
    "../../dataset/Incomplete Data NullNEQ/hepatitis.json",
    "../../dataset/Incomplete Data NullNEQ/uniprot_512001r_30c.json",
    "../../dataset/Incomplete Data NullNEQ/plista.json",
    "../../dataset/Incomplete Data NullNEQ/breast.json",
    "../../dataset/Incomplete Data NullNEQ/diabetic.json",
    "../../dataset/Incomplete Data NullNEQ/pdbx.json",
    "../../dataset/Incomplete Data NullNEQ/ncvoter.json",
    "../../dataset/Incomplete Data NullNEQ/echo.json",
    "../../dataset/Incomplete Data NullNEQ/flight.json",
    "../../dataset/Incomplete Data NullNEQ/china_weather.json",
    "../../dataset/Incomplete Data NullNEQ/bridges.json",
    "../../dataset/Incomplete Data NullNEQ/horse.json",
    "../../dataset/Incomplete Data NullEQ/ncvoter8060060.json",
    "../../dataset/Incomplete Data NullEQ/ncvoter4000.json",
    "../../dataset/Incomplete Data NullEQ/hepatitis.json",
    "../../dataset/Incomplete Data NullEQ/ncvoter1024000.json",
    "../../dataset/Incomplete Data NullEQ/uniprot_512001r_30c.json",
    "../../dataset/Incomplete Data NullEQ/plista.json",
    "../../dataset/Incomplete Data NullEQ/ncvoter16000.json",
    "../../dataset/Incomplete Data NullEQ/ncvoter64000.json",
    "../../dataset/Incomplete Data NullEQ/breast.json",
    "../../dataset/Incomplete Data NullEQ/diabetic.json",
    "../../dataset/Incomplete Data NullEQ/pdbx.json",
    "../../dataset/Incomplete Data NullEQ/ncvoter256000.json",
    "../../dataset/Incomplete Data NullEQ/ncvoter8000.json",
    "../../dataset/Incomplete Data NullEQ/ncvoter2000.json",
    "../../dataset/Incomplete Data NullEQ/ncvoter.json",
    "../../dataset/Incomplete Data NullEQ/echo.json",
    "../../dataset/Incomplete Data NullEQ/ncvoter512000.json",
    "../../dataset/Incomplete Data NullEQ/flight.json",
    "../../dataset/Incomplete Data NullEQ/china_weather.json",
    "../../dataset/Incomplete Data NullEQ/ncvoter32000.json",
    "../../dataset/Incomplete Data NullEQ/bridges.json",
    "../../dataset/Incomplete Data NullEQ/ncvoter128000.json",
    "../../dataset/Incomplete Data NullEQ/horse.json",
});

/**
 * Sort functional dependencies in ascending order and return the first M
 * functional dependencies.
 */
fds head(const fds &F, const int M) {

  // Copy.
  fds G = fds(F);

  // Sort.
  sort(G.begin(), G.end());

  // Slice.
  return fds(G.begin(), G.begin() + M);
}

/**
 * Calculate the total number of attributes in F.
 */
int calc(const fds &F) {

  int total = 0;

  for (const fd &f : F) {
    total += f.first.size() + f.second.size();
  }

  return total;
}

// Yaml file.
auto yaml = ofstream("../../dataset.analyse.yaml", fstream::out);

#define record(name, algo, N, F)                                               \
  {                                                                            \
    double t0 = clock();                                                       \
    yaml << "       - Name: " << name << endl;                                 \
    yaml << "         Attrs: " << calc(algo(N, F)) << endl;                    \
    yaml << "         Time: " << (clock() - t0) / CLOCKS_PER_SEC << endl;      \
  }

void solve(const string dataset) {

  // The number of attributes.
  int N;

  // Functional dependencies.
  fds F = fds();

  // Open json file.
  ifstream json = ifstream(dataset);

  // Load dataset.
  from_json(json, N, F);

  // Print result.
  yaml << " - Dataset: " << dataset << endl;
  yaml << "   Attrs: " << N << endl;
  yaml << "   Metrics: " << endl;

  for (int pct = 1; pct <= 100; pct++) {

    // Retrieve pct% functional dependencies.
    const fds G = head(F, pct * F.size() / 100);

    yaml << "    - Pct: " << pct << endl;
    yaml << "      Fds: " << G.size() << endl;
    yaml << "      Algos: " << endl;

    record("Non-Redundant", non_redundant, N, G);
    record("Canonical", canonical, N, G);
    record("Minimum", minimum, N, G);
    record("L-Minimum", lminimum, N, G);
    record("LR-Minimum", lrminimum, N, G);
  }
}

TEST(dataset, complete_fd_reduced) {

  // 3573 FDs.
  // solve("../../dataset/Complete Data/fd_reduced.json");

  // 5794 FDs.
  // solve("../../dataset/Incomplete Data NullNEQ/uniprot_512001r_30c.json");
}
