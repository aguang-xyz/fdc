#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

TEST(algorithm, depend_1) {

  auto F = fds({

    fd(attrs({ "X" }), attrs({ "Y" })),
    fd(attrs({ "X" }), attrs({ "Z" })),
    fd(attrs({ "Y", "Z" }), attrs({ "V" })),
  });

  auto X = attrs({ "X" });
  
  auto Y = attrs({ "X", "Y", "Z", "V", });

  ASSERT_EQ(depend(F, X), Y);
}

