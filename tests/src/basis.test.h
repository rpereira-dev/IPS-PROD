#include <cxxtest/TestSuite.h>
# include "Basis.hpp"

class BasisTestSuite: public CxxTest::TestSuite {
  public:
    void testBasis(void) {
        //     br = 1.935801664793151, bz = 2.829683956491218, N = 14, Q = 1.3
        ips::Basis basis(1.935801664793151, 2.829683956491218, 14, 1.3);

        uint i = 0;
        for (uint m = 0; m < basis.mMax; m++) {
            for (uint n = 0; n < basis.nMax(m); n++) {
                for (uint n_z = 0; n_z < basis.n_zMax(m, n); n_z++) {
                    i++;
                }
            }
        }
        TS_ASSERT_EQUALS(i, 374);
    }
};
