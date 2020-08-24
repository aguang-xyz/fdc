#include "fdc/fdc.h"
#include "gtest/gtest.h"

using namespace std;
using namespace fdc;

TEST(algorithm, equal_attrs_1) {

  auto F = fds({

      fd(attrs({0}), attrs({1})),
      fd(attrs({1}), attrs({2})),
      fd(attrs({2}), attrs({0})),
  });

  auto X = attrs({0});
  auto Y = attrs({1});

  ASSERT_TRUE(equal(3, F, X, Y));
}

TEST(algorithm, equal_fds_1) {

  // This case:
  //
  //   A -> B     =     A -> BC
  //   A -> C

  auto F = fds({

      fd(attrs({0}), attrs({1})),
      fd(attrs({0}), attrs({2})),
  });

  auto G = fds({

      fd(attrs({0}), attrs({1, 2})),
  });

  ASSERT_TRUE(equal(3, F, G));
}

TEST(algorithm, equal_fds_2) {

  // This case:
  //
  //    A -> B            A -> B
  //   AC -> D      =     A -> C
  //    A -> CD           A -> D

  auto F = fds({

      fd(attrs({0}), attrs({1})),
      fd(attrs({0, 2}), attrs({3})),
      fd(attrs({0}), attrs({2, 3})),
  });

  auto G = fds({

      fd(attrs({0}), attrs({1})),
      fd(attrs({0}), attrs({2})),
      fd(attrs({0}), attrs({3})),
  });

  ASSERT_TRUE(equal(4, F, G));
}

TEST(algorithm, equal_fds_3) {

  // This case:
  //
  //  ABC -> D           AE -> D
  //   BC -> E      =    BC -> E
  //    E -> BC           E -> BC

  auto F = fds({

      fd(attrs({0, 1, 2}), attrs({3})),
      fd(attrs({1, 2}), attrs({4})),
      fd(attrs({4}), attrs({1, 2})),
  });

  auto G = fds({

      fd(attrs({0, 4}), attrs({3})),
      fd(attrs({1, 2}), attrs({4})),
      fd(attrs({4}), attrs({1, 2})),
  });

  ASSERT_TRUE(equal(5, F, G));
}
