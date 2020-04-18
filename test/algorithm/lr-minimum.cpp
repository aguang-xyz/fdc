#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

TEST(algorithm, lr_minimum_1) {

  auto F = fds({

    fd(attrs({ 0, 1, 2 }), attrs({ 4 })),
    fd(attrs({ 0 }), attrs({ 0, 2, 5 })),
  });
  
  auto G = fds({

    fd(attrs({ 0, 1 }), attrs({ 4 })),
    fd(attrs({ 0 }), attrs({ 2, 5 })),
  });

  ASSERT_FALSE(is_lrminimum(F));

  ASSERT_EQ(lrminimum(F), G);

  ASSERT_TRUE(is_lrminimum(G));
}

