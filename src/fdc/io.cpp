#include "fdc.h"
#include "json/json.hpp"

namespace fdc {

  using namespace std;

  using json = nlohmann::json;


  string to_str(const attr &x) {

    return to_string(x);
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


   void from_json(const json input, int &N, fds &F) {
 
     F.clear();
 
     N = input["R"].get<int>();
 
     for (auto f : input["fds"]) {
 
       auto X = attrs();
 
       for (auto x : f["lhs"]) {
 
         X.push_back(attr(x.get<int>()));
       }
 
       auto Y = attrs();
 
       for (auto y : f["rhs"]) {
 
         Y.push_back(attr(y.get<int>()));
       }
 
       F.push_back(fd(X, Y));
     }
   }
 
 
   void from_json(const string input, int &N, fds &F) {
 
     from_json(json::parse(input), N, F);
   }
 
 
   void from_json(istream &input, int &N, fds &F) {
 
     from_json(json::parse(input), N, F);
   }
 
 
   void to_json(ostream &output, const int &N, const fds &F) {
 
     json j;
 
     j["R"] = N;
 
     auto fds = vector<map<string, vector<int>>>();
 
     for (auto &f : F) {
 
       auto lhs = vector<int>();
 
       for (attr x : f.first) {
 
         lhs.push_back(x);
       }
       
       auto rhs = vector<int>();
 
       for (attr y : f.second) {
 
         rhs.push_back(y);
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
