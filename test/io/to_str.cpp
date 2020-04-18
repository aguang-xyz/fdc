#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

TEST(io, to_str_attr) {

  auto x = attr("X");

  EXPECT_EQ(to_str(x), "X");
}

TEST(io, to_str_attrs) {

  auto X = attrs({ attr("X"), attr("Y") });
  
  EXPECT_EQ(to_str(X), "(X, Y)");
}

TEST(io, to_str_fd) {

  auto f = fd(
      
    attrs({ attr("X") }),
    attrs({ attr("Y") })
  );

  EXPECT_EQ(to_str(f), "(X) -> (Y)");
}

TEST(io, to_str_fds) {

  auto F = fds({
      
    fd(
      attrs({ attr("X") }),
      attrs({ attr("Y") })
    )
  });
 
  EXPECT_EQ(to_str(F), "FDS {\n  (X) -> (Y)\n}");
}
