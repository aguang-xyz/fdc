#include "fdc.h"

namespace fdc {

  using namespace std;


  attrs minus(const attrs &X, const attrs &Y) {

    auto ret = attrs();

    for (auto & x : X) {

      if (Y.find(x) == Y.end()) {

        ret.insert(x);
      }
    }

    return ret;
  }


  fds minus(const fds &X, const fds &Y) {

    auto ret = fds();

    for (auto & x : X) {

      if (Y.find(x) == Y.end()) {

        ret.insert(x);
      }
    }

    return ret;
  }


  bool is_subset_eq(const attrs &X, const attrs &Y) {

    for (auto &x : X) {

      if (Y.find(x) == Y.end()) {

        return false;
      }
    }

    return true;
  }


  bool is_subset_eq(const fds &X, const fds &Y) {

    for (auto &x : X) {

      if (Y.find(x) == Y.end()) {

        return false;
      }
    }

    return true;
  }


	attrs union_of(const attrs &X, const attrs &Y) {
	
	  auto res = attrs();
	
	  for (auto x : X) {
	
	    res.insert(x);
	  }
	
	  for (auto y : Y) {
	
	    res.insert(y);
	  }
	
	  return res;
	}
}
