#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

TEST(algorithm, is_direct_1) {

  auto F = fds({

    fd(attrs({ "X" }), attrs({ "Y" })),
    fd(attrs({ "Y" }), attrs({ "Z" })),
    fd(attrs({ "Z" }), attrs({ "X" })),
    fd(attrs({ "Z" }), attrs({ "V" })),
  });

  auto f = fd(attrs({ "X" }), attrs({ "V" }));

  ASSERT_FALSE(is_direct(F, f));
}

TEST(algorithm, is_direct_2) {

  auto F = fds({

    fd(attrs({ "X" }), attrs({ "Y" })),
    fd(attrs({ "Y" }), attrs({ "Z" })),
    fd(attrs({ "Z" }), attrs({ "X" })),
    fd(attrs({ "X" }), attrs({ "V" })),
  });

  auto f = fd(attrs({ "X" }), attrs({ "X", "Y", "Z" }));

  ASSERT_FALSE(is_direct(F, f));
}

TEST(algorithm, is_direct_3) {

  auto F = fds({

    fd(attrs({ "X" }), attrs({ "Y" })),
  });

  auto f = fd(attrs({ "X", "Z" }), attrs({ "Y", "Z" }));

  ASSERT_TRUE(is_direct(F, f));
}

// This example is from Maier(1979, p. 333).
TEST(algorithm, is_direct_4) {

  auto F = fds({

    fd(attrs({ "A" }), attrs({ "B" })),
    fd(attrs({ "C" }), attrs({ "D" })),
    fd(attrs({ "A", "C" }), attrs({ "E" })),
  });

  auto f = fd(attrs({ "A", "C" }), attrs({ "B", "D" }));

  ASSERT_TRUE(is_direct(F, f));
}
