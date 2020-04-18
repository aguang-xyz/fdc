#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

TEST(io, to_str_attr) {

  auto x = attr(0);

  EXPECT_EQ(to_str(x), "0");
}

TEST(io, to_str_attrs) {

  auto X = attrs({ attr(0), attr(1) });
  
  EXPECT_EQ(to_str(X), "(0, 1)");
}

TEST(io, to_str_fd) {

  auto f = fd(
      
    attrs({ attr(0) }),
    attrs({ attr(1) })
  );

  EXPECT_EQ(to_str(f), "(0) -> (1)");
}

TEST(io, to_str_fds) {

  auto F = fds({
      
    fd(
      attrs({ attr(0) }),
      attrs({ attr(1) })
    )
  });
 
  EXPECT_EQ(to_str(F), "FDS {\n  (0) -> (1)\n}");
}
