#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

TEST(algorithm, lminimum_1) {

  // F can be minimized to G.

  auto F = fds({

    fd(attrs({ "X", "Y", "Z" }), attrs({ "V" })),
    fd(attrs({ "X" }), attrs({ "Z" })),
  });
  
  auto G = fds({

    fd(attrs({ "X", "Y" }), attrs({ "V" })),
    fd(attrs({ "X" }), attrs({ "Z" })),
  });

  ASSERT_FALSE(is_lminimum(F));

  ASSERT_EQ(lminimum(F), G);

  ASSERT_TRUE(is_lminimum(G));
}

