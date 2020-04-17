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
}
