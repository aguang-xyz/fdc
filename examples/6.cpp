// 1.6 Non-redundant.

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
    fd(X, Z)
  });

  cout<<is_non_redundant(F)<<endl;       // Expected to print 0(false),
                                         // because { X -> Y, Y -> Z } is a
                                         // possible subset of F.

  return 0;
}
