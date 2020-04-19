#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

TEST(algorithm, minimum_1) {

  auto F = fds({

    fd(attrs({ 0 }), attrs({ 1 })),
    fd(attrs({ 0 }), attrs({ 2 })),
  });
  
  auto G = fds({

    fd(attrs({ 0 }), attrs({ 1, 2 })),
  });

  ASSERT_FALSE(is_minimum(3, F));

  ASSERT_EQ(minimum(3, F), G);

  ASSERT_TRUE(is_minimum(3, G));
}

