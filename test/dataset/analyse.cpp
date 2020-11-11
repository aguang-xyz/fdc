#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>

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
    auto result = algo(N, F);                                                  \
    sort(result.begin(), result.end());                                        \
    yaml << "       - Name: " << name << endl;                                 \
    yaml << "         Attrs: " << calc(result) << endl;                        \
    yaml << "         FDs: " << result.size() << endl;                         \
    yaml << "         Time: " << (clock() - t0) / CLOCKS_PER_SEC << endl;      \
    yaml.flush();                                                              \
    fprintf(stderr, "%s cover = %s\n", name, to_str(result).c_str());          \
  }

void solve(const string dataset, bool run_mini) {

  // The number of attributes.
  int N;

  // Functional dependencies.
  fds F = fds();

  // Open json file.
  ifstream json = ifstream(dataset);

  // Load dataset.
  from_json(json, N, F);

  sort(F.begin(), F.end());

  fprintf(stderr, "original cover = %s\n", to_str(F).c_str());
  fprintf(stderr, "attrs = %d\n", calc(F));

  // Print result.
  yaml << " - Dataset: " << dataset << endl;
  yaml << "   Attrs: " << N << endl;
  yaml << "   Metrics: " << endl;

  for (int pct = 100, prev_size = -1; pct <= 100; pct++) {

    if (prev_size != (pct * F.size() / 100)) {

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

      if (run_mini) {
        record("Mini", mini, N, G);
        record("Optimal", optimal, N, G);
      }

      prev_size = pct * F.size() / 100;
    }
  }
}

TEST(dataset, complete_fd_reduced) {

  // Slow cases.
  // solve("../../dataset/Complete Data/fd_reduced.json", false);
  // solve("../../dataset/Complete Data/lineitem.json", false);

  // Cases where mini cover can be solve.
  solve("../../dataset/Complete Data/abalone.json", true);
 
  /*
  solve("../../dataset/Complete Data/balance-scale.json", true);
  solve("../../dataset/Complete Data/chess.json", true);
  solve("../../dataset/Complete Data/iris.json", true);
  solve("../../dataset/Complete Data/letter.json", true);
  solve("../../dataset/Complete Data/nursery.json", true);
  solve("../../dataset/Complete Data/adult.json", true);

  auto rest_datasets = vector<string>({
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

  for (auto dataset : rest_datasets) {
    solve(dataset, false);
  }
  */
}
