#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

TEST(algorithm, is_canonical_2) {

  auto F = fds({

    fd(attrs({ 0, 1, 2 }), attrs({ 3 })),
    fd(attrs({ 0 }), attrs({ 1 })),
  });

  auto G = fds({

    fd(attrs({ 0, 2 }), attrs({ 3 })),
    fd(attrs({ 0 }), attrs({ 1 })),
  });

  ASSERT_FALSE(is_canonical(4, F));

  ASSERT_EQ(canonical(4, F), G);

  ASSERT_TRUE(is_canonical(4, G));
}

TEST(algorithm, canonical_2) {

  auto F = fds({

    fd(attrs({ 0 }), attrs({ 1, 2 })),
  });

  auto G = fds({

    fd(attrs({ 0 }), attrs({ 1 })),
    fd(attrs({ 0 }), attrs({ 2 })),
  });

  ASSERT_FALSE(is_canonical(3, F));

  ASSERT_EQ(canonical(3, F), G);
  
  ASSERT_TRUE(is_canonical(3, G));
}
