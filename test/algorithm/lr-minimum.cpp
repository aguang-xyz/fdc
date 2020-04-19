#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

TEST(algorithm, lr_minimum_1) {

  auto F = fds({

    fd(attrs({ 0, 1, 2 }), attrs({ 3 })),
    fd(attrs({ 0 }), attrs({ 0, 2, 4 })),
  });
  
  auto G = fds({

    fd(attrs({ 0, 1 }), attrs({ 3 })),
    fd(attrs({ 0 }), attrs({ 4, 2 })),
  });

  ASSERT_FALSE(is_lrminimum(5, F));

  ASSERT_EQ(lrminimum(5, F), G);

  ASSERT_TRUE(is_lrminimum(5, G));
}

