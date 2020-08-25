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

  glp_set_prob_name(lp, "qmc");

  glp_set_obj_dir(lp, GLP_MIN);

  // Rows.
  glp_add_rows(lp, exprs.size());

  for (int i = 1; i <= exprs.size(); i++) {
    glp_set_row_bnds(lp, i, GLP_LO, 1, 0);
  }

  // Columns.
  glp_add_cols(lp, combined_exprs.size());

  for (int i = 1; i <= combined_exprs.size(); i++) {
    glp_set_col_kind(lp, i, GLP_IV);
    glp_set_col_bnds(lp, i, GLP_LO, 0, 0);
    glp_set_col_bnds(lp, i, GLP_UP, 0, 1);
    glp_set_obj_coef(lp, i, qmc_count_attributes(combined_exprs[i - 1].second));
  }

  // Matrix.
  int matrix_size = 0;

  for (auto expr : combined_exprs) {
    matrix_size += expr.first.size();
  }

  int ia[matrix_size + 1], ja[matrix_size + 1];
  double ar[matrix_size + 1];

  for (int i = 0, j = 1; i < combined_exprs.size(); i++) {
    for (auto id : combined_exprs[i].first) {
      ia[j] = id + 1;
      ja[j] = i + 1;
      ar[j] = 1;
      j++;
    }
  }

  glp_load_matrix(lp, matrix_size, ia, ja, ar);

  // Solve the described 01-IP problem.
  glp_simplex(lp, NULL);

  bool_exprs result;

  for (int i = 1; i <= combined_exprs.size(); i++) {
    if (glp_get_col_prim(lp, i) > 0.5) {
      result.push_back(combined_exprs[i - 1].second);
    }
  }

  return result;
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

  // 3. Search for the best selection of combined expressions.
  return qmc_search(exprs, combined_exprs);
}

} // namespace fdc
