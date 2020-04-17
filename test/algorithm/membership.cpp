#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

TEST(algorithm, membership_1) {

  auto F = fds({

    fd(attrs({ "X" }), attrs({ "Y" })),
    fd(attrs({ "X" }), attrs({ "Z" })),
    fd(attrs({ "Y", "Z" }), attrs({ "V" })),
  });

  auto f = fd(attrs({ "X" }), attrs({ "V" }));

  ASSERT_TRUE(membership(F, f));
}

TEST(algorithm, membership_2) {

  auto F = fds({

    fd(attrs({ "X" }), attrs({ "Y" })),
    fd(attrs({ "X" }), attrs({ "Z" })),
    fd(attrs({ "Y", "Z", "W" }), attrs({ "V" })),
  });

  auto f = fd(attrs({ "X" }), attrs({ "V" }));

  ASSERT_FALSE(membership(F, f));
}
