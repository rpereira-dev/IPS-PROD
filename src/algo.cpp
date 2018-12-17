/**
 * @file algo.cpp
 * @brief différentes implémentation du calcule de la densité nucléaire local
 */

# include "algo.hpp"

#ifndef ALGO
/** l'id de l'algorithme a utiliser */
# define ALGO 0
#elif ALGO == 7 // l'algo 7 a besoin de pthread
# include <thread>
#endif

/**
 * implémentation de l'algorithme de calcul de la densité nucléaire
 */
arma::mat localNuclearDensity(
    arma::mat & rho,
    ips::Basis & basis,
    arma::vec r,
    arma::vec z) {

    // matrice stockant le résultat
    arma::mat result = arma::zeros(r.size(), z.size());

    // timer mesurant l'algorithme
    arma::wall_clock timer;
    timer.tic();

// Algorithme naïf
#if ALGO == 0
    uint a = 0;
    for (uint ma = 0; ma < basis.mMax; ma++) {
        for (uint na = 0; na < basis.nMax(ma); na++) {
            for (uint n_za = 0; n_za < basis.n_zMax(ma, na); n_za++) {
                uint b = 0;
                for (uint mb = 0; mb < basis.mMax; mb++) {
                    for (uint nb = 0; nb < basis.nMax(mb); nb++) {
                        for (uint n_zb = 0; n_zb < basis.n_zMax(mb, nb); n_zb++) {
                            arma::mat phi_a = basis.rPart(r, ma, na) * basis.zPart(z, n_za).t();
                            arma::mat phi_b = basis.rPart(r, mb, nb) * basis.zPart(z, n_zb).t();
                            result += rho(a, b) * phi_a % phi_b;
                            ++b;
                        }
                    }
                }
                ++a;
            }
        }
    }

// Optimisation : on sort le calcul de 'phi_a' des boucle sur 'b'
#elif ALGO == 1

    uint a = 0;
    for (uint ma = 0; ma < basis.mMax; ma++) {
        for (uint na = 0; na < basis.nMax(ma); na++) {
            for (uint n_za = 0; n_za < basis.n_zMax(ma, na); n_za++) {
                // calcul de 'phi_a' une seule fois
                arma::mat phi_a = basis.rPart(r, ma, na) * basis.zPart(z, n_za).t();
                uint b = 0;
                for (uint mb = 0; mb < basis.mMax; mb++) {
                    for (uint nb = 0; nb < basis.nMax(mb); nb++) {
                        for (uint n_zb = 0; n_zb < basis.n_zMax(mb, nb); n_zb++) {
                            arma::mat phi_b = basis.rPart(r, mb, nb) * basis.zPart(z, n_zb).t();
                            result += rho(a, b) * phi_a % phi_b;
                            ++b;
                        }
                    }
                }
                ++a;
            }
        }
    }
// Optimisation
// on sort les calculs de R(a) de la boucle sur n_za
// on sort les calculs de R(b) de la boucle sur n_zb
#elif ALGO == 2

    uint a = 0;
    for (uint ma = 0; ma < basis.mMax; ma++) {
        for (uint na = 0; na < basis.nMax(ma); na++) {
            // calcul de R(a) une fois au lieu de 'basis.n_zMax(ma, na)' fois
            arma::vec Ra = basis.rPart(r, ma, na);
            for (uint n_za = 0; n_za < basis.n_zMax(ma, na); n_za++) {
                arma::mat phi_a = Ra * basis.zPart(z, n_za).t();
                uint b = 0;
                for (uint mb = 0; mb < basis.mMax; mb++) {
                    for (uint nb = 0; nb < basis.nMax(mb); nb++) {
                        // calcul de R(a) une fois au lieu de 'basis.n_zMax(mb, nb)' fois
                        arma::vec Rb = basis.rPart(r, mb, nb);
                        for (uint n_zb = 0; n_zb < basis.n_zMax(mb, nb); n_zb++) {
                            arma::mat phi_b = Rb * basis.zPart(z, n_zb).t();
                            result += rho(a, b) * phi_a % phi_b;
                            ++b;
                        }
                    }
                }
                ++a;
            }
        }
    }
// Optimisation
// suppression de la boucle 'mb' (car si ma != mb, alors rho(a, b) = 0)
#elif ALGO == 3
    uint a = 0;
    uint b_bgn = 0;
    for (uint m = 0; m < basis.mMax; m++) {
        for (uint na = 0; na < basis.nMax(m); na++) {
            arma::vec Ra = basis.rPart(r, m, na);
            for (uint n_za = 0; n_za < basis.n_zMax(m, na); n_za++) {
                arma::mat phi_a = Ra * basis.zPart(z, n_za).t();

                // on positionne l'indice 'b'
                uint b = b_bgn;

                for (uint nb = 0; nb < basis.nMax(m); nb++) {
                    arma::vec Rb = basis.rPart(r, m, nb);
                    for (uint n_zb = 0; n_zb < basis.n_zMax(m, nb); n_zb++) {
                        arma::mat phi_b = Rb * basis.zPart(z, n_zb).t();
                        result += rho(a, b) * phi_a % phi_b;
                        ++b;
                    }
                }
                ++a;
            }
        }

// 		on a fixé mb = ma : on replace l'indice 'b' avec le code suivant :
//
//        for (uint n = 0; n < basis.nMax(m); n++) {
//            b_bgn += basis.n_zMax(m, n);
//        }
//
//	ce code est équivalent à:
        b_bgn = a;
    }

// Optimisation
// pré-calcul de R * Z
#elif ALGO == 4

    // pré-calcul de Z
    arma::vec * Z = new arma::vec[basis.n_zMax(0, 0)];
    for (uint n_z = 0; n_z < basis.n_zMax(0, 0); n_z++) {
        Z[n_z] = basis.zPart(z, n_z);
    }

    // pré-calcul de R * Z
    uint i = 0;
    arma::mat * RZ = new arma::mat[basis.mMax * basis.nMax(0) * basis.n_zMax(0, 0)];
    for (uint m = 0 ; m < basis.mMax ; m++) {
        for (uint n = 0 ; n < basis.nMax(m) ; n++) {
            arma::mat R = basis.rPart(r, m, n);
            for (uint n_z = 0; n_z < basis.n_zMax(m, n); n_z++) {
                RZ[i] = R * Z[n_z].t();
                ++i;
            }
        }
    }
    // libère la mémoire de Z
    delete [] Z;

    // algo 3
    uint a = 0;
    uint b_bgn = 0;
    for (uint m = 0; m < basis.mMax; m++) {
        for (uint na = 0; na < basis.nMax(m); na++) {
            for (uint n_za = 0; n_za < basis.n_zMax(m, na); n_za++) {
                uint b = b_bgn;
                for (uint nb = 0; nb < basis.nMax(m); nb++) {
                    for (uint n_zb = 0; n_zb < basis.n_zMax(m, nb); n_zb++) {
                        result += rho(a, b) * RZ[a] % RZ[b];
                        ++b;
                    }
                }
                ++a;
            }
        }
        b_bgn = a;
    }

    // libère la mémoire de R * Z
    delete [] RZ;

// Optimisation
// utilisation symétrie rho(a, b) == rho(b, a) + linéarisation boucle sur 'b'
#elif ALGO == 5
    // algo 4
    arma::vec * Z = new arma::vec[basis.n_zMax(0, 0)];
    for (uint n_z = 0; n_z < basis.n_zMax(0, 0); n_z++) {
        Z[n_z] = basis.zPart(z, n_z);
    }

    uint i = 0;
    arma::mat * RZ = new arma::mat[basis.mMax * basis.nMax(0) * basis.n_zMax(0, 0)];
    for (uint m = 0 ; m < basis.mMax ; m++) {
        for (uint n = 0 ; n < basis.nMax(m) ; n++) {
            arma::mat R = basis.rPart(r, m, n);
            for (uint n_z = 0; n_z < basis.n_zMax(m, n); n_z++) {
                RZ[i] = R * Z[n_z].t();
                ++i;
            }
        }
    }
    delete [] Z;

    uint a = 0;
    uint b_bgn = 0;
    for (uint m = 0; m < basis.mMax; m++) {
        for (uint na = 0; na < basis.nMax(m); na++) {
            for (uint n_za = 0; n_za < basis.n_zMax(m, na); n_za++) {
                // on utilise la symétrie
                for (uint b = b_bgn ; b < a ; b++) {
                    result += rho(a, b) * RZ[a] % RZ[b] * 2.0;
                }
                result += rho(a, a) * RZ[a] % RZ[a];
                ++a;
            }
        }
        b_bgn = a;
    }

    delete [] RZ;

// Optimisation
// linéarisation de la boucle sur 'a'
#elif ALGO == 6
    // algo 5
    arma::vec * Z = new arma::vec[basis.n_zMax(0, 0)];
    for (uint n_z = 0; n_z < basis.n_zMax(0, 0); n_z++) {
        Z[n_z] = basis.zPart(z, n_z);
    }

    uint i = 0;
    arma::mat * RZ = new arma::mat[basis.mMax * basis.nMax(0) * basis.n_zMax(0, 0)];
    for (uint m = 0 ; m < basis.mMax ; m++) {
        for (uint n = 0 ; n < basis.nMax(m) ; n++) {
            arma::mat R = basis.rPart(r, m, n);
            for (uint n_z = 0; n_z < basis.n_zMax(m, n); n_z++) {
                RZ[i] = R * Z[n_z].t();
                ++i;
            }
        }
    }
    delete [] Z;

    // pré-calcul des indices (three-pass)
    uint * ind = (uint *) malloc(2 * sizeof(uint) * basis.mMax * basis.nMax(0) * basis.n_zMax(0, 0));
    uint * ptr = ind;
    i = 0;
    uint b_bgn = 0;
    for (uint m = 0; m < basis.mMax; m++) {
        for (uint n = 0; n < basis.nMax(m); n++) {
            for (uint n_z = 0; n_z < basis.n_zMax(m, n); n_z++) {
                *(ptr + 0) = i;
                *(ptr + 1) = b_bgn;
                ptr += 2;
                ++i;
            }
        }
        b_bgn = i;
    }

    uint * end = ptr;
    ptr = ind;

    while (ptr != end) {
        uint a = *ptr++;

        uint b_bgn = *ptr++;
        for (uint b = b_bgn ; b < a ; b++) {
            result += rho(a, b) * RZ[a] % RZ[b] * 2.0;
        }
        result += rho(a, a) * RZ[a] % RZ[a];
    }

    delete [] RZ;

    // libère la mémoire
    free(ind);

// Optimisation
// multithreading
#elif ALGO == 7
# ifndef ALGO_NUM_THREADS
# 	define ALGO_NUM_THREADS 4
# endif

    arma::vec * Z = new arma::vec[basis.n_zMax(0, 0)];
    for (uint n_z = 0; n_z < basis.n_zMax(0, 0); n_z++) {
        Z[n_z] = basis.zPart(z, n_z);
    }

    uint i = 0;
    arma::mat * RZ = new arma::mat[basis.mMax * basis.nMax(0) * basis.n_zMax(0, 0)];
    for (uint m = 0 ; m < basis.mMax ; m++) {
        for (uint n = 0 ; n < basis.nMax(m) ; n++) {
            arma::mat R = basis.rPart(r, m, n);
            for (uint n_z = 0; n_z < basis.n_zMax(m, n); n_z++) {
                RZ[i] = R * Z[n_z].t();
                ++i;
            }
        }
    }
    delete [] Z;

    uint * ind = (uint *) malloc(2 * sizeof(uint) * basis.mMax * basis.nMax(0) * basis.n_zMax(0, 0));
    uint * ptr = ind;
    i = 0;
    uint b_bgn = 0;
    for (uint m = 0; m < basis.mMax; m++) {
        for (uint n = 0; n < basis.nMax(m); n++) {
            for (uint n_z = 0; n_z < basis.n_zMax(m, n); n_z++) {
                *(ptr + 0) = i;
                *(ptr + 1) = b_bgn;
                ptr += 2;
                ++i;
            }
        }
        b_bgn = i;
    }

    uint * end = ptr;
    uint size = i;

    // allocation de l'emplacement du resultat intermédiaire par thread
    arma::mat * results = new arma::mat[ALGO_NUM_THREADS];

    // tableau contenant les threads
    std::thread threads[ALGO_NUM_THREADS];

    // création de chaque thread
    for (uint thrdID = 0 ; thrdID < ALGO_NUM_THREADS ; thrdID++) {
        // allocation de la matrice du resultat intermédiaire pour ce thread
        results[thrdID] = arma::zeros(r.size(), z.size());

        // création du thread
        threads[thrdID] = std::thread([thrdID, ind, end, size, results, RZ, rho]() {
            uint * thrdPtr = ind + 2 * (size / ALGO_NUM_THREADS * thrdID);
            uint * thrdEnd = (thrdID == ALGO_NUM_THREADS - 1)  ? end : ind + 2 * (size / ALGO_NUM_THREADS * (thrdID + 1));
            while (thrdPtr != thrdEnd) {
                uint a = *thrdPtr++;
                uint b_bgn = *thrdPtr++;
                for (uint b = b_bgn ; b < a ; b++) {
                    results[thrdID] += rho(a, b) * RZ[a] % RZ[b] * 2.0;
                }
                results[thrdID] += rho(a, a) * RZ[a] % RZ[a];
            }
        });
    }

    // attends la fin de chaque thread
    for (uint thrdID = 0 ; thrdID < ALGO_NUM_THREADS ; thrdID++) {
        threads[thrdID].join();
    }


    // libère la mémoire qui n'est plus utilisé
    delete [] RZ;
    free(ind);

    // somme les contributions de chaque thread
    for (uint thrdID = 0 ; thrdID < ALGO_NUM_THREADS ; thrdID++) {
        result += results[thrdID];
    }
    delete [] results;

#endif

    std::cout << timer.toc() << " secondes pour l'algorithme " << ALGO << std::endl;
    return result;
}
