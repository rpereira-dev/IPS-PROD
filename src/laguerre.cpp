/**
 * @file laguerre.cpp
 * @brief calcule la valeur des polynomes de laguerre
 */

# include "laguerre.hpp"

arma::cube laguerre(arma::vec z, unsigned int mMax, unsigned int nMax) {
    // Initialisation du cube : (n_rows, n_cols, n_slices)
    arma::cube L = arma::cube(z.n_rows, mMax + 1, nMax + 1);

    // initialisation pour n=0
    // L(z, m, 0) = 1
    L.slice(0).fill(1);

    // initilisation pour n=1
    // L(z, m, 1) = 1 + m - z
    L.slice(1).fill(1);
    for (unsigned int m = 0 ; m <= mMax ; m++) {
        L.slice(1).col(m) -= z;
    }
    arma::vec mVec = arma::linspace(0, mMax, mMax + 1);
    for (unsigned int i = 0 ; i < z.n_rows ; i++) {
        L.slice(1).row(i) += mVec.t();
    }

    //création de la matrice des 'm - 1'
    arma::mat mMat(z.n_rows, mMax + 1);
    for (unsigned int i = 0 ; i < z.n_rows ; i++) {
        mMat.row(i) = mVec.t() - 1;
    }

    //création de la matrice des 'm - 1 - z'
    arma::mat mzMat(z.n_rows, mMax + 1);
    for (unsigned int m = 0 ; m <= mMax ; m++) {
        mzMat.col(m) = mMat.col(m) - z;
    }

    // calcul pour 2 <= n <= nMax
    for (unsigned int n = 2 ; n <= nMax ; n++) {
        // formule de recursivité
        L.slice(n) = (2 + mzMat / (float)n) % L.slice(n - 1) - (1.0 + mMat / (float)n) % L.slice(n - 2);
    }

    return L;
}
