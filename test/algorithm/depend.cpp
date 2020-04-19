#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

TEST(algorithm, depend_1) {

  auto N = 4;

  auto F = fds({

    fd(attrs({ 0 }), attrs({ 1 })),
    fd(attrs({ 0 }), attrs({ 2 })),
    fd(attrs({ 1, 2 }), attrs({ 3 })),
  });

  auto X = attrs({ 0 });
  
  auto Y = attrs({ 0, 1, 2, 3, });

  bool D[4];

  depend(N, F, X, D);

  ASSERT_TRUE(D[0]);
  ASSERT_TRUE(D[1]);
  ASSERT_TRUE(D[2]);
  ASSERT_TRUE(D[3]);
}

