#include "fdc.h"
#include "json/json.hpp"

namespace fdc {

  using namespace std;

  using json = nlohmann::json;


  string to_str(const attr &x) {

    return (string) x;
  }


  string to_str(const attrs &X) {

    bool first = true;
    
    string str = "(";

    for (auto x : X) {

      if (!first) {

        str += ", ";
      }

      str += to_str(x);

      first = false;
    }

    str += ")";

    return str;
  }


  string to_str(const fd &f) {

    return to_str(f.first) + " -> " + to_str(f.second);
  }


  string to_str(const fds &F) {

    bool first = true;
    
    string str = "FDS {";

    for (auto f : F) {

      str += "\n  " + to_str(f);

      first = false;
    }

    if (!first) {

      str += "\n";
    }

    str += "}";

    return str;
  }


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


  void from_json(const string input, attrs &U, fds &F) {

    from_json(json::parse(input), U, F);
  }


  void from_json(istream &input, attrs &U, fds &F) {

    from_json(json::parse(input), U, F);
  }


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
