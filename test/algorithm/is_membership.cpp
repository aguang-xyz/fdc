#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

TEST(algorithm, is_membership_1) {

  auto F = fds({

    fd(attrs({ "X" }), attrs({ "Y" })),
    fd(attrs({ "X" }), attrs({ "Z" })),
    fd(attrs({ "Y", "Z" }), attrs({ "V" })),
  });

  auto f = fd(attrs({ "X" }), attrs({ "V" }));

  ASSERT_TRUE(is_membership(F, f));
}

TEST(algorithm, is_membership_2) {

  auto F = fds({

    fd(attrs({ "X" }), attrs({ "Y" })),
    fd(attrs({ "X" }), attrs({ "Z" })),
    fd(attrs({ "Y", "Z", "W" }), attrs({ "V" })),
  });

  auto f = fd(attrs({ "X" }), attrs({ "V" }));

  ASSERT_FALSE(is_membership(F, f));
}

TEST(algorithm, is_membership_3) {

  auto F = fds({

    fd(attrs({ "X" }), attrs({ "Y" })),
    fd(attrs({ "X" }), attrs({ "Z" })),
    fd(attrs({ "Y", "Z", "W" }), attrs({ "V" })),
  });

  auto f = fd(attrs({ "X" }), attrs({ "X", "V", "W" }));

  ASSERT_TRUE(is_membership(F, f));
}
