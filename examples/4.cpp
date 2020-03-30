// 1.4 Equivalent sets of attributes.

#include <iostream>
#include <fdc>

using namespace std;
using namespace fdc;

int main(int argc, char **argv) {

  auto X = attrs({ attr("X") });
  auto Y = attrs({ attr("Y") });
  auto Z = attrs({ attr("Z") });

  auto F = fds({

    fd(X, Y),
    fd(Y, Z),
    fd(Z, X)
  });

  cout<<equal(X, Y, F)<<endl; // Expected to print 1(true).

  return 0;
}
