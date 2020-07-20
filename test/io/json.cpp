#include "fdc/fdc.h"
#include "gtest/gtest.h"

#include <cstdio>
#include <fstream>

using namespace std;
using namespace fdc;

TEST(io, from_json) {

  auto iris = ifstream("../../dataset/Complete Data/iris.json");

  int N;

  auto F1 = fds();

  fdc::from_json(iris, N, F1);

  auto F2 = fds({

      fd(attrs({0, 1, 2}), attrs({4})),
      fd(attrs({0, 1, 3}), attrs({4})),
      fd(attrs({0, 2, 3}), attrs({4})),
      fd(attrs({1, 2, 3}), attrs({4})),
  });

  ASSERT_EQ(N, 5);
  ASSERT_EQ(F1, F2);
}

TEST(io, to_json) {

  auto N1 = 5;

  auto F1 = fds({

      fd(attrs({0, 1, 2}), attrs({4})),
      fd(attrs({0, 1, 3}), attrs({4})),
      fd(attrs({0, 2, 3}), attrs({4})),
      fd(attrs({1, 2, 3}), attrs({4})),
  });

  string filename = tmpnam(NULL);

  auto tmpOut = ofstream(filename);

  to_json(tmpOut, N1, F1);

  int N2;

  auto F2 = fds();

  auto tmpIn = ifstream(filename);

  from_json(tmpIn, N2, F2);

  ASSERT_EQ(N1, N2);
  ASSERT_EQ(F1, F2);
}
