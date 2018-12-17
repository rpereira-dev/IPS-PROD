/**
 * @file hermite.h
 * @brief calcule la valeur des polynomes d'hermite
 */

#ifndef HERMITE_HPP
# define HERMITE_HPP

# include <armadillo>

/**
 * 	Renvoie une matrice rectangulaire, contenant la valeur
 *	des polynomes de Hermite. Les lignes sont indexées par 'z',
 *	et les colonnes par 'n'
 *
 * 	e.x: H[i][j] = H_j(z_i)
 *
 *	@param z un vecteur colonne contenant les abscisses 'z'
 *	@param nMax la valeur maximal de 'n' dans la résolution
 *	@return H
 */
arma::mat hermite(arma::vec z, unsigned int nMax);

#endif
