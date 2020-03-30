// 1.5 Equivalent sets of functional dependencies (cover)

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

  auto G = fds({

    fd(X, Y),
    fd(Y, Z),
  });

  cout<<equal(F, G)<<endl;       // Expected to print 1(true).
  cout<<is_cover_of(F, G)<<endl; // Expected to print 1(true).

  return 0;
}
