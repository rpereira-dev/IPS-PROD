/**
 * @file hermite.cpp
 * @brief calcule la valeur des polynomes d'hermite
 */

# include "hermite.hpp"

arma::mat hermite(arma::vec z, unsigned int nMax) {
    /* Initialisation de la matrice */
    arma::mat H = arma::mat(z.n_rows, nMax + 1);

    H.col(0).fill(1.0);
    H.col(1) = 2 * z;

    /* remplissage de la matrice */
    unsigned int i;
    for (i = 2 ; i <= nMax ; i++) {
        H.col(i) = 2 * z % H.col(i - 1) - 2 * (i - 1) * H.col(i - 2);
    }

    return H;
}
