#include<vector>
#include<fstream>
#include<ctime>

#include "gtest/gtest.h"
#include "fdc/fdc.h"

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

#define RECORD(desc, exp) { \
  double t0 = clock(); \
  exp; \
  report<<" - Task `"<<desc<<"` runs for "<<\
    (clock() - t0) / CLOCKS_PER_SEC<<" seconds."<<endl; \
}


void solve(string input) {
   
    int N;
    fds F = fds();
    
    ifstream file = ifstream(input);
    
    from_json(file, N, F);

    report<<"Start to solve `"<<input<<"`."<<endl;
    report<<" - "<<N<<" attributes, "<<F.size()<<" functional dependencies."<<endl;

    RECORD("is_membership.", is_membership(N, F, *(F.begin())));
    RECORD("is_redundant.", is_redundant(N, F));
    RECORD("non_redundant.", non_redundant(N, F));
    RECORD("is_canonical.", is_canonical(N, F));
    RECORD("canonical.", canonical(N, F));
    RECORD("is_direct.", is_direct(N, F, *(F.begin())));
    RECORD("minimum.", minimum(N, F));
    RECORD("is_minimum.", is_minimum(N, F));
}

// TEST(dataset, all) {
// 
// 
//   for (int i = 0; i < inputs.size(); i++) {
// 
//     solve(inputs[i]);
//   }
// }

TEST(dataset, specific) {

	solve("../../dataset/Complete Data/fd_reduced.json");
}
