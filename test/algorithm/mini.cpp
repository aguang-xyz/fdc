#include "fdc/fdc.h"
#include "gtest/gtest.h"

using namespace std;
using namespace fdc;

TEST(algorithm, mini_1) {

  auto F = fds({

      fd(attrs({0, 1}), attrs({2})),
      fd(attrs({0, 1}), attrs({3})),
      fd(attrs({2}), attrs({3})),
  });

  auto G = fds({

      fd(attrs({0, 1}), attrs({2})),
      fd(attrs({2}), attrs({3})),
  });

  ASSERT_FALSE(is_mini(4, F));
  ASSERT_EQ(mini(4, F), G);
  ASSERT_TRUE(is_mini(4, G));
}
