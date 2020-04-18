#include<vector>
#include<fstream>
#include<ctime>

#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

const auto inputs = vector<string>({

	"../../dataset/A/Complete Data/balance-scale.json",
	"../../dataset/A/Complete Data/iris.json",
	"../../dataset/A/Complete Data/letter.json",
	"../../dataset/A/Complete Data/adult.json",
	"../../dataset/A/Complete Data/chess.json",
	"../../dataset/A/Complete Data/nursery.json",
	"../../dataset/A/Complete Data/abalone.json",
	"../../dataset/A/Complete Data/lineitem.json",
	"../../dataset/A/Complete Data/fd_reduced.json",
	"../../dataset/A/Incomplete Data NullNEQ/hepatitis.json",
	"../../dataset/A/Incomplete Data NullNEQ/uniprot_512001r_30c.json",
	"../../dataset/A/Incomplete Data NullNEQ/plista.json",
	"../../dataset/A/Incomplete Data NullNEQ/breast.json",
	"../../dataset/A/Incomplete Data NullNEQ/diabetic.json",
	"../../dataset/A/Incomplete Data NullNEQ/pdbx.json",
	"../../dataset/A/Incomplete Data NullNEQ/ncvoter.json",
	"../../dataset/A/Incomplete Data NullNEQ/echo.json",
	"../../dataset/A/Incomplete Data NullNEQ/flight.json",
	"../../dataset/A/Incomplete Data NullNEQ/china_weather.json",
	"../../dataset/A/Incomplete Data NullNEQ/bridges.json",
	"../../dataset/A/Incomplete Data NullNEQ/horse.json",
	"../../dataset/A/Incomplete Data NullEQ/ncvoter8060060.json",
	"../../dataset/A/Incomplete Data NullEQ/ncvoter4000.json",
	"../../dataset/A/Incomplete Data NullEQ/hepatitis.json",
	"../../dataset/A/Incomplete Data NullEQ/ncvoter1024000.json",
	"../../dataset/A/Incomplete Data NullEQ/uniprot_512001r_30c.json",
	"../../dataset/A/Incomplete Data NullEQ/plista.json",
	"../../dataset/A/Incomplete Data NullEQ/ncvoter16000.json",
	"../../dataset/A/Incomplete Data NullEQ/ncvoter64000.json",
	"../../dataset/A/Incomplete Data NullEQ/breast.json",
	"../../dataset/A/Incomplete Data NullEQ/diabetic.json",
	"../../dataset/A/Incomplete Data NullEQ/pdbx.json",
	"../../dataset/A/Incomplete Data NullEQ/ncvoter256000.json",
	"../../dataset/A/Incomplete Data NullEQ/ncvoter8000.json",
	"../../dataset/A/Incomplete Data NullEQ/ncvoter2000.json",
	"../../dataset/A/Incomplete Data NullEQ/ncvoter.json",
	"../../dataset/A/Incomplete Data NullEQ/echo.json",
	"../../dataset/A/Incomplete Data NullEQ/ncvoter512000.json",
	"../../dataset/A/Incomplete Data NullEQ/flight.json",
	"../../dataset/A/Incomplete Data NullEQ/china_weather.json",
	"../../dataset/A/Incomplete Data NullEQ/ncvoter32000.json",
	"../../dataset/A/Incomplete Data NullEQ/bridges.json",
	"../../dataset/A/Incomplete Data NullEQ/ncvoter128000.json",
	"../../dataset/A/Incomplete Data NullEQ/horse.json",
});

#define RECORD(exp, sec) { \
  double t0 = clock(); \
  exp; \
  sec = (clock() - t0) / CLOCKS_PER_SEC; \
}

TEST(dataset, a_minimum) {

  auto report = ofstream("../../a.report.yaml");

  for (int i = 0; i < inputs.size(); i++) {

    auto input = inputs[i];

    auto U = attrs();
    auto F = fds();
    
    auto file = ifstream(input);
    
    from_json(file, U, F);

    report<<input<<","<<U.size()<<","<<F.size()<<",";

    bool is_minimum_ret;
    double is_minimum_sec;

    RECORD(is_minimum_ret = is_minimum(F), is_minimum_sec);
    report<<is_minimum_ret<<","<<is_minimum_sec<<endl;
  }
}
