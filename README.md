# IPS Projet 2

Ce projet a pour but de représenter graphique (en 3 dimension, et de manière interactive),
la densité nucléaire local d'un système.

Cette densité doit être fourni dans un format de matrice armadillo, voir fichier **rho.arma**

## Récupérer le projet

```
git clone http://gitlab.pedago.ensiie.fr/romain.pereira/IPS_2.git
cd IPS_2
make
```

## Utilisation

```
./bin/main [-p rho.arma] {-c config.json} {-m out.mat} {-r out.raw} {-d out.df3} {-q}
```
- rho.arma : le fichier de densité
- config.json : la configuration du calcul (voir 'config.json')
- out.mat : fichier de sortie du calcul dans le plan theta=0
- out.raw : fichier de sortie en format .raw (blender)
- out.df3 : fichier de sortie en format .df3 (povray)

## Exemple d'utilisation (calcul + affichage matplotlib plan 2D)

```
bin/main -p rho.arma -c config.json -m out.mat
python3.6 plot/pyplot/plot.py < out.mat
```

## Exemple d'utilisation (calcul + affichage 3D povray)

```
./bin/main -p rho.arma -c config.json -d plot/povray/out.df3
cd plot/povray
povray +A0.0001 -W800 -H600 +P +Q11 visu.pov
```

## Développement
Règles du Makefile

| Nom de la règle | Description de la règle                               |
|-----------------|-------------------------------------------------------|
| **bin/main**    | Compile le programme dans bin/main                    |
| **clean**       | Supprime les fichiers objets (.cpp compilés en .o)    |
| **fclean**      | 'clean' puis supprime le programme                    |
| **docs**        | Génère la documentation dans le dossier docs          |
| **help**        | Affiche l'aide d'utilisation du Makefile              |
| **tests**       | Lance les tests unitaires                             |
| **astyle**      | Formatte, indente et beautifie le code source         |

## Benchmarking
Pour tester l'implémentation 'i' de l'algorithme de résolution, veuillez
définir la variable 'ALGO' du Makefile à 'i'

Exemple:
```
> make ALGO=1
```

Les optimisations se cumulent par numéro d'algorithme croissant.
L'algorithme **i + 1** implémente aussi les optimisations de l'algorithme **i**

Voici la table des algorithmes:

| Numéro de l'algorithme | Détail de l'implémentation                                                                                      |
|------------------------|-----------------------------------------------------------------------------------------------------------------|
|      **0**             | Approche naïve : aucunes optimisations                                                                          |
|      **1**             | Déplacement phi(a) 'en haut à gauche' (https://dubrayn.github.io/IPS-PROD/sumoptim.html#16)                     |
|      **2**             | Déplacement R(a) et R(b) 'en haut à gauche'                                                                     | 
|      **3**             | Suppression d'une profondeur de boucle (ma != mb, alors rho(a, b))                                              | 
|      **4**             | Pré-calcul/pré-sommation de R * Z (https://dubrayn.github.io/IPS-PROD/sumoptim.html#17)                         | 
|      **5**             | Utilisation de la symétrie rho(a, b) = rho(b, a) pour réduire les calculs + linéarisation de la boucle sur 'b'  | 
|      **6**             | Linéarisation trois-passe de la boucle sur 'a' (https://dubrayn.github.io/IPS-PROD/sumoptim.html#21)            |
|      **7**             | Multithreading (chaque thread fait une partie intermédiaire du calcul, le parent somme les résultats            |


## Résultats
![alt text](https://raw.githubusercontent.com/rpereira-dev/IPS-PROD/master/plot/blender/output.png)
