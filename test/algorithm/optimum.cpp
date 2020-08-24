#include "fdc/fdc.h"
#include "gtest/gtest.h"

using namespace std;
using namespace fdc;

TEST(algorithm, optimum_1) {

  // This case:
  //
  //   AB -> C             AB -> C
  //   AB -> D     -->      C -> D
  //    C -> D

  auto F = fds({

      fd(attrs({0, 1}), attrs({2})),
      fd(attrs({0, 1}), attrs({3})),
      fd(attrs({2}), attrs({3})),
  });

  auto G = fds({

      fd(attrs({2}), attrs({3})),
      fd(attrs({0, 1}), attrs({2})),
  });

  ASSERT_FALSE(is_optimum(4, F));
  ASSERT_EQ(optimum(4, F), G);
  ASSERT_TRUE(is_optimum(4, G));
}

TEST(algorithm, optimum_2) {

  // This case:
  //
  //    A -> B              A -> BCD
  //   AC -> D     -->
  //    A -> CD

  auto F = fds({

      fd(attrs({0}), attrs({1})),
      fd(attrs({0, 2}), attrs({3})),
      fd(attrs({0}), attrs({2, 3})),
  });

  auto G = fds({

      fd(attrs({0}), attrs({1, 2, 3})),
  });

  ASSERT_FALSE(is_optimum(4, F));
  ASSERT_EQ(optimum(4, F), G);
  ASSERT_TRUE(is_optimum(4, G));
}

TEST(algorithm, optimum_3) {

  // This case:
  //
  //   ABC -> D             AE -> D
  //    BC -> E     -->     BC -> E
  //     E -> BC             E -> BC

  // ABC -> D
  //  BC -> E
  //   E -> BC

  auto F = fds({

      fd(attrs({0, 1, 2}), attrs({3})),
      fd(attrs({1, 2}), attrs({4})),
      fd(attrs({4}), attrs({1, 2})),
  });

  auto G = fds({

      fd(attrs({4}), attrs({1, 2})),
      fd(attrs({1, 2}), attrs({4})),
      fd(attrs({0, 4}), attrs({3})),
  });

  ASSERT_TRUE(equal(5, F, G));

  // ASSERT_FALSE(is_optimum(5, F));
  ASSERT_EQ(optimum(5, F), G);
  // ASSERT_TRUE(is_optimum(5, G));
}
