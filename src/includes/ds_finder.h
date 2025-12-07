#ifndef DS_FINDER_H
# define DS_FINDER_H
# define _POSIX_C_SOURCE 200809L

# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <math.h>
# include <stdbool.h>
# include <time.h>
# include <limits.h>

# include "get_next_line.h"
# include "libft.h"

typedef long long	t_ll;
typedef unsigned long long	t_ull;

typedef struct s_node
{
	t_ull	*neighbors;
	t_ull	degree;
	t_ull	capacity;
}	t_node;

typedef struct s_graph
{
	t_ull	v_count;
	t_ull	e_count;
	t_node	*nodes;
}	t_graph;

void	parse_input(t_graph *graph);
void	fill_graph(t_graph	*graph, t_ull v, t_ull e);
void	add_neighbor(t_graph *graph, t_ull e1, t_ull e2);
void	free_graph(t_graph	*graph);
void	solve_graph(t_graph *g);

#endif