/**
 *	\file Basis.cpp
 *	\brief Implementation de Basis.hpp
 */

# include "Basis.hpp"


namespace ips {

Basis::Basis(double br, double bz, uint N, double Q) {

    // enregistre br et bz
    this->br = br;
    this->bz = bz;

    // fonction de calcul n_z_max(i)
    auto n_z_max = [N, Q](unsigned int i) {
        return ((double) N + 2.0) * cbrt(Q * Q) + 0.5 - i * Q;
    };
    // calcul de m_max
    for (this->mMax = 0; n_z_max(this->mMax + 1) >= 1.0; this->mMax++)
        ;

    // calcul de n_max
    this->nMax = arma::ivec(this->mMax);
    for (unsigned int m = 0; m < this->mMax; m++) {
        this->nMax(m) = (arma::sword)(
                            0.5 * ((double) (this->mMax - m - 1)) + 1.0);
    }

    // calcul de n_zMax
    this->n_zMax = arma::imat(this->mMax, this->nMax(0));
    this->n_zMax.fill(0);
    for (unsigned int m = 0; m < this->mMax; m++) {
        for (unsigned int n = 0; n < this->nMax(m); n++) {
            this->n_zMax(m, n) = n_z_max(m + 2 * n + 1);
        }
    }

}
Basis::~Basis() {
}

arma::vec Basis::zPart(arma::vec & z, uint n_z) {
    Poly poly;
    poly.calcHermite(n_z + 1, z / this->bz);

    double f    = 1.0 / sqrt(this->bz * (double)(1 << n_z) * sqrt(M_PI) * fact(n_z));
    arma::vec e = arma::exp(-0.5 * z % z / (this->bz * this->bz));
    arma::vec h = poly.hermite(n_z);
    return f * e % h;
}


// Basis r-function
arma::vec Basis::rPart(arma::vec & rr, uint m, uint n) {
    Poly poly;
    poly.calcLaguerre(m + 1, n + 1, rr % rr / (this->br * this->br));

    double f = 1.0 / this->br * sqrt(fact(n) / (M_PI * fact(n + m)));
    arma::vec e = arma::exp(-0.5 * rr % rr / (this->br * this->br));
    arma::vec p = arma::pow(rr / this->br, m);
    arma::vec L = poly.laguerre(m, n);
    return f * e % p % L;
}

} /* namespace ips */
