#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

TEST(algorithm, equal_attrs_1) {

  auto F = fds({

    fd(attrs({ "X" }), attrs({ "Y" })),
    fd(attrs({ "Y" }), attrs({ "Z" })),
    fd(attrs({ "Z" }), attrs({ "X" })),
  });

  auto X = attrs({ "X" });
  auto Y = attrs({ "Y" });

  ASSERT_TRUE(equal(X, Y, F));
}

TEST(algorithm, equal_fds_1) {

  auto F = fds({

    fd(attrs({ "X" }), attrs({ "Y" })),
    fd(attrs({ "X" }), attrs({ "Z" })),
  });

  auto G = fds({

    fd(attrs({ "X" }), attrs({ "Y", "Z" })),
  });

  ASSERT_TRUE(equal(F, G));
}

