#ifndef SOLVER_H
# define SOLVER_H

# include "types.h"

void	solve_graph(t_graph *graph);
void	solve_optimizer(t_graph *g);
void	solve_greedy(t_graph *graph);
void	solve_periphery_greedy(t_graph *graph);
t_bool	try_prune(t_graph *g, int *covers, int u);
t_bool	try_swap(t_graph *g, int *covers, int u, int *tabu_list, int iter);

#endif