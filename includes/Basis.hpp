/**
 *	\file Basis.hpp
 *	\brief Interface du tronqueur de base
 */

#ifndef BASIS_HPP_
#define BASIS_HPP_

# include <iostream>
# include <armadillo>
# include <math.h>
# include "Poly.hpp"
# include "fact.h"

namespace ips {

class Basis {
  public:

    /**
     * Crée un nouveau tronqueur de base
     */
    Basis(double p_br, double p_bz, uint p_N, double p_Q);
    virtual ~Basis();

    /**
     * bz
     */
    double bz;

    /**
     * br
     */
    double br;

    /**
     * la valeur maximal pour 'm'
     */
    uint mMax;

    /**
     * Vecteur d'entier n_max
     */
    arma::ivec nMax;

    /**
     * Matrix d'entier n_z_max
     */
    arma::imat n_zMax;

    /**
     * Calcule la z-function
     * @param z vecteur de coordonnées
     * @param n_z entier calculé précedemment
     * @brief Renvoie le vecteur calculé par la z-function de z et n_z
     */
    arma::vec zPart(arma::vec & z,uint n_z);

    /**
    * Calcule la r-function
    * @param rr vecteur de coordonnées
    * @param m entier calculé précedemment
    * @param n indice de la solution
    * @brief renvoie le vecteur calculé par la r-function de rr m et n
    */
    arma::vec rPart(arma::vec & rr, uint m, uint n);
};

} /* namespace ips */
#endif /* BASIS_HPP_ */

