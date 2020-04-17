#include <map>
#include <queue>

#include "fdc.h"

namespace fdc {

  using namespace std;


  attrs depend(const fds &F, const attrs &X) {

    // attrlist[x] indicates all the functional dependencies with attribute
    //$ \f$ x \f$ on their left sides.
    auto attrlist = map<attr, set<fd>>();

    // Build attrlist.
    for (auto &f : F) {
      for (auto &x : f.first) {

        if (attrlist.find(x) == attrlist.end()) {

          attrlist[x] = set<fd>();
        }

        attrlist[x].insert(f);
      }
    }

    // depend is a set of attributes found to be functionally dependent on X.
    auto depend = set<attr>();

    // new_depend is a subset of dependend that has not yet been examined.
    auto new_depend = queue<attr>();

    // Initialize$ \f$ depend \f$ and$ \f$ new_depend \f$ .
    for (auto & x : X) {

      depend.insert(x);
      new_depend.push(x);
    }

    // counter[f] indicates the number of attributes on the left side of
    // \f$ f \f$ that have not yet been found to be in depend.
    auto counter = map<fd, int>();

    // Initialize counter.
    for (auto &f : F) {

      counter[f] = f.first.size();
    }

    while (new_depend.size() > 0) {

      auto a = new_depend.front();

      for (auto &f : attrlist[a]) {

        if (--counter[f] == 0) {
         
          for (auto &b : f.second) {

            if (depend.find(b) == depend.end()) {

              depend.insert(b);
              new_depend.push(b);
            }
          }
        }
      }

      new_depend.pop();
    }

    return depend;
  }


  bool is_membership(const fds &F, const fd &f) {

    const auto &X = f.first;
    const auto &Y = f.second;

    const auto &D = depend(F, X);

    return is_subset_eq(Y, D);
  }
 

  bool is_redundant(const fds &F) {

    for (auto &f : F) {

      auto G = minus(F, fds({ f }));

      if (is_membership(G, f)) {

        return true;
      }
    }

    return false;
  }


  fds redundant(const fds &F) {

    auto G = fds(F);

    for (auto &f : F) {

      auto H = minus(G, fds({ f }));

      if (is_membership(H, f)) {

        G = H;
      }
    }

    return G;
  }
}
