#include "fdc/fdc.h"
#include "gtest/gtest.h"

using namespace std;
using namespace fdc;

TEST(algorithm, qmc) {

  bool_exprs exprs = bool_exprs({

      bool_expr({'0', '0', '0', '0'}),
      bool_expr({'0', '1', '0', '0'}),
      bool_expr({'1', '0', '0', '0'}),
      bool_expr({'0', '1', '0', '1'}),
      bool_expr({'1', '1', '0', '0'}),
      bool_expr({'0', '1', '1', '1'}),
      bool_expr({'1', '0', '1', '1'}),
      bool_expr({'1', '1', '1', '1'}),
  });

  bool_exprs min_exprs = qmc(exprs);

  ASSERT_EQ(min_exprs, bool_exprs({
                           bool_expr({'-', '-', '0', '0'}),
                           bool_expr({'0', '1', '-', '1'}),
                           bool_expr({'1', '-', '1', '1'}),
                       }));
}
