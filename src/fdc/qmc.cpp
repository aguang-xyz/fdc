#include <queue>
#include <set>

#include "fdc.h"

namespace fdc {

using namespace std;

struct qmc_reduce_state {

  // Related input expression ids.
  set<int> ids;

  // Reduced expression.
  bool_expr expr;

  friend bool operator<(const qmc_reduce_state &x, const qmc_reduce_state &y) {
    return x.expr < y.expr;
  }
};

struct qmc_search_state {

  // Covered input expression ids.
  set<int> ids;

  // Combined states.
  set<qmc_reduce_state> states;

  static int count_attrs(const qmc_search_state &x) {

    int count = 0;

    for (auto state : x.states) {
      for (auto c : state.expr) {
        if (c == '0' || c == '1') {
          count++;
        }
      }
    }

    return count;
  }

  friend bool operator<(const qmc_search_state &x, const qmc_search_state &y) {

    if (x.states.size() < y.states.size()) {
      return true;
    }

    if (x.states.size() > y.states.size()) {
      return false;
    }

    return count_attrs(x) < count_attrs(y);
  }

  friend bool operator>(const qmc_search_state &x, const qmc_search_state &y) {
    return y < x;
  }
};

bool_exprs qmc_non_redundant(bool_exprs input_exprs) {

  set<bool_expr> s;

  bool_exprs exprs;

  for (auto expr : input_exprs) {
    if (s.find(expr) == s.end()) {
      s.insert(expr);
      exprs.push_back(expr);
    }
  }

  return exprs;
}

int qmc_count_zero(bool_expr expr) {

  int count = 0;

  for (char &c : expr) {
    if (c == '0') {
      count++;
    }
  }

  return count;
}

bool qmc_match(bool_expr expr1, bool_expr expr2, int &pos) {

  pos = -1;

  for (int i = 0; i < expr1.size(); i++) {
    if (expr1[i] != expr2[i]) {

      if (pos == -1 && expr1[i] == '1' && expr2[i] == '0') {
        pos = i;
      } else {
        return false;
      }
    }
  }

  if (pos == -1) {
    return false;
  }

  return true;
}

bool_exprs qmc(bool_exprs input_exprs) {

  bool_exprs exprs = qmc_non_redundant(input_exprs);

  if (exprs.size() == 0) {
    return exprs;
  }

  // The number of columns.
  const int N = exprs[0].size();

  // Buckets, buckets[count_zero(expr)] <- expr.
  set<qmc_reduce_state> buckets[N + 1][N + 1];

  // Initialize buckets.
  for (int i = 0; i < exprs.size(); i++) {
    buckets[0][qmc_count_zero(exprs[i])].insert(qmc_reduce_state({
        .ids = set<int>({i}),
        .expr = bool_expr(exprs[i]),
    }));
  }

  set<qmc_reduce_state> reduced_states;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (auto x : buckets[i][j]) {
        for (auto y : buckets[i][j + 1]) {

          int pos;

          if (qmc_match(x.expr, y.expr, pos)) {

            reduced_states.insert(x);
            reduced_states.insert(y);

            set<int> new_ids = set<int>();

            for (auto id : x.ids) {
              new_ids.insert(id);
            }

            for (auto id : y.ids) {
              new_ids.insert(id);
            }

            bool_expr new_expr = bool_expr(x.expr);

            new_expr[pos] = '-';

            buckets[i + 1][j].insert(qmc_reduce_state({
                .ids = new_ids,
                .expr = new_expr,
            }));
          }
        }
      }
    }
  }

  // Extract reduced states.
  vector<qmc_reduce_state> rest_states;

  for (int i = 0; i <= N; i++) {
    for (int j = 0; j <= N; j++) {
      for (auto state : buckets[i][j]) {
        if (reduced_states.find(state) == reduced_states.end()) {
          rest_states.push_back(state);
        }
      }
    }
  }

  // Search for the optimal combination.
  priority_queue<qmc_search_state, vector<qmc_search_state>,
                 greater<qmc_search_state>>
      queue;

  queue.push({qmc_search_state({
      .ids = set<int>(),
      .states = set<qmc_reduce_state>(),
  })});

  while (queue.size() > 0) {

    auto top = queue.top();
    queue.pop();

    if (top.ids.size() == exprs.size()) {
      // Since it is an A* like searching process, the first valid answer is
      // the optimum answer.

      bool_exprs result;

      for (auto state : top.states) {
        result.push_back(state.expr);
      }

      return result;
    }

    for (auto state : rest_states) {
      if (top.states.find(state) == top.states.end()) {

        auto new_ids = set<int>();

        for (auto id : top.ids) {
          new_ids.insert(id);
        }

        for (auto id : state.ids) {
          new_ids.insert(id);
        }

        set<qmc_reduce_state> new_states(top.states.begin(), top.states.end());

        new_states.insert(state);

        queue.push(qmc_search_state({
            .ids = new_ids,
            .states = new_states,
        }));
      }
    }
  }

  // Failed.
  return exprs;
}
} // namespace fdc
