/**
 *	\file main.cpp
 *	\brief	Contient le 'main' du programme
 *		et lis les arguments passés en paramètres
 */

#include <iostream>
#include <fstream>
# include <unistd.h>
# include "laguerre.hpp"
# include "Basis.hpp"
# include "algo.hpp"
# include "exporter.hpp"
# include "nlohmann/json.hpp"

/**
 * Charge le fichier de configuration passé en paramètre s'il existe,
 * ou charges une configuration par défaut sinon
 * @param file le chemin du fichier de config
 * @return un objet 'nlohmann::json' contenant la configuration
 */
nlohmann::json loadConfig(char * file) {
    /* charge la config par défaut */
    nlohmann::json config;

    config["x"] = nlohmann::json();
    config["x"]["min"] = -10.0;
    config["x"]["max"] =  10.0;
    config["x"]["points"] = 32;

    config["y"] = nlohmann::json();
    config["y"]["min"] = -10.0;
    config["y"]["max"] =  10.0;
    config["y"]["points"] = 32;

    config["z"] = nlohmann::json();
    config["z"]["min"] = -20.0;
    config["z"]["max"] =  20.0;
    config["z"]["points"] = 64;

    if (file) {
        try {
            std::ifstream config_if(file);
            config_if >> config;
        } catch (nlohmann::detail::parse_error & err) {
            std::cerr << "Le fichier " << file << " est invalide." << std::endl;
            std::cerr << err.what() << std::endl;
        }
    }
    return config;
}


/**
 * Main du programme
 * @param argc nombre d'argument (taille de argv)
 * @param argv les arguments
 * @return exit status
 */
int main(int argc, char **argv) {

    // lecture des arguments
    char * rhoFile = NULL;
    char * configFile = NULL;
    char * df3File = NULL;
    char * rawFile = NULL;
    char * matFile = NULL;
    bool quiet = false;
    extern char * optarg;
    int opt;
    while ((opt = getopt(argc, argv, "p:c:d:r:m:q")) != -1) {
        switch (opt) {
        case 'p':
            rhoFile = optarg;
            break ;
        case 'c':
            configFile = optarg;
            break ;
        case 'd':
            df3File = optarg;
            break ;
        case 'r':
            rawFile = optarg;
            break ;
        case 'm':
            matFile = optarg;
            break ;
        case 'q':
            quiet = true;
            break ;
        default:
            goto arg_err;
        }
    }

    // si erreur
    if (! rhoFile) {
arg_err:
        fprintf(stderr, "Usage: %s [-p rho.arma] {-c config.json} {-m file.mat} {-d file.df3} {-r file.raw}\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (quiet) {
        close(STDOUT_FILENO);
    }

    // chargement de la config
    nlohmann::json config = loadConfig(configFile);

    // création de la matrice 'rho' à partir de la matrice lu
    arma::mat rho;
    rho.load(rhoFile, arma::arma_ascii);

    //     	    br = 1.935801664793151, bz = 2.829683956491218, N = 14, Q = 1.3
    ips::Basis basis(1.935801664793151,      2.829683956491218,     14,     1.3);

    // axe en fm.
    arma::vec X = arma::linspace(config["x"]["min"], config["x"]["max"], config["x"]["points"]);
    arma::vec Y = arma::linspace(config["y"]["min"], config["y"]["max"], config["y"]["points"]);
    arma::vec Z = arma::linspace(config["z"]["min"], config["z"]["max"], config["z"]["points"]);

    // calcul de la densité nucléaire dans le plan theta=0 (r = x, z = z)
    arma::mat plane = localNuclearDensity(rho, basis, X, Z);

    // si l'utilisateur souhaite exporter en .mat
    if (matFile) {
        std::ofstream file;
        file.open(matFile);
        file << config << std::endl << plane << std::endl;
        file.close();
    }

    // si l'utilisateur souhaite exporter en .df3 ou en .raw
    if (df3File || rawFile) {
        arma::cube cube(X.size(), Y.size(), Z.size());
        for (uint i = 0 ; i < X.size() ; i++) {
            double x = X(i);
            for (uint j = 0 ; j < Y.size() ; j++) {
                double y = Y[j];

                // on utilise la symétrie sur l'axe 'Z'

                // passage en coordonnées cylindriques
                //
                // r = sqrt(x^2 + y^2)
                // theta = arctan(y / x)
                // z = z

                double r = sqrt(x * x + y * y);

                // indice de 'r' correspondant à (x, y, z)
                uint l = 0;

                // recherches le point de coordonnées (r', theta=0, z),
                // avec r' = min({abs(r - ri)} / ri in X})
                for (uint ll = 1 ; ll < X.size() ; ll++) {
                    if (abs(r - X[ll]) < abs(r - X[l])) {
                        l = ll;
                    }
                }

                // pour chaque point le long de l'axe 'z'
                for (uint k = 0 ; k < Z.size() ; k++) {

                    // indice de 'z' correspondant à (x, y, z)
                    cube(i, j, k) = plane(l, k);
                }
            }
        }

        if (df3File) {
            std::ofstream file;
            file.open (df3File);
            file << cubeToDf3(cube);
            file.close();
        }

        if (rawFile) {
            std::ofstream file;
            file.open (rawFile);
            file << cubeToRaw(cube);
            file.close();
        }
    }

    return 0;
}
