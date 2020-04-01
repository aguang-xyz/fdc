#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

TEST(basic, attr) {

  auto x = attr("X");

  EXPECT_EQ(to_str(x), "X");
}

TEST(basic, attrs) {

  auto X = attrs({ attr("X"), attr("Y") });
  
  EXPECT_EQ(to_str(X), "(X, Y)");
}

TEST(basic, fd) {

  auto f = fd(
      
    attrs({ attr("X") }),
    attrs({ attr("Y") })
  );

  EXPECT_EQ(to_str(f), "(X) -> (Y)");
}

TEST(basic, fds) {

  auto F = fds({
      
    fd(
      attrs({ attr("X") }),
      attrs({ attr("Y") })
    )
  });
 
  EXPECT_EQ(to_str(F), "FDS {\n  (X) -> (Y)\n}");
}
