#include <iostream>

#include "fdc/fdc.hpp"

using namespace std;

using namespace fdc;

int main(int argc, char **argv) {

  fds F = fds({

    fd(attrs({ "A" }), attrs({ "B" })),
    fd(attrs({ "B" }), attrs({ "C" })),
    fd(attrs({ "C" }), attrs({ "A" })),
    fd(attrs({ "A" }), attrs({ "C" })),
  });
 
  fds G = fds({
    
    fd(attrs({ "A" }), attrs({ "B" })),
    fd(attrs({ "B" }), attrs({ "C" })),
  });

  attrs U = union_of(attrs_of(F), attrs_of(G));
 
  cout<<"U = "<<to_str(U)<<endl<<endl;

  cout<<"F = "<<to_str(F)<<endl<<endl;

  cout<<"G = "<<to_str(G)<<endl<<endl;


  cout<<"Closure(U, F) = "<<to_str(closure_of(U, F))<<endl<<endl;
  
  cout<<"Closure(U, G) = "<<to_str(closure_of(U, G))<<endl<<endl;

  cout<<"(F == G) = "<<equal(F, G)<<endl<<endl;

  attrs A = attrs({ "A" });
  attrs B = attrs({ "B" });

  cout<<"(A <-> B under F) = "<<equal(A, B, F)<<endl<<endl;

  return 0;
}
