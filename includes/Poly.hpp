/**
 *	\file Poly.hpp
 *	\brief Interface du calculateur de polynome
 */

#ifndef POLY_HPP_
#define POLY_HPP_

# include "hermite.hpp"
# include "laguerre.hpp"
# include <iostream>
# include <armadillo>

namespace ips {

class Poly {
  public:

    /**
     * Crée un nouveau calculateur de polynome
     */
    Poly();
    virtual ~Poly();

    /**
     * calcul les valeurs des polynomes d'Hermite pour dont l'indice est dans {0 ... n - 1}
     * @param nMax l'indice 'n' maximal pour lequel les polynomes doivent être calculé
     * @param z le vecteur des absisses (coordonées d'espace 1D)
     */
    void calcHermite(unsigned int nMax, arma::vec z);

    /**
     * Renvoie les valeurs du n-ieme polynome d'Hermite pour i dans {0 ... n - 1}
     * @param n indice dans la famille des polynomes d'Hermite
     * @attention Un appel vers cette fonction doit être précédé d'un appel vers \ref Poly::calcHermite(n', z), avec n < n'
     */
    arma::vec hermite(unsigned int n);

    /**
     * calcul les valeurs des polynomes de Laguerre dont les indices (m, n) sont dans {0, ..., mMax - 1} x (0, ..., nMax - 1}
     * @param mMax l'indice 'm' maximal pour lequel les polynomes doivent être calculé
     * @param nMax l'indice 'n' maximal pour lequel les polynomes doivent être calculé
     * @param z le vecteur des absisses (coordonées d'espace 1D)
     */
    void calcLaguerre(unsigned int mMax, unsigned int nMax, arma::vec z);

    /**
     * Renvoie les valeurs du n-ieme polynome d'Hermite pour i dans {0 ... n - 1}
     * @param (n, m) est l'indice dans la famille des polynomes de Laguerre
     * @attention Un appel vers cette fonction doit être précédé d'un appel vers \ref Poly::calcHermite(n', z), avec n < n'
     */
    arma::vec laguerre(unsigned int m, unsigned int n);

  protected:
    /**
     *  La dernière matrice de hermite calculé
     */
    arma::mat H;

    /**
     *  Le dernier cube de Laguerre calculé
     */
    arma::cube L;

};

} /* namespace ips */
#endif /* POLY_HPP_ */

