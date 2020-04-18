#include "gtest/gtest.h"
#include "fdc/fdc.h"

#include <fstream>
#include <cstdio>

using namespace std;
using namespace fdc;

TEST(io, from_json) {

  auto iris = ifstream("../../dataset/Complete Data/iris.json");

  auto U1 = attrs();
  auto F1 = fds();

  fdc::from_json(iris, U1, F1);

  auto U2 = attrs({ 0, 1, 2, 3, 4 });

  auto F2 = fds({
 
    fd(attrs({ 0, 1, 2 }), attrs({ 4 })),
    fd(attrs({ 0, 1, 3 }), attrs({ 4 })),
    fd(attrs({ 0, 2, 3 }), attrs({ 4 })),
    fd(attrs({ 1, 2, 3 }), attrs({ 4 })),
  });

  ASSERT_EQ(U1, U2);
  ASSERT_EQ(F1, F2);
}

TEST(io, to_json) {

  auto U1 = attrs({ 0,1,2,3,4 });

  auto F1 = fds({
 
    fd(attrs({ 0, 1, 2 }), attrs({ 4 })),
    fd(attrs({ 0, 1, 3 }), attrs({ 4 })),
    fd(attrs({ 0, 2, 3 }), attrs({ 4 })),
    fd(attrs({ 1, 2, 3 }), attrs({ 4 })),
  });
 
  string filename = tmpnam(NULL);

  auto tmpOut = ofstream(filename);

  to_json(tmpOut, U1, F1);

  auto U2 = attrs();
  auto F2 = fds();

  auto tmpIn = ifstream(filename);

  from_json(tmpIn, U2, F2);

  ASSERT_EQ(U1, U2);
  ASSERT_EQ(F1, F2);
}
