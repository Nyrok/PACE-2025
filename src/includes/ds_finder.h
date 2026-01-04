#ifndef DS_FINDER_H
# define DS_FINDER_H
# define _POSIX_C_SOURCE 200809L
# ifndef DEBUG
#  define DEBUG 1
# endif
# define TABU_TENURE 2
# define TRUE 1
# define FALSE 0

# include <stdio.h>
# include <stdarg.h>
# include <signal.h>
# include <sys/time.h>
# include <time.h>

# include "libft.h"

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
	GRAPH_ERDOS_RENYI = 9,			// Aléatoire uniforme (chaque arête a une probabilité p)
}   t_graph_type;

typedef struct s_node
{
	int	*neighbors;
	int	degree;
	int	capacity;
}	t_node;

typedef struct s_graph
{
	int				v_count;
	int				e_count;
	t_graph_type	type;
	t_node			*nodes;
	t_bool			*solutions;
	t_bool			*actives;
	int				*v_sorted;
	int				len_solutions;
	t_bool			finished;
}	t_graph;

extern volatile sig_atomic_t	tle;
extern t_time					start_time;

t_time			gettime(void);
void			debug(char *message, ...);
void			parse_input(t_graph *graph);
void			fill_graph(t_graph	*graph, int v, int e);
void			add_neighbor(t_graph *graph, int e1, int e2);
void			free_graph(t_graph	*graph);
void			sort_graph(t_graph *graph);
void			solve_graph(t_graph *graph);
void			solve_optimizer(t_graph *g);
void			solve_greedy(t_graph *graph);
void			solve_periphery_greedy(t_graph *graph);
t_bool			try_prune(t_graph *g, int *covers, int u);
t_bool			try_swap(t_graph *g, int *covers, int u, int *tabu_list, int iter);
int				*init_cover_counts(t_graph *g);
t_bool			is_covered(t_graph *g, int *covers);
void			update_covers(t_graph *g, int *covers, int u, int val);
void			exit_print_solution(t_graph *graph);
t_graph_type	get_graph_type(t_graph *g);

static inline void check_timeout(t_graph *graph) {
    if (tle) exit_print_solution(graph);
}

#endif