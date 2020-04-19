#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

TEST(algorithm, is_direct_1) {

  auto F = fds({

    fd(attrs({ 0 }), attrs({ 1 })),
    fd(attrs({ 1 }), attrs({ 2 })),
    fd(attrs({ 2 }), attrs({ 0 })),
    fd(attrs({ 2 }), attrs({ 3 })),
  });

  auto f = fd(attrs({ 0 }), attrs({ 3 }));

  ASSERT_FALSE(is_direct(4, F, f));
}

TEST(algorithm, is_direct_2) {

  auto F = fds({

    fd(attrs({ 0 }), attrs({ 1 })),
    fd(attrs({ 1 }), attrs({ 2 })),
    fd(attrs({ 2 }), attrs({ 0 })),
    fd(attrs({ 0 }), attrs({ 3 })),
  });

  auto f = fd(attrs({ 0 }), attrs({ 0, 1, 2 }));

  ASSERT_FALSE(is_direct(4, F, f));
}

TEST(algorithm, is_direct_3) {

  auto F = fds({

    fd(attrs({ 0 }), attrs({ 1 })),
  });

  auto f = fd(attrs({ 0, 2 }), attrs({ 1, 2 }));

  ASSERT_TRUE(is_direct(3, F, f));
}

// This example is from Maier(1979, p. 333).
TEST(algorithm, is_direct_4) {

  auto F = fds({

    fd(attrs({ 0 }), attrs({ 1 })),
    fd(attrs({ 2 }), attrs({ 3 })),
    fd(attrs({ 0, 2 }), attrs({ 4 })),
  });

  auto f = fd(attrs({ 0, 2 }), attrs({ 1, 3 }));

  ASSERT_TRUE(is_direct(5, F, f));
}
