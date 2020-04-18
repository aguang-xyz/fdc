#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

TEST(algorithm, is_canonical_1) {

  auto F = fds({

    fd(attrs({ "A", "B", "C" }), attrs({ "D" })),
    fd(attrs({ "A" }), attrs({ "B" })),
  });

  auto G = fds({

    fd(attrs({ "A", "C" }), attrs({ "D" })),
    fd(attrs({ "A" }), attrs({ "B" })),
  });

  ASSERT_FALSE(is_canonical(F));

  ASSERT_EQ(canonical(F), G);

  ASSERT_TRUE(is_canonical(G));
}

TEST(algorithm, canonical_2) {

  auto F = fds({

    fd(attrs({ "X" }), attrs({ "Y", "Z" })),
  });

  auto G = fds({

    fd(attrs({ "X" }), attrs({ "Y" })),
    fd(attrs({ "X" }), attrs({ "Z" })),
  });

  ASSERT_FALSE(is_canonical(F));

  ASSERT_EQ(canonical(F), G);
  
  ASSERT_TRUE(is_canonical(G));
}
