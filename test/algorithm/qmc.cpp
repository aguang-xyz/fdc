#include "fdc/fdc.h"
#include "gtest/gtest.h"

using namespace std;
using namespace fdc;

TEST(algorithm, qmc_1) {

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

TEST(algorithm, qmc_2) {

  // This case:
  //
  //   AB -> C             AB -> C
  //   AB -> D     -->      C -> D
  //    C -> D

  bool_exprs exprs = bool_exprs({

      // AB -> C
      bool_expr({'1', '1', '0', '0'}),
      bool_expr({'1', '1', '0', '1'}),

      // AB -> D
      bool_expr({'1', '1', '0', '0'}),
      bool_expr({'1', '1', '1', '0'}),

      // C -> D
      bool_expr({'0', '0', '1', '0'}),
      bool_expr({'0', '1', '1', '0'}),
      bool_expr({'1', '0', '1', '0'}),
      bool_expr({'1', '1', '1', '0'}),
  });

  bool_exprs min_exprs = qmc(exprs);

  ASSERT_EQ(min_exprs, bool_exprs({
                           // C -> D
                           bool_expr({'-', '-', '1', '0'}),

                           // AB -> C
                           bool_expr({'1', '1', '0', '-'}),
                       }));
}
