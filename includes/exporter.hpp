#ifndef EXPORTER_HPP
# define EXPORTER_HPP

# include <iostream>
# include <armadillo>

/**
 * Converti un cube armadillo en une chaine de caractère
 * au format 'DF3' (POV-Ray)
 * @param m un cube armadillo
 * @return une chaine au format DF3
 */
std::string cubeToDf3(const arma::cube & m);

/**
 * Converti un cube armadillo en une chaine de caractère
 * au format 'RAW' (Blender)
 * @param m un cube armadillo
 * @return une chaine au format RAW
 */
std::string cubeToRaw(const arma::cube & m);

# endif // EXPORTER_HPP
