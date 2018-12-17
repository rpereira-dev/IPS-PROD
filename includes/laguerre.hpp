/**
 * @file laguerre.h
 * @brief calcule la valeur des polynomes de laguerre
 */

#ifndef LAGUERRE_HPP
# define LAGUERRE_HPP

# include <armadillo>

/**
 * 	Renvoie un cube, contenant les valeurs des polynomes de Laguerre,
 *  indexé en L[z][m][n]
 *	@param z un vecteur colonne contenant les abscisses 'z'
 *	@param mMax la valeur maximal de 'm' dans le calcul
 *	@param nMax la valeur maximal de 'n' dans le calcul
 *	@return L un cube contenant les valeurs de polynomes de Laguerre : L[z][m][n]
 */
arma::cube laguerre(arma::vec z, unsigned int mMax, unsigned int nMax);

#endif
