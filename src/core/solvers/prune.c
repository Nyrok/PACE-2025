#include "ds_finder.h"

__attribute__((hot))
t_bool	try_prune(t_graph *g, t_bool * restrict solutions, int *len_solutions,
		int * restrict covers, int u)
{
	int			i;
	int			deg;
	const int	*neigh;

	// Seuil 2 : si on retire u, covers[u] décrémente de 1. Pour que u reste
	// couvert (covers >= 1), il faut covers[u] >= 2 avant le retrait. Idem pour ses voisins.
	if (covers[u] < 2)
		return (FALSE);
	deg = g->nodes[u].degree;
	neigh = g->nodes[u].neighbors;
	i = 0;
	while (i < deg)
	{
		if (covers[neigh[i]] < 2)
			return (FALSE);
		i++;
	}
	solutions[u] = FALSE;
	(*len_solutions)--;
	update_covers(g, covers, u, -1);
	return (TRUE);
}