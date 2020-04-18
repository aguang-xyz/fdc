#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

TEST(algorithm, equal_attrs_1) {

  auto F = fds({

    fd(attrs({ 0 }), attrs({ 1 })),
    fd(attrs({ 1 }), attrs({ 2 })),
    fd(attrs({ 2 }), attrs({ 0 })),
  });

  auto X = attrs({ 0 });
  auto Y = attrs({ 1 });

  ASSERT_TRUE(equal(X, Y, F));
}

TEST(algorithm, equal_fds_1) {

  auto F = fds({

    fd(attrs({ 0 }), attrs({ 1 })),
    fd(attrs({ 0 }), attrs({ 2 })),
  });

  auto G = fds({

    fd(attrs({ 0 }), attrs({ 1, 2 })),
  });

  ASSERT_TRUE(equal(F, G));
}

