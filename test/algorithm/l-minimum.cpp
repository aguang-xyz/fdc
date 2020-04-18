#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

TEST(algorithm, l_minimum_1) {

  auto F = fds({

    fd(attrs({ 0, 1, 2 }), attrs({ 4 })),
    fd(attrs({ 0 }), attrs({ 2 })),
  });
  
  auto G = fds({

    fd(attrs({ 0, 1 }), attrs({ 4 })),
    fd(attrs({ 0 }), attrs({ 2 })),
  });

  ASSERT_FALSE(is_lminimum(F));

  ASSERT_EQ(lminimum(F), G);

  ASSERT_TRUE(is_lminimum(G));
}

