#ifndef DS_FINDER_H
# define DS_FINDER_H
# define _POSIX_C_SOURCE 200809L
# ifndef MAX_SOLVE_TIME
#  define MAX_SOLVE_TIME 300LL
# endif
# define TOLERANCE_TIME 10LL
# define TABU_TENURE 2
# define TRUE 1
# define FALSE 0

# include <signal.h>
# include <sys/time.h>

# include "get_next_line.h"
# include "libft.h"

typedef long long			t_ll;
typedef long long			t_time;
typedef unsigned long long	t_ull;
typedef unsigned char		t_bool;

typedef struct s_node
{
	t_ull	*neighbors;
	t_ull	degree;
}	t_node;

typedef struct s_graph
{
	t_ull	v_count;
	t_ull	e_count;
	t_node	*nodes;
	t_bool	*solutions;
	t_bool	*actives;
	t_ull	len_solutions;
	t_bool	finished;
}	t_graph;

t_time	gettime(void);
void	parse_input(t_graph *graph);
void	fill_graph(t_graph	*graph, t_ull v, t_ull e);
void	add_neighbor(t_graph *graph, t_ull e1, t_ull e2);
void	remove_neighbor(t_node *node, t_ull target);
void	free_graph(t_graph	*graph);
void	solve_graph(t_graph *graph, t_time *start_time);
void	solve_optimizer(t_graph *g, t_time *start_time);
void	solve_greedy(t_graph *graph, t_time *start_time);

#endif