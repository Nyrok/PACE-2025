[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/dVaZWQFC)
# Projet 2025 Dominating Set

[Le sujet](https://www.lamsade.dauphine.fr/~sikora/ens/graphes/projet2025/)

## AUTHOR

Hamza KONTE

## Optilio

`dauphine_l3miage_hamza`

## USAGE
```
cmake .
make
./ds_finder < in.gr > out.sol
```

## Docker

Deux conteneurs Docker sont disponibles via `docker-compose` :

### Conteneur de développement (`ds-dev`)

Environnement complet avec gcc-13, valgrind, vim, et Java (pour le vérificateur).
Les répertoires `src/`, `testset/` et `real-instances/` sont montés en volumes.

```bash
docker compose up -d ds-dev
docker exec -it ds-dev bash

# Dans le conteneur :
cmake . && make
./ds_finder < tmp/testset/lite_1.gr
```

### Conteneur de build statique (`ds-build`)

Compile un binaire statique Linux/amd64 (pour soumission sur optil.io) :

```bash
docker start ds-build
```

Le binaire statique est généré dans `src/` via le target `binary_solution`.

## Visualizer

Outils Python pour visualiser les graphes et les solutions. Installation des dépendances :

```bash
pip install -r visualizer/requirements.txt
```

### Visualisation interactive (matplotlib)

Affiche le graphe avec les sommets de la solution en rouge :

```bash
python3 visualizer/graph_visualizer.py <graphe.gr> [solution.sol]
```

### Export Gephi (GEXF)

Convertit le graphe en fichier `.gexf` pour analyse dans [Gephi](https://gephi.org/) :

```bash
python3 visualizer/gefx_converter.py <graphe.gr> <solution.sol>
# Génère graph.gexf dans le répertoire courant
```

## Tests & Vérification

### Test unitaire rapide

```bash
cd src && ./ds_finder < ../testset/lite_1.gr
```

### Suite de tests complète

Le script `testall.sh` exécute le solveur sur toutes les instances d'un répertoire, vérifie les solutions avec `ds_verifier-1.0.jar`, et produit un fichier `results.csv` :

```bash
./testall.sh <timeout> <programme> <répertoire_instances>
# Exemple :
./testall.sh 300s ./src/ds_finder real-instances
```

Format de sortie (`results.csv`) :
```
instance ; valeur   (solution valide)
instance ; TO       (timeout)
instance ; KO       (solution invalide)
instance ; ERR      (erreur d'exécution)
```

### Vérification manuelle

```bash
java -jar ds_verifier-1.0.jar <graphe.gr> <solution.sol>
```

## Structure du projet

```
.
├── src/
│   ├── core/
│   │   ├── main.c                  # Pipeline principal + gestion SIGTERM
│   │   ├── solvers/
│   │   │   ├── solver.c            # Routage vers la bonne stratégie
│   │   │   ├── greedy.c            # Glouton par degré
│   │   │   ├── periphery_greedy.c  # Glouton spécialisé core-periphery
│   │   │   ├── optimizer.c         # Recherche tabou (boucle principale)
│   │   │   ├── prune.c             # Suppression de sommets redondants
│   │   │   ├── swap.c              # Échange de sommets
│   │   │   ├── perturbation.c      # Échappement des optima locaux
│   │   │   └── sorter.c            # Tri par degré
│   │   ├── struct/
│   │   │   ├── graph.c             # Classification du graphe
│   │   │   └── covers.c            # Compteur de couverture
│   │   └── utils/
│   │       ├── parser.c            # Lecture format DIMACS
│   │       ├── time.c              # Utilitaires de temps
│   │       └── logger.c            # Logs de debug
│   ├── includes/                   # Headers
│   ├── libs/libft/                 # Librairie faite dans mon cursus à 42
│   └── CMakeLists.txt
├── visualizer/                     # Outils de visualisation Python
├── testset/                        # Instances de test légères
├── real-instances/                 # 100 instances d'optimisation
├── docker-compose.yml
├── build.Dockerfile                # Image de build statique
├── dev.Dockerfile                  # Image de développement
├── testall.sh                      # Script de benchmark
└── ds_verifier-1.0.jar             # Vérificateur officiel
```
