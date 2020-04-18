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


  bool equal(const attrs &X, const attrs &Y, const fds &F) {

    return is_membership(F, fd(X, Y)) && is_membership(F, fd(Y, X));
  }


  bool equal(const fds &F, const fds &G) {

    for (auto &f : F) {

      if (!is_membership(G, f)) {
        
        return false;
      }
    }

    for (auto &f : G) {

      if (!is_membership(F, f)) {

        return false;
      }
    }

    return true;
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


  fds non_redundant(const fds &F) {

    auto G = fds(F);

    for (auto &f : F) {

      auto H = minus(G, fds({ f }));

      if (is_membership(H, f)) {

        G = H;
      }
    }

    return G;
  }


  bool is_canonical(const fds &F) {

    for (auto &f : F) {

      if (f.second.size() > 1) {

        return false;
      }
    }

    if (is_redundant(F)) {

      return false;
    }

    for (auto &f : F) {

      auto &X = f.first;
      auto &Y = f.second;

      if (X.size() > 0) {

        for (auto &x : X) {

          auto X2 = minus(X, attrs({ x }));

          if (is_membership(F, fd(X2, Y))) {

            return false;
          }
        }
      }
    }

    return true;
  }

  bool is_direct(const fds &F, const fd &f) {

    // 0. Check if \f$ X \to Y \in F^+ \f$.
    if (!is_membership(F, f)) {

      return false;
    }

    const auto &X = f.first;
    const auto &Y = f.second;

    // 1. Find a non-redundant cover for `F`.
    auto G = non_redundant(F);

    // 2.1 Calculate X^+.
    auto D = depend(G, X);

    cout<<"D = "<<to_str(D)<<endl;

    auto EFX = fds();

    // 2.2 Determine ef(X). 
    for (auto &fi : G) {

      // If fi: (V, W), where V \subseteq X^+. 
      if (is_subset_eq(fi.first, D)) {

        // Z \to X \in G^+
        if (is_membership(G, fd(fi.first, X))) {

          EFX.insert(fi);
        }
      }
    }

    // 3. Check if X \to Y \in (F - EF(X))^+.
    return is_membership(minus(G, EFX), f);
  }


  fds minimum(const fds &F) {

    // 1. Find a non-redundant cover for `F`.
    auto G = non_redundant(F);

    // 2. Find all equivalence classes for `G`.
    auto D = vector<attrs>();
    auto ef = vector<set<attrs>>();
    auto EF = vector<fds>();

    for (auto &f : G) {

      auto &X = f.first;

      bool found = false;

      for (int i = 0; i < D.size(); i++) {

        // $ \text{The i-th class} \to X \in F^+ $.
        if (is_subset_eq(X, D[i])) {

          // $ X \to \text{The i-th class} \in F^+ $.
          if (is_membership(G, fd(X, *(ef[i].begin())))) {

            ef[i].insert(X);
            EF[i].insert(f);

            found = true;

            break;
          }
        }
      }

      // Or, append a new class.
      if (!found) {

        D.push_back(depend(G, X));
        ef.push_back(set<attrs>({ X }));
        EF.push_back(fds({ f }));
      }
    }

    // 3. Find pairs $Y1 \to Y2$ and $Z1 \to Z2$, where $Y1$, $Z1$ are
    // equivalent and $Y1$ directly determine $Z1$. Replace them with
    // $Z1 \to Y2Z2$.
    for (int i = 0; i < D.size(); i++) {

			again:
			
				auto G2 = minus(G, EF[i]);
	
				for (auto &y : EF[i]) {
				 
					auto &Y1 = y.first;
					auto &Y2 = y.second;

					auto DY = depend(G2, Y1);

					for (auto &z : EF[i]) {

						if (y == z) continue;

						auto &Z1 = z.first;
						auto &Z2 = z.second;

						if (is_subset_eq(Z1, DY)) {
							
							G.insert(fd(attrs(Z1), union_of(Y2, Z2)));
							G.erase(y);
							G.erase(z);
							
							EF[i].insert(fd(attrs(Z1), union_of(Y2, Z2)));
							EF[i].erase(y);
							EF[i].erase(z);

							goto again;
						}
					}
				}
    }

    return G;
  }


  bool is_minimum(const fds &F) {

    return minimum(F).size() == F.size();
  }
}
