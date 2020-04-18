#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

TEST(algorithm, lr_minimum_1) {

  auto F = fds({

    fd(attrs({ "X", "Y", "Z" }), attrs({ "V" })),
    fd(attrs({ "X" }), attrs({ "X", "Z", "W" })),
  });
  
  auto G = fds({

    fd(attrs({ "X", "Y" }), attrs({ "V" })),
    fd(attrs({ "X" }), attrs({ "Z", "W" })),
  });

  ASSERT_FALSE(is_lrminimum(F));

  ASSERT_EQ(lrminimum(F), G);

  ASSERT_TRUE(is_lrminimum(G));
}

