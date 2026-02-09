#ifndef SOLVER_H
# define SOLVER_H

# include "types.h"

void	solve_graph(t_graph *graph);
void	solve_optimizer(t_graph *graph);
void	solve_greedy(t_graph *graph);
void	solve_periphery_greedy(t_graph *graph);
t_bool	try_prune(t_graph *graph, t_bool * restrict solutions, int *len_solutions, int * restrict covers, int u);
t_bool	try_swap(t_graph *graph, t_bool * restrict solutions, int *len_solutions, int * restrict covers, int u, int * restrict tabu_list, int iter, int *buffer);
void	add_missing_solutions(t_graph *graph, t_bool *actives);

#endif