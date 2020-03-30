#include <iostream>
#include <fdc.hpp>

using namespace std;
using namespace fdc;

int main(int argc, char **argv) {
  
  auto x = attr("X");
  auto X = attrs({ attr("X"), attr("Y") });

  cout<<"x = "<<to_str(x)<<endl;
  cout<<"X = "<<to_str(X)<<endl;

  return 0;
}
