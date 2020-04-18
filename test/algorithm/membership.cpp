#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

TEST(algorithm, is_membership_1) {

  auto F = fds({

    fd(attrs({ 0 }), attrs({ 1 })),
    fd(attrs({ 0 }), attrs({ 2 })),
    fd(attrs({ 1, 2 }), attrs({ 4 })),
  });

  auto f = fd(attrs({ 0 }), attrs({ 4 }));

  ASSERT_TRUE(is_membership(F, f));
}

TEST(algorithm, is_membership_2) {

  auto F = fds({

    fd(attrs({ 0 }), attrs({ 1 })),
    fd(attrs({ 0 }), attrs({ 2 })),
    fd(attrs({ 1, 2, 5 }), attrs({ 4 })),
  });

  auto f = fd(attrs({ 0 }), attrs({ 4 }));

  ASSERT_FALSE(is_membership(F, f));
}

TEST(algorithm, is_membership_3) {

  auto F = fds({

    fd(attrs({ 0 }), attrs({ 1 })),
    fd(attrs({ 0 }), attrs({ 2 })),
    fd(attrs({ 1, 2, 5 }), attrs({ 4 })),
  });

  auto f = fd(attrs({ 0, 4, 5 }), attrs({ 0 }));

  ASSERT_TRUE(is_membership(F, f));
}
