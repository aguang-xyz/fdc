#include "fdc.h"
#include "json/json.hpp"

namespace fdc {

  using namespace std;

  using json = nlohmann::json;

  // Convert a json `input` into a set of attributes `U` and a set of
  // functional dependencies `F`.
  //
  // The json `input` is expected to be under the structure below:
  //
  // {
  //   "R": Integer,
  //   "fds": [
  //     {
  //        "lhs": [ Integer ],
  //        "rhs": [ Integer ]
  //     }
  //   ]
  // }
  void from_json(const json input, attrs &U, fds &F) {

    U.clear();
    F.clear();

    const int R = input["R"].get<int>();

    for (auto x = 0; x < R; x++) {

      U.insert(attr(to_string(x)));
    }

    for (auto f : input["fds"]) {

      auto X = attrs();

      for (auto x : f["lhs"]) {

        X.insert(attr(to_string(x.get<int>())));
      }

      auto Y = attrs();

      for (auto y : f["rhs"]) {

        Y.insert(attr(to_string(y.get<int>())));
      }

      F.insert(fd(X, Y));
    }
  }

  // Parse a json string `input` into a set of attributes `U` and a set of
  // functional dependencies `F`
  void from_json(const string input, attrs &U, fds &F) {

    from_json(json::parse(input), U, F);
  }

  // Parse a input stream `input` into a set of attributes `U` and a set of
  // functional dependencies `F`
  void from_json(istream &input, attrs &U, fds &F) {

    from_json(json::parse(input), U, F);
  }
}
