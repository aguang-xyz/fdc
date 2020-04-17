#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

TEST(algorithm, is_minimum_1) {

  // Since $X \to YZ$ is minimum, this is not minimum.
  auto F = fds({

    fd(attrs({ "X" }), attrs({ "Y" })),
    fd(attrs({ "X" }), attrs({ "Z" })),
  });

  ASSERT_FALSE(is_minimum(F));
}

