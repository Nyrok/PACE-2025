#ifndef GRAPH_H
# define GRAPH_H

# include "types.h"

t_graph_type	get_graph_type(t_graph *g);
void			fill_graph(t_graph *graph, int v, int e);
void			add_neighbor(t_graph *graph, int e1, int e2);
void			free_graph(t_graph *graph);
void			sort_graph(t_graph *graph, int **v_sorted);

#endif