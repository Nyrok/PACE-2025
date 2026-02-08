#ifndef DS_FINDER_H
# define DS_FINDER_H
# define _POSIX_C_SOURCE 200809L
# ifndef DEBUG
#  define DEBUG 1
# endif
// Durée minimale (en itérations) pendant laquelle un sommet est interdit après un swap
# define TABU_TENURE 1
# define TRUE 1
# define FALSE 0

# include <stdio.h>
# include <stdarg.h>
# include <signal.h>
# include <sys/time.h>
# include <time.h>

# include "libft.h"
# include "types.h"
# include "covers.h"
# include "graph.h"
# include "solver.h"

// Flag de timeout levé par SIGTERM (le juge optil.io envoie ce signal quand le temps est écoulé)
extern volatile sig_atomic_t	tle;
extern t_time					start_time;
static unsigned int g_seed = 42;

t_time	gettime(void);
void	debug(char *message, ...);
void	parse_input(t_graph *graph);

/* Générateur pseudo-aléatoire XOR-shift : rapide et déterministe.
** La seed fixe (42) garantit des résultats reproductibles entre les exécutions. */
static inline int	xor_rand(void) {
	g_seed ^= g_seed << 13;
	g_seed ^= g_seed >> 17;
	g_seed ^= g_seed << 5;
	return ((int)(g_seed & 0x7FFFFFFF));
}

#endif