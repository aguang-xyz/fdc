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

  // Convert given set of attributes `U` and given set of functional
  // dependencies `F` to json string and write it into output.
  void to_json(ostream &output, const attrs &U, const fds &F) {

    json j;

    j["R"] = U.size();

    auto fds = vector<map<string, vector<int>>>();

    for (auto &f : F) {

      auto lhs = vector<int>();

      for (attr x : f.first) {

        lhs.push_back(distance(U.begin(), U.find(x)));
      }
      
      auto rhs = vector<int>();

      for (attr y : f.second) {

        rhs.push_back(distance(U.begin(), U.find(y)));
      }

      auto fd = map<string, vector<int>>();

      fd["lhs"] = lhs;
      fd["rhs"] = rhs;

      fds.push_back(fd);
    }

    j["fds"] = fds;

    output<<j.dump(2)<<endl;
  }
}
