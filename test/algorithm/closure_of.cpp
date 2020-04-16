#include "gtest/gtest.h"
#include "fdc/fdc.h"

#include <fstream>

using namespace std;
using namespace fdc;

TEST(algorithm, closure_of_0) {

  auto F = fds({

    fd(attrs({ "X" }), attrs({ "Y" })),
    fd(attrs({ "X" }), attrs({ "Z" })),
  });

  cout<<to_str(closure_of(F))<<endl;
}

TEST(algorithm, closure_of_1) {

  auto F = fds({

    fd(attrs({ "X" }), attrs({ "Z" })),
    fd(attrs({ "Y" }), attrs({ "Z" })),
  });

  cout<<to_str(closure_of(F))<<endl;
}

TEST(algorithm, closure_of_2) {

  auto F = fds({

    fd(attrs({ "X" }), attrs({ "Y" })),
    fd(attrs({ "X" }), attrs({ "Z" })),
    fd(attrs({ "Y", "Z" }), attrs({ "V" })),
    fd(attrs({ "V" }), attrs({ "X" })),
  });

  cout<<to_str(closure_of(F))<<endl;
}

/*
TEST(algorithm, closure_of_iris) {

  const string inputs[] = {

	 "../../dataset/A/Complete Data/balance-scale.json",
	 "../../dataset/A/Complete Data/chess.json",
	 "../../dataset/A/Complete Data/nursery.json",
	 "../../dataset/A/Complete Data/iris.json",
	 "../../dataset/A/Complete Data/abalone.json",
	 "../../dataset/A/Complete Data/adult.json",
	 "../../dataset/A/Complete Data/letter.json",
	 "../../dataset/A/Complete Data/iris.closure.out.json",
	 "../../dataset/A/Complete Data/lineitem.json",
	 "../../dataset/A/Complete Data/fd_reduced.json"
  };

  const string outputs[] = {

	 "../../dataset/A/Complete Data/balance-scale.out.json",
	 "../../dataset/A/Complete Data/chess.out.json",
	 "../../dataset/A/Complete Data/nursery.out.json",
	 "../../dataset/A/Complete Data/iris.out.json",
	 "../../dataset/A/Complete Data/abalone.out.json",
	 "../../dataset/A/Complete Data/adult.out.json",
	 "../../dataset/A/Complete Data/letter.out.json",
	 "../../dataset/A/Complete Data/iris.closure.out.out.json",
	 "../../dataset/A/Complete Data/lineitem.out.json",
	 "../../dataset/A/Complete Data/fd_reduced.out.json"
  };

	for (int i = 0; i < 10; i++) {

		auto input = ifstream(inputs[i]);
		auto output = ofstream(outputs[i]);

		auto U = attrs();
		auto F = fds();

		from_json(input, U, F);
	 
		cout<<"U = "<<to_str(U)<<endl;
		cout<<"F = "<<to_str(F)<<endl;

		auto closure = closure_of(U, F);

		cout<<"Closure(`"<<inputs[i]<<"`) = "<<to_str(closure)<<endl;

		to_json(output, U, closure);
	}
}
*/
