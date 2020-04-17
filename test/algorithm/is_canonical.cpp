#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

TEST(algorithm, is_canonical_1) {

  // Since $AC \to D \in F^+$, this is not canonical.
  auto F = fds({

    fd(attrs({ "A", "B", "C" }), attrs({ "D" })),
    fd(attrs({ "A" }), attrs({ "B" })),
  });

  ASSERT_FALSE(is_canonical(F));
}
