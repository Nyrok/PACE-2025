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
# include "types.h"
# include "covers.h"
# include "graph.h"
# include "solver.h"

extern volatile sig_atomic_t	tle;
extern t_time					start_time;

t_time	gettime(void);
void	debug(char *message, ...);
void	parse_input(t_graph *graph);
void	exit_print_solution(t_graph *graph);

static inline void check_timeout(t_graph *graph) {
    if (tle) exit_print_solution(graph);
}

#endif