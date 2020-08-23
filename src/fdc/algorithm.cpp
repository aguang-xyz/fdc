#include <cstring>
#include <queue>
#include <set>
#include <vector>

#include "fdc.h"

namespace fdc {

using namespace std;

const fd FD_EMPTY = fd(attrs({}), attrs({}));

void depend(const int N, const fds &F, const attrs X, bool D[]) {

  vector<int> attrlist[N];

  int counter[F.size()];

  for (int i = 0; i < F.size(); i++) {

    const fd &f = F[i];

    counter[i] = f.first.size();

    for (const int &x : f.first) {

      attrlist[x].push_back(i);
    }
  }

  memset(D, 0x00, sizeof(bool) * N);

  queue<int> que;

  for (const int &x : X) {

    if (!D[x]) {

      D[x] = true;

      que.push(x);
    }
  }

  for (; que.size() > 0; que.pop()) {

    int x = que.front();

    for (const int &i : attrlist[x]) {

      if (--(counter[i]) == 0) {

        for (const int &y : F[i].second) {

          if (!D[y]) {

            D[y] = true;

            que.push(y);
          }
        }
      }
    }
  }
}

bool is_membership(const int N, const fds &F, const fd &f) {

  bool D[N];

  depend(N, F, f.first, D);

  for (const int &y : f.second) {

    if (!D[y]) {

      return false;
    }
  }

  return true;
}

bool equal(const int N, const fds &F, const attrs &X, const attrs &Y) {

  return is_membership(N, F, fd(X, Y)) && is_membership(N, F, fd(Y, X));
}

bool equal(const int N, const fds &F, const fds &G) {

  for (const fd &f : F) {

    if (!is_membership(N, G, f)) {

      return false;
    }
  }

  for (const fd &f : G) {

    if (!is_membership(N, F, f)) {

      return false;
    }
  }

  return true;
}

bool is_redundant(const int N, const fds &F) {

  fds G = fds(F);

  for (int i = 0; i < G.size(); i++) {

    const fd f = G[i];

    // Assigning G[i] to $\empty \to \empty$ is equivalent to removing G[i],
    // but assigning operating takes less time.
    G[i] = FD_EMPTY;

    if (is_membership(N, G, f)) {

      return true;
    }

    // Recovery G[i].
    G[i] = f;
  }

  return false;
}

fds non_redundant(const int N, const fds &F) {

  fds G = fds(F);

  for (int i = 0; i < G.size();) {

    const fd f = G[i];

    // Assigning G[i] to $\empty \to \empty$ is equivalent to removing G[i],
    // but assigning operating takes less time.
    G[i] = FD_EMPTY;

    if (is_membership(N, G, f)) {

      // Since the erasing operation of vector is linear to the number of
      // elements between the erasing position and the end of the vector,
      // swapping G[i] to the end first can reduce time cost efficiently.
      G[i] = G[G.size() - 1];
      G.erase(G.end() - 1);

    } else {

      G[i++] = f;
    }
  }

  return G;
}

bool is_canonical(const int N, const fds &F) {

  for (const fd &f : F) {

    if (f.second.size() > 1) {

      return false;
    }
  }

  if (is_redundant(N, F)) {

    return false;
  }

  for (const fd &f : F) {

    if (f.first.size() > 1) {

      fd f2 = fd(f);
      attrs &X = f2.first;

      for (int i = 0; i < X.size(); i++) {

        const attr x = X[i];

        X[i] = X[X.size() - 1];
        X.erase(X.end() - 1);

        if (is_membership(N, F, f2)) {

          return false;
        }

        X.push_back(X[i]);
        X[i] = x;
      }
    }
  }

  return true;
}

fds canonical(const int N, const fds &F) {

  fds G = non_redundant(N, F);

  for (fd &f : G) {

    if (f.first.size() > 1) {

      fd f2 = fd(f);
      attrs &X = f2.first;

      for (int i = 0; i < X.size();) {

        const attr x = X[i];

        X[i] = X[X.size() - 1];
        X.erase(X.end() - 1);

        if (!is_membership(N, G, f2)) {

          X.push_back(X[i]);
          X[i++] = x;
        }
      }

      if (X.size() < f.first.size()) {

        f = f2;
      }
    }
  }

  fds H = fds();

  for (const fd &f : G) {
    for (const attr &y : f.second) {

      H.push_back(fd(f.first, attrs({y})));
    }
  }

  return H;
}

bool is_direct(const int N, const fds &F, const fd &f) {

  // 0. Check if \f$ X \to Y \in F^+ \f$.
  if (!is_membership(N, F, f)) {

    return false;
  }

  const attrs &X = f.first;

  // 1. Find a non-redundant cover for `F`.
  fds G = non_redundant(N, F);

  // 2.1 Calculate X^+.
  bool D[N];

  depend(N, G, X, D);

  // 2.2 Determine ef(X).
  bool EFX[G.size()];

  for (int i = 0; i < G.size(); i++) {

    const attrs &Y = G[i].first;

    bool contained = true;

    for (const int &y : Y) {

      if (!D[y]) {

        contained = false;

        break;
      }
    }

    if (contained && is_membership(N, G, fd(Y, X))) {

      EFX[i] = true;

    } else {

      EFX[i] = false;
    }
  }

  // 3. Check if X \to Y \in (F - EF(X))^+.

  fds H = fds();

  for (int i = 0; i < G.size(); i++) {

    if (!EFX[i]) {

      H.push_back(G[i]);
    }
  }

  return is_membership(N, H, f);
}

fds minimum(const int N, const fds &F) {

  // 1. Find a non-redundant cover for `F`.
  fds G = non_redundant(N, F);

  // 2. Find all equivalence classes for `G`.

  // 2.1 Calculate $ X^+ for each X \to Y \in G $.
  bool **D = new bool *[F.size()];

  for (int i = 0; i < F.size(); i++) {

    D[i] = new bool[N];
  }

  for (int i = 0; i < G.size(); i++) {

    depend(N, G, F[i].first, &(D[i][0]));
  }

  // 2.2 Calculate equivalence classes.
  bool **M = new bool *[F.size()];

  for (int i = 0; i < F.size(); i++) {

    M[i] = new bool[F.size()];
  }

  for (int i = 0; i < G.size(); i++) {
    for (int j = 0; j < G.size(); j++) {

      M[i][j] = true;

      if (i != j) {

        for (const int &x : G[j].first) {

          if (!D[i][x]) {

            M[i][j] = false;

            break;
          }
        }
      }
    }
  }

  // 3. Replacing process.
  for (int i = 0; i < G.size(); i++) {

    // Since G[i] has already been merged into another functional dependency,
    // ignore G[i].
    if (G[i].first.size() == 0)
      continue;

    // H is $ F - EF(X) $.
    fds H = fds();

    for (int j = 0; j < G.size(); j++) {

      if (!(M[i][j] && M[j][i])) {

        H.push_back(G[j]);
      }
    }

    // D2 is $ X^+ $ under $ H $.
    bool D2[N];

    depend(N, H, G[i].first, D2);

    for (int j = 0; j < G.size(); j++) {
      if (j != i && G[j].first.size() > 0 && M[i][j] && M[j][i]) {

        bool direct = true;

        for (const int &x : G[j].first) {

          if (!D2[x]) {

            direct = false;

            break;
          }
        }

        if (direct) {

          // Let's say:
          //   G[i]: Y1 \to Y2
          //   G[j]: Z1 \to Z2
          //
          // Since Y1 <-> Z1 and Y1 directly determine Z2, we can replace
          // G[i], G[j] with Z1 \to Y2Z2.

          set<int> Z2;

          copy(G[i].second.begin(), G[i].second.end(), inserter(Z2, Z2.end()));

          copy(G[j].second.begin(), G[j].second.end(), inserter(Z2, Z2.end()));

          G[i] = FD_EMPTY;
          G[j].second = attrs(Z2.begin(), Z2.end());

          break;
        }
      }
    }
  }

  // 4. Since we use two dynamic array D, M, clean up here.
  for (int i = 0; i < F.size(); i++) {

    delete[] D[i];
    delete[] M[i];
  }

  delete[] D;
  delete[] M;

  // 5. Filter the functional dependencies which are already been assigned
  // to FD_EMPTY.
  fds J = fds();

  for (const fd &f : G) {

    if (f.first.size() != 0 && f.second.size() != 0) {

      J.push_back(f);
    }
  }

  return J;
}

bool is_minimum(const int N, const fds &F) {

  return minimum(N, F).size() == F.size();
}

bool is_lminimum(const int N, const fds &F) {

  if (!is_minimum(N, F)) {

    return false;
  }

  for (const fd &f : F) {

    if (f.first.size() > 1) {

      fd f2 = fd(f);
      attrs &X = f2.first;

      for (int i = 0; i < X.size(); i++) {

        const attr x = X[i];

        X[i] = X[X.size() - 1];
        X.erase(X.end() - 1);

        if (is_membership(N, F, f2)) {

          return false;
        }

        X.push_back(X[i]);
        X[i] = x;
      }
    }
  }

  return true;
}

fds lminimum(const int N, const fds &F) {

  fds G = minimum(N, F);

  for (fd &f : G) {

    if (f.first.size() > 1) {

      fd f2 = fd(f);
      attrs &X = f2.first;

      for (int i = 0; i < X.size(); i) {

        const attr x = X[i];

        X[i] = X[X.size() - 1];
        X.erase(X.end() - 1);

        if (!is_membership(N, G, f2)) {

          X.push_back(X[i]);
          X[i++] = x;
        }
      }

      if (X.size() < f.first.size()) {

        f = f2;
      }
    }
  }

  return G;
}

bool is_lrminimum(const int N, const fds &F) {

  if (!is_lminimum(N, F)) {

    return false;
  }

  fds G = fds(F);

  for (fd &f : G) {
    if (f.second.size() > 1) {

      fd f2 = fd(f);
      attrs &Y = f.second;

      for (int i = 0; i < Y.size(); i++) {

        const attr y = Y[i];

        Y[i] = Y[Y.size() - 1];
        Y.erase(Y.end() - 1);

        if (is_membership(N, G, f2)) {

          return false;
        }

        Y.push_back(Y[i]);
        Y[i] = y;
      }
    }
  }

  return true;
}

fds lrminimum(const int N, const fds &F) {

  fds G = lminimum(N, F);

  for (fd &f : G) {
    if (f.second.size() > 1) {

      fd f2 = fd(f);
      attrs &Y = f.second;

      for (int i = 0; i < Y.size();) {

        const attr y = Y[i];

        Y[i] = Y[Y.size() - 1];
        Y.erase(Y.end() - 1);

        if (!is_membership(N, G, f2)) {

          Y.push_back(Y[i]);
          Y[i++] = y;
        }
      }
    }
  }

  return G;
}

bool is_mini(const int N, const fds &F) {

  // TODO

  return false;
}

fds mini(const int N, const fds &F) {

  // TODO

  return fds(F);
}
} // namespace fdc
