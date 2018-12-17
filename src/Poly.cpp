/**
 *	\file Poly.cpp
 *	\brief Implementation de Poly.hpp
 */

# include "Poly.hpp"

namespace ips {

Poly::Poly() {
}

Poly::~Poly() {
}

void Poly::calcHermite(unsigned int nMax, arma::vec z) {
    this->H = ::hermite(z, nMax);
}

arma::vec Poly::hermite(unsigned int n) {
    return this->H.col(n);
}

void Poly::calcLaguerre(unsigned int mMax, unsigned int nMax, arma::vec z) {
    this->L = ::laguerre(z, mMax, nMax);
}

arma::vec Poly::laguerre(unsigned int m, unsigned int n) {
    return this->L.slice(n).col(m);
}



} /* namespace ips */
