// 1.7 Canonical.

#include <iostream>
#include <fdc>

using namespace std;
using namespace fdc;

int main(int argc, char **argv) {

  auto X = attrs({ attr("X") });
  auto Y = attrs({ attr("Y") });
  auto Z = attrs({ attr("Z") });

	auto XY = attrs({ attr("X"), attr("Y") });

  auto F = fds({

    fd(X, Z),
		fd(XY, Z),
  });

  cout<<is_canonical(F)<<endl;       // Expected to print 0(false),
                                     // because X \subset XY and
                                     // XY \to Z \in F.

  return 0;
}
