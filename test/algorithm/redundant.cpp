#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

TEST(algorithm, is_redundant_1) {

  auto F = fds({

    fd(attrs({ 0 }), attrs({ 1 })),
    fd(attrs({ 0 }), attrs({ 2 })),
  });

  ASSERT_FALSE(is_redundant(F));
}

TEST(algorithm, is_redundant_2) {

  auto F = fds({

    fd(attrs({ 0 }), attrs({ 1 })),
    fd(attrs({ 0 }), attrs({ 2 })),
    fd(attrs({ 1 }), attrs({ 2 })),
  });

  ASSERT_TRUE(is_redundant(F));
}

TEST(algorithm, non_redundant_1) {

  auto F = fds({

    fd(attrs({ 0 }), attrs({ 1 })),
    fd(attrs({ 0 }), attrs({ 2 })),
    fd(attrs({ 1 }), attrs({ 2 })),
  });

  auto G = fds({

    fd(attrs({ 0 }), attrs({ 1 })),
    fd(attrs({ 1 }), attrs({ 2 })),
  });


  ASSERT_EQ(non_redundant(F), G);
}
