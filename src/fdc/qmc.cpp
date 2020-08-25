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

  // Combined state ids.
  set<int> state_ids;

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

  fprintf(stderr, "input size = %lu\n", input_exprs.size());

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

  fprintf(stderr, "Start searching, |rest_states| = %lu.\n",
          rest_states.size());

  for (auto state : rest_states) {
    for (auto c : state.expr) {
      fprintf(stderr, "%c", c);
    }

    fprintf(stderr, " :");

    for (auto id : state.ids) {
      fprintf(stderr, " %d", id);
    }

    fprintf(stderr, "\n");
  }

  // Search for the optimal combination.
  priority_queue<qmc_search_state, vector<qmc_search_state>,
                 greater<qmc_search_state>>
      queue;

  set<set<int>> visit;

  auto init_state = qmc_search_state({
      .ids = set<int>(),
      .states = set<qmc_reduce_state>(),
      .state_ids = set<int>(),
  });

  queue.push(init_state);

  while (queue.size() > 0) {
    fprintf(stderr, "Rest: %lu\n", queue.size());

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

    // Count how many un-searched expressions can cover each target input
    // expression.
    int ref_cnt[exprs.size()] = {0};

    for (int state_id = 0; state_id < rest_states.size(); state_id++) {
      if (top.state_ids.find(state_id) == top.state_ids.end()) {
        for (auto id : rest_states[state_id].ids) {
          ref_cnt[id]++;
        }
      }
    }

    // Compute if there is a must included search expression.
    int must_select_state_id = -1;

    for (int state_id = 0; state_id < rest_states.size(); state_id++) {
      if (top.state_ids.find(state_id) == top.state_ids.end()) {
        int must_select = false;

        for (auto id : rest_states[state_id].ids) {
          if (ref_cnt[id] == 1 && top.ids.find(id) == top.ids.end()) {
            must_select = true;
            break;
          }
        }

        if (must_select) {
          must_select_state_id = state_id;
          break;
        }
      }
    }

    // Iteration for adding a new expression.
    for (int state_id = 0; state_id < rest_states.size(); state_id++) {

      // If there one must be included, skip others.
      if (must_select_state_id != -1 && must_select_state_id != state_id) {
        continue;
      }

      auto state = rest_states[state_id];

      if (top.state_ids.find(state_id) == top.state_ids.end()) {

        auto new_ids = set<int>();

        for (auto id : top.ids) {
          new_ids.insert(id);
        }

        bool expand_ids = false;

        for (auto id : state.ids) {
          if (new_ids.find(id) == new_ids.end()) {
            new_ids.insert(id);
            expand_ids = true;
          }
        }

        // Prune strategy 1. Adding new expressions must lead to more input
        // expressions to be covered.
        if (!expand_ids) {
          continue;
        }

        set<qmc_reduce_state> new_states(top.states.begin(), top.states.end());
        new_states.insert(state);

        set<int> new_state_ids(top.state_ids.begin(), top.state_ids.end());
        new_state_ids.insert(state_id);

        auto new_search_state = qmc_search_state({
            .ids = new_ids,
            .states = new_states,
            .state_ids = new_state_ids,
        });

        // Prune strategy 2. Do not search for exact same combinations for
        // multiple times.
        if (visit.find(new_state_ids) == visit.end()) {
          queue.push(new_search_state);
          visit.insert(new_state_ids);
        }
      }
    }
  }

  // Failed.
  return exprs;
}
} // namespace fdc
