#include "ds_finder.h"

t_bool	try_prune(t_graph *g, t_bool *solutions, int *len_solutions, int *covers, int u)
{
	int i; // Itérateur
	int	v; // Voisin de u

	// Seuil 2 : si on retire u, covers[u] décrémente de 1. Pour que u reste
	// couvert (covers >= 1), il faut covers[u] >= 2 avant le retrait. Idem pour ses voisins.
	if (covers[u] < 2)
		return (FALSE);
	i = 0;
	while (i < g->nodes[u].degree)
	{
		v = g->nodes[u].neighbors[i];
		if (covers[v] < 2)
			return (FALSE);
		i++;
	}
	solutions[u] = FALSE;
	(*len_solutions)--;
	update_covers(g, covers, u, -1);
	return (TRUE);
}