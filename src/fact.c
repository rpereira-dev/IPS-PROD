/**
 * @file fact.cpp
 * @brief calcule la factorielle
 */

#include "fact.h"

# define FACT0  (1.0)
# define FACT1  (1.0)
# define FACT2  (FACT1  *  2.0)
# define FACT3  (FACT2  *  3.0)
# define FACT4  (FACT3  *  4.0)
# define FACT5  (FACT4  *  5.0)
# define FACT6  (FACT5  *  6.0)
# define FACT7  (FACT6  *  7.0)
# define FACT8  (FACT7  *  8.0)
# define FACT9  (FACT8  *  9.0)
# define FACT10 (FACT9  * 10.0)
# define FACT11 (FACT10 * 11.0)
# define FACT12 (FACT11 * 12.0)
# define FACT13 (FACT12 * 13.0)
# define FACT14 (FACT13 * 14.0)
# define FACT15 (FACT14 * 15.0)
# define FACT16 (FACT15 * 16.0)
# define FACT17 (FACT16 * 17.0)
# define FACT18 (FACT17 * 18.0)
# define FACT19 (FACT18 * 19.0)

/**
 *  Calcule la factorielle de n (n!)
 *  @param n l'entier
 *  @return n!
 */
double fact(unsigned int n) {
    static double r[20] = {
        FACT0,  FACT1,  FACT2,  FACT3,  FACT4,
        FACT5,  FACT6,  FACT7,  FACT8,  FACT9,
        FACT10, FACT11, FACT12, FACT13, FACT14,
        FACT15, FACT16, FACT17, FACT18, FACT19
    };
    return n < (sizeof(r) / sizeof(double)) ? r[n] : -1;
}

