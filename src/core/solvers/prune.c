#include "ds_finder.h"

t_bool	try_prune(t_graph *g, t_bool *solutions, int *len_solutions, int *covers, int u)
{
	int j, neighbor;

	// Seuil 2 : si on retire u, covers[u] décrémente de 1. Pour que u reste
	// couvert (covers >= 1), il faut covers[u] >= 2 avant le retrait. Idem pour ses voisins.
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
	solutions[u] = FALSE;
	(*len_solutions)--;
	update_covers(g, covers, u, -1);
	return (TRUE);
}