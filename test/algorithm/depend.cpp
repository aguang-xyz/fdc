#include "gtest/gtest.h"
#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

TEST(algorithm, depend_1) {

  auto F = fds({

    fd(attrs({ 0 }), attrs({ 1 })),
    fd(attrs({ 0 }), attrs({ 2 })),
    fd(attrs({ 1, 2 }), attrs({ 4 })),
  });

  auto X = attrs({ 0 });
  
  auto Y = attrs({ 0, 1, 2, 4, });

  ASSERT_EQ(depend(F, X), Y);
}

