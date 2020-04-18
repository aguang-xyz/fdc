#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

TEST(algorithm, is_redundant_1) {

  auto F = fds({

    fd(attrs({ "X" }), attrs({ "Y" })),
    fd(attrs({ "X" }), attrs({ "Z" })),
  });

  ASSERT_FALSE(is_redundant(F));
}

TEST(algorithm, is_redundant_2) {

  auto F = fds({

    fd(attrs({ "X" }), attrs({ "Y" })),
    fd(attrs({ "X" }), attrs({ "Z" })),
    fd(attrs({ "Y" }), attrs({ "Z" })),
  });

  ASSERT_TRUE(is_redundant(F));
}

TEST(algorithm, non_redundant_1) {

  auto F = fds({

    fd(attrs({ "X" }), attrs({ "Y" })),
    fd(attrs({ "X" }), attrs({ "Z" })),
    fd(attrs({ "Y" }), attrs({ "Z" })),
  });

  auto G = fds({

    fd(attrs({ "X" }), attrs({ "Y" })),
    fd(attrs({ "Y" }), attrs({ "Z" })),
  });


  ASSERT_EQ(non_redundant(F), G);
}
