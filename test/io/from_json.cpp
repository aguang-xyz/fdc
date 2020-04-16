#include "gtest/gtest.h"
#include "fdc/fdc.h"

#include <fstream>

using namespace std;
using namespace fdc;

TEST(io, from_json) {

  ifstream abalone;

  abalone.open("../../dataset/A/Complete Data/abalone.json");

  attrs U;
  fds F;

  fdc::from_json(abalone, U, F);
  
  cout<<"U = "<<to_str(U)<<endl;
  cout<<"F = "<<to_str(F)<<endl;
}
