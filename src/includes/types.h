#ifndef TYPES_H
# define TYPES_H

typedef long long			t_time;
typedef unsigned char		t_bool;

typedef enum e_graph_type
{
	GRAPH_UNKNOWN = 0,			// Type non identifié
	GRAPH_STAR = 1,				// Une seule étoile (1 hub connectant tout le monde)
	GRAPH_MULTI_STAR = 2,		// Plusieurs étoiles disjointes (votre cas probable)
	GRAPH_CORE_PERIPHERY = 3,	// Un noyau dense et une périphérie de feuilles
	GRAPH_GRID_2D = 4,			// Maillage type grille (ex: pixels, rues)
	GRAPH_RING = 5,				// Anneau (chaque nœud a exactement 2 voisins)
	GRAPH_COMPLETE = 6,			// Clique (tout le monde est connecté à tout le monde)
	GRAPH_SCALE_FREE = 7,		// Loi de puissance (ex: Internet, réseaux sociaux)
	GRAPH_TREE = 8,				// Arbre pur (pas de cycles)
	GRAPH_ERDOS_RENYI = 9,		// Aléatoire uniforme (chaque arête a une probabilité p)
}   t_graph_type;

typedef struct s_node
{
	int	*neighbors; // Tableau dynamique des voisins (indices des sommets adjacents)
	int	degree; // Nombre de voisins (degré du sommet)
	int	capacity; // Metadata pour savoir la taille à allouer pour neighbors
}	t_node;

typedef struct s_graph
{
	int				v_count; // nombre de sommets
	int				e_count; // nombre d'arêtes
	t_graph_type	type; // classification du graphe pour choisir la meilleure stratégie de résolution
	t_node			*nodes; // nodes[i] = structure du sommet i (degré, voisins, etc.)
	t_bool			*solutions;	// solutions[i] = TRUE si le sommet i fait partie de l'ensemble dominant
	int				len_solutions; // nombre de sommets dominants
}	t_graph;

#endif