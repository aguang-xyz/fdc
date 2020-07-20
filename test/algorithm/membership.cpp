#include "fdc/fdc.h"
#include "gtest/gtest.h"

using namespace std;
using namespace fdc;

TEST(algorithm, is_membership_1) {

  auto F = fds({

      fd(attrs({0}), attrs({1})),
      fd(attrs({0}), attrs({2})),
      fd(attrs({1, 2}), attrs({3})),
  });

  auto f = fd(attrs({0}), attrs({3}));

  ASSERT_TRUE(is_membership(4, F, f));
}

TEST(algorithm, is_membership_2) {

  auto F = fds({

      fd(attrs({0}), attrs({1})),
      fd(attrs({0}), attrs({2})),
      fd(attrs({1, 2, 3}), attrs({4})),
  });

  auto f = fd(attrs({0}), attrs({4}));

  ASSERT_FALSE(is_membership(5, F, f));
}

TEST(algorithm, is_membership_3) {

  auto F = fds({

      fd(attrs({0}), attrs({1})),
      fd(attrs({0}), attrs({2})),
      fd(attrs({1, 2, 4}), attrs({3})),
  });

  auto f = fd(attrs({0, 3, 4}), attrs({0}));

  ASSERT_TRUE(is_membership(5, F, f));
}
