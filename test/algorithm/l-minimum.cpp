#include "fdc/fdc.h"
#include "gtest/gtest.h"

using namespace std;
using namespace fdc;

TEST(algorithm, l_minimum_1) {

  auto F = fds({

      fd(attrs({0, 1, 2}), attrs({3})),
      fd(attrs({0}), attrs({2})),
  });

  auto G = fds({

      fd(attrs({0, 1}), attrs({3})),
      fd(attrs({0}), attrs({2})),
  });

  ASSERT_FALSE(is_lminimum(4, F));

  ASSERT_EQ(lminimum(4, F), G);

  ASSERT_TRUE(is_lminimum(4, G));
}
