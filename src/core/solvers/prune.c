#include "ds_finder.h"

t_bool	try_prune(t_graph *g, t_bool *solutions, int *len_solutions, int *covers, int u)
{
	int j, neighbor;

	if (covers[u] < 2)
		return (FALSE);
	j = 0;
	while (j < g->nodes[u].degree)
	{
		neighbor = g->nodes[u].neighbors[j];
		if (covers[neighbor] < 2)
			return (FALSE);
		j++;
	}
	check_timeout(g);
	solutions[u] = FALSE;
	(*len_solutions)--;
	update_covers(g, covers, u, -1);
	return (TRUE);
}