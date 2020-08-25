#include <queue>
#include <set>

#include "fdc.h"
#include "glpk/glpk.h"

namespace fdc {

using namespace std;

typedef pair<set<int>, bool_expr> qmc_combined_expr;

// Remove redundant expressions.
bool_exprs qmc_redundant_filter(bool_exprs exprs) {

  set<bool_expr> expr_set;

  for (auto expr : exprs) {
    expr_set.insert(expr);
  }

  return bool_exprs(expr_set.begin(), expr_set.end());
}

// Check if a and b has only one different element which are '0' and '1'.
bool qmc_match_expr(bool_expr a, bool_expr b, int &pos) {

  pos = -1;

  for (int i = 0; i < a.size(); i++) {
    if (a[i] != b[i]) {
      if (a[i] == '0' && b[i] == '1' && pos == -1) {
        pos = i;
      } else {
        return false;
      }
    }
  }

  return pos != -1;
}

int qmc_count_zero(bool_expr x) {

  int count = 0;

  for (auto c : x) {
    if (c == '0') {
      count++;
    }
  }

  return count;
}

int qmc_count_attributes(bool_expr x) {

  int count = 0;

  for (auto c : x) {
    if (c == '0' || c == '1') {
      count++;
    }
  }

  return count;
}

// Try to combine expressions.
vector<qmc_combined_expr> qmc_combine(int N, bool_exprs exprs) {

  set<qmc_combined_expr> reduced_set;
  set<qmc_combined_expr> buckets[N + 1][N + 1];

  for (int id = 0; id < exprs.size(); id++) {
    buckets[0][qmc_count_zero(exprs[id])].insert(
        qmc_combined_expr(set<int>({id}), exprs[id]));
  }

  for (int num_dash = 0; num_dash < N; num_dash++) {
    for (int num_zero = 0; num_zero < N; num_zero++) {
      for (auto a : buckets[num_dash][num_zero + 1]) {
        for (auto b : buckets[num_dash][num_zero]) {

          int pos = 0;

          if (qmc_match_expr(a.second, b.second, pos)) {

            set<int> new_ids = set<int>(a.first.begin(), a.first.end());

            for (auto id : b.first) {
              new_ids.insert(id);
            }

            bool_expr new_expr = bool_expr(a.second);
            new_expr[pos] = '-';

            buckets[num_dash + 1][num_zero].insert(qmc_combined_expr({
                .ids = new_ids,
                .expr = new_expr,
            }));

            reduced_set.insert(a);
            reduced_set.insert(b);
          }
        }
      }
    }
  }

  vector<qmc_combined_expr> result;

  for (int num_dash = 0; num_dash < N; num_dash++) {
    for (int num_zero = 0; num_zero < N; num_zero++) {
      for (auto a : buckets[num_dash][num_zero]) {
        if (reduced_set.find(a) == reduced_set.end()) {
          result.push_back(a);
        }
      }
    }
  }

  return result;
}

bool_exprs qmc_search(bool_exprs exprs,
                      vector<qmc_combined_expr> combined_exprs) {

  set<int> refs[exprs.size()];

  glp_prob *lp = glp_create_prob();

  // TODO

  return exprs;
}

bool_exprs qmc(bool_exprs exprs) {

  if (exprs.size() == 0) {
    return exprs;
  }

  int N = exprs[0].size();

  // 1. Remove redundant expressions.
  exprs = qmc_redundant_filter(exprs);

  // 2. Try to combine and reduce expressions.
  auto combined_exprs = qmc_combine(N, exprs);

  // For debug.
  for (auto x : combined_exprs) {

    for (auto c : x.second) {
      printf("%c", c);
    }

    printf(" : ");

    for (int id = 0; id < exprs.size(); id++) {
      if (x.first.find(id) != x.first.end()) {
        printf("x");
      } else {
        printf(" ");
      }
    }

    for (auto id : x.first) {
      printf(" %d", id);
    }

    printf("\n");
  }

  // 3. Search for the best selection of combined expressions.
  return qmc_search(exprs, combined_exprs);
}

} // namespace fdc
