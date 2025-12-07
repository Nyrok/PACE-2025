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

typedef unsigned long long	t_ull;

typedef struct s_node
{
	t_ull	*adj;
	int		degree;
}	t_node;

typedef struct s_graph
{
	int		v_count;
	int		e_count;
	t_node	*neighbors;
}	t_graph;

void	parse_input(t_graph *graph);
void	fill_graph(t_graph	*graph, int v, int e);
void	free_graph(t_graph	*graph);
void    run_root_strategy(t_graph *graph);

#endif