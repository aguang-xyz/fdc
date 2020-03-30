// 1.3 Closure.

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

  cout<<to_str(closure_of(F))<<endl;

  return 0;
}
