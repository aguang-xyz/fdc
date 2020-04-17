#include "fdc.h"

namespace fdc {

  using namespace std;

  // Convert an attribute `x` to a string.
  string to_str(const attr &x) {

    return (string) x;
  }

  // Convert a set of attributes `X` to a string.
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

  // Convert a set of functional depdency `f` to a string.
  string to_str(const fd &f) {

    return to_str(f.first) + " -> " + to_str(f.second);
  }

  // Convert a set of functional dependencies `F` to a string.
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

  // Get all attributes of a given functional dependency set `F`.
  attrs attrs_of(const fds &F) {

    attrs ret = {};

    for (fd f : F) {

      for (attr x : f.first) {

        ret.insert(x);
      }

      for (attr x : f.second) {

        ret.insert(x);
      }
    }

    return ret;
  }

  // Get all subsets of a given set attributes `X`.
  set<attrs> subsets_of(const attrs &X) {

    auto subsets = set<attrs>();

    auto q_set = queue<attrs>({ attrs() });
    auto q_itr = queue<attrs::iterator>({ X.begin() });
 
    while (!q_set.empty()) {

      auto expanding_set = q_set.front();
      auto expanding_itr = q_itr.front();

      if (expanding_itr != X.end()) {

        auto next_set0 = attrs(expanding_set);

        q_set.push(next_set0);
        q_itr.push(next(expanding_itr));
        
        auto next_set1 = attrs(expanding_set);

        next_set1.insert(*expanding_itr);

        q_set.push(next_set1);
        q_itr.push(next(expanding_itr));

      } else {

        if (!expanding_set.empty()) {

          subsets.insert(expanding_set);
        }
      }

      q_set.pop();
      q_itr.pop();
    }

    return subsets;
  }

  // Get all subsets of a given set of functional dependencies `F`.
  set<fds> subsets_of(const fds &F) {

    auto subsets = set<fds>();

    auto q_set = queue<fds>({ fds() });
    auto q_itr = queue<fds::iterator>({ F.begin() });
 
    while (!q_set.empty()) {

      auto expanding_set = q_set.front();
      auto expanding_itr = q_itr.front();

      if (expanding_itr != F.end()) {

        auto next_set0 = fds(expanding_set);

        q_set.push(next_set0);
        q_itr.push(next(expanding_itr));
        
        auto next_set1 = fds(expanding_set);

        next_set1.insert(*expanding_itr);

        q_set.push(next_set1);
        q_itr.push(next(expanding_itr));

      } else {

        if (!expanding_set.empty()) {

          subsets.insert(expanding_set);
        }
      }

      q_set.pop();
      q_itr.pop();
    }

    return subsets;
  }


  // Get the closure of a given set of functional depdencies `F`. It is an
  // implementation of Armstrong's Axioms.
  fds closure_of(const fds &F) {

    return closure_of(attrs_of(F), F);
  }

  // Get the closure of a given set of functional depdencies `F` under a
  // given set of attributes, universe `U`. It is an implementation of
  // Armstrong's Axioms.
  fds closure_of(const attrs &U, const fds &F) {

    // Closure.
    auto closure = fds(F);

    // 1. Reflexivity rule.
    //
    // $$
    //   \forall X \subseteq U,
    //     X \to X \in F^+
    // $$
    for (auto X : subsets_of(U)) {

      closure.insert(fd(X, X));
    }

    // Expanding loop.
    for (bool expanding = true; expanding; ) {

      expanding = false;

      // 2. Projectivity rule.
      //
      // $$
      //   \forall X \to YZ \in F^+,
      //   X \to Y \in F^+
      // $$
      for (auto f : closure) {

        auto X = f.first, YZ = f.second;

        for (auto Y : subsets_of(YZ)) {

          auto f = fd(X, Y);

          if (closure.find(f) == closure.end()) {

            closure.insert(f);

            expanding = true;
          }
        }
      } // End of rule 2.

      // 3. Accumulation rule.
      //
      // $$
      //   \forall X \to YZ \in F^+ \land Z \to VW \in F^+,
      //   X \to YZV \in F^+
      // $$
      for (auto f1 : closure) {

        auto X = f1.first, YZ = f1.second;

        for (auto f2 : closure) {

          auto Z = f2.first, VW = f2.second;

          if (is_subset_eq(Z, YZ)) {

            for (auto V : subsets_of(VW)) {

              auto f = fd(X, union_of(YZ, V));

              if (closure.find(f) == closure.end()) {

                closure.insert(f);

                expanding = true;
              }
            }
          }
        }
      } // End of rule 3.

    } // End of expanding loop.

    return closure;
  }


  // Check if a given set of functional dependencies `F` is a cover of
  // another given set of functional dependencies `G`.
  bool is_cover_of(const fds &F, const fds &G) {

    return equal(F, G);
  }
}
