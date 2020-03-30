// 1.2 Functional dependencies & sets of functional dependencies.

#include <iostream>
#include <fdc>

using namespace std;
using namespace fdc;

int main(int argc, char **argv) {
 
  auto X = attrs({ attr("X") });
  auto Y = attrs({ attr("Y") });

  auto f = fd(X, Y);
  auto F = fds({ f });
  
  cout<<"f = "<<to_str(f)<<endl;
  cout<<"F = "<<to_str(F)<<endl;

  return 0;
}
