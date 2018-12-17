# README IPS Projet 2

Ce projet a pour but de représenter graphique (en 3 dimension, et de manière interactive),
la densité nucléaire local d'un système.

Cette densité doit être fourni dans un format de matrice armadillo, voir fichier **conf/rho.arma**

#### Récupérer le projet
```
git clone http://gitlab.pedago.ensiie.fr/romain.pereira/IPS_2.git
cd IPS_2
make
```

#### Exemple d'utilisation (calcul seulement)
```
./bin/main [-p rho.arma] {-c config.json}
```
Un fichier 'config.json' d'exemple est disponible dans le dossier 'conf/'

#### Développement
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
