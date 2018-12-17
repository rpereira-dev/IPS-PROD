#include <cxxtest/TestSuite.h>
#include "Basis.hpp"

// namespace de la class Poly
using namespace ips;

class TestSuiteClientBasis: public CxxTest::TestSuite {
  public:
    void testClientBasis(void) {

        // Mandatory test #01 - Basis truncation
        //     br = 1.935801664793151, bz = 2.829683956491218, N = 14, Q = 1.3
        Basis basis(1.935801664793151,      2.829683956491218,     14,     1.3);
        TS_ASSERT_EQUALS(basis.mMax, 14);
        arma::ivec nMax = {7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1};
        TS_ASSERT(!arma::any(basis.nMax - nMax));
        arma::imat n_zMax = {{18, 15, 13, 10, 7, 5, 2},
            {16, 14, 11,  9, 6, 3, 1},
            {15, 13, 10,  7, 5, 2, 0},
            {14, 11,  9,  6, 3, 1, 0},
            {13, 10,  7,  5, 2, 0, 0},
            {11,  9,  6,  3, 1, 0, 0},
            {10,  7,  5,  2, 0, 0, 0},
            { 9,  6,  3,  1, 0, 0, 0},
            { 7,  5,  2,  0, 0, 0, 0},
            { 6,  3,  1,  0, 0, 0, 0},
            { 5,  2,  0,  0, 0, 0, 0},
            { 3,  1,  0,  0, 0, 0, 0},
            { 2,  0,  0,  0, 0, 0, 0},
            { 1,  0,  0,  0, 0, 0, 0}
        };
        // check if matrices are equal
        TS_ASSERT(!arma::any(arma::any(basis.n_zMax - n_zMax)));
    }

};

