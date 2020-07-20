#include <ctime>
#include <fstream>
#include <vector>

#include "fdc/fdc.h"
#include "gtest/gtest.h"

using namespace std;
using namespace fdc;

const auto inputs = vector<string>({

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

auto report = ofstream("../../dataset.report.log", fstream::app);

#define RECORDT(desc, exp, sec)                                                \
  {                                                                            \
    double t0 = clock();                                                       \
    exp;                                                                       \
    report << " - Task `" << desc << "` runs for "                             \
           << (sec = (clock() - t0) / CLOCKS_PER_SEC) << " seconds." << endl;  \
  }

#define RECORD(desc, exp)                                                      \
  {                                                                            \
    double t0 = clock();                                                       \
    exp;                                                                       \
    report << " - Task `" << desc << "` runs for "                             \
           << (clock() - t0) / CLOCKS_PER_SEC << " seconds." << endl;          \
  }

void solve(string input) {

  int N;
  fds F = fds();

  ifstream file = ifstream(input);

  from_json(file, N, F);

  report << "Start to solve `" << input << "`." << endl;
  report << " - " << N << " attributes, ";
  report << F.size() << " functional dependencies." << endl;

  bool res_redundant, res_canonical, res_minimum, res_lminimum, res_lrminimum;

  double t_redundant, t_canonical, t_minimum, t_lminimum, t_lrminimum;

  RECORD("is_redundant.", res_redundant = is_redundant(N, F));
  RECORDT("non_redundant.", non_redundant(N, F), t_redundant);

  RECORD("is_canonical.", res_canonical = is_canonical(N, F));
  RECORDT("canonical.", canonical(N, F), t_canonical);

  RECORD("is_minimum.", res_minimum = is_minimum(N, F));
  RECORDT("minimum.", minimum(N, F), t_minimum);

  RECORD("is_lminimum.", res_lminimum = is_lminimum(N, F));
  RECORDT("lminimum.", lminimum(N, F), t_lminimum);

  RECORD("is_lrminimum.", res_lrminimum = is_lrminimum(N, F));
  RECORDT("lrminimum.", lrminimum(N, F), t_lrminimum);

  report << "[csv]" << input << "," << N << "," << F.size() << ","
         << res_redundant << "," << res_canonical << "," << res_minimum << ","
         << res_lminimum << "," << res_lrminimum << "," << t_redundant << ","
         << t_canonical << "," << t_minimum << "," << t_lminimum << ","
         << t_lrminimum << endl;
}

// TEST(dataset, all) {
//
//   for (int i = 0; i < inputs.size(); i++) {
//
//     solve(inputs[i]);
//   }
// }

TEST(dataset, specific) {

  solve("../../dataset/Complete Data/fd_reduced.json");
}
