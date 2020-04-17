#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

TEST(algorithm, minimum_1) {

  auto F = fds({

    fd(attrs({ "X" }), attrs({ "Y" })),
    fd(attrs({ "X" }), attrs({ "Z" })),
  });
 
  auto G = fds({

    fd(attrs({ "X" }), attrs({ "Y", "Z" })),
  });

  ASSERT_EQ(minimum(F), G);
}

