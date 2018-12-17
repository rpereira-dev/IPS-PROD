#include <cxxtest/TestSuite.h>
#include "hermite.hpp"

class HermiteTestSuite: public CxxTest::TestSuite {
  public:
    /**
     *	Les valeurs ont été testé à partir de :
     *
     *	https://www.wolframalpha.com/input/?i=hermiteh
     */
    void testHermite(void) {

        {
            unsigned int n = 20;

            /* on fixe z à 1.42 */
            arma::vec z = arma::vec(1);
            z[0] = 1.42;

            arma::mat H = hermite(z, n);
            TS_ASSERT_DELTA(H(0, 5),  -102.9729944576, 1e-7);
            TS_ASSERT_DELTA(H(0, 10), -84345.35025821, 1e-7);
        }


        {
            unsigned int n = 7;

            arma::vec z = arma::vec(2);
            z[0] = 4.47;
            z[1] = 4.48;

            arma::mat H = hermite(z, n);

            TS_ASSERT_DELTA(H(0, 3), 660.876984, 1e-7);
            TS_ASSERT_DELTA(H(1, 3), 665.563136, 1e-7);
            TS_ASSERT_DELTA(H(0, 7), 2458281.8217, 1e-4);
            TS_ASSERT_DELTA(H(1, 7), 2505290.9364, 1e-4);
        }


    }


};
