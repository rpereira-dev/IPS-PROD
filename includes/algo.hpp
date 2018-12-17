/**
 * @file algo.hpp
 * @brief calcule une tranche de la densité nucléaire (theta = 0)
 */

#ifndef ALGO_HPP
# define ALGO_HPP

# include "Basis.hpp"
# include <armadillo>

/**
 *  Calcule la densité nucléaire
 *  @param rho la matrice rho(a, b)
 *  @param basis la base de calcul
 *  @param r le vecteur des coordonnées 'r' (coordonnées cylindriques)
 *  @param z le vecteur des coordonnées 'z' (coordonnées cylindriques)
 *  @return une tranche de la densité nucléaire (theta = 0)
 */
arma::mat localNuclearDensity(
    arma::mat & rho,
    ips::Basis & basis,
    arma::vec r,
    arma::vec z);

#endif
