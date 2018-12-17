#include <cxxtest/TestSuite.h>
#include "fact.h"

class FactTestSuite: public CxxTest::TestSuite {
  public:
    void testFactorielle(void) {
        TS_ASSERT_DELTA(fact(0), 1.0, 1e-15);
        TS_ASSERT_DELTA(fact(1), 1.0, 1e-15);
        TS_ASSERT_DELTA(fact(2), 2.0, 1e-15);
        TS_ASSERT_DELTA(fact(3), 6.0, 1e-15);
        TS_ASSERT_DELTA(fact(4), 24.0, 1e-15);
        TS_ASSERT_DELTA(fact(12), 479001600.0, 1e-15);
    }

};
