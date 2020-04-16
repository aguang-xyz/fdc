#include "gtest/gtest.h"
#include "fdc/fdc.h"

#include <fstream>

using namespace std;
using namespace fdc;

TEST(algorithm, closure_of_iris) {

  auto iris = ifstream("../../dataset/A/Complete Data/iris.json");

  auto U = attrs();
  auto F = fds();

  from_json(iris, U, F);
 
  cout<<"U = "<<to_str(U)<<endl;
  cout<<"F = "<<to_str(F)<<endl;

  auto closure = closure_of(U, F);

  cout<<"Closure(U, F) = "<<to_str(closure)<<endl;

  auto irisClosure =
    ofstream("../../dataset/A/Complete Data/iris.closure.out.json");

  to_json(irisClosure, U, closure);
}
