#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

TEST(algorithm, lr_minimum_1) {

  // F can be minimized to G.

  auto F = fds({

    fd(attrs({ "X", "Y" }), attrs({ "V" })),
    fd(attrs({ "X" }), attrs({ "X", "Z", "W" })),
  });
  
  auto G = fds({

    fd(attrs({ "X", "Y" }), attrs({ "V" })),
    fd(attrs({ "X" }), attrs({ "Z", "W" })),
  });

  ASSERT_FALSE(is_lrminimum(F));

  ASSERT_TRUE(is_lrminimum(G));
}

