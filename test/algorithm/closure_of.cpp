#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

TEST(algorithm, closure_of_1) {

  fds F = fds({

    fd(attrs({ "X" }), attrs({ "Y" })),
    fd(attrs({ "X" }), attrs({ "Z" })),
  });
  
  cout<<"Closure(U, F) = "<<to_str(closure_of(F))<<endl;
}

TEST(algorithm, closure_of_2) {

  fds F = fds({

    fd(attrs({ "X" }), attrs({ "Y" })),
    fd(attrs({ "Y" }), attrs({ "Z" })),
  });
  
  cout<<"Closure(U, F) = "<<to_str(closure_of(F))<<endl;
}
