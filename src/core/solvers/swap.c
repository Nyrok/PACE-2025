#include "ds_finder.h"

t_bool	try_swap(t_graph *g, t_bool *solutions, int *len_solutions, int *covers, int u, int *tabu_list, int iter)
{
	t_node	*first_priv;
	int		*private_neighbors;
	int		p_count = 0;
	int		j, v, k, neighbor;
	t_bool	can_cover_all;
	t_bool	covered_by_v;

	if (tabu_list[u] > iter)
		return (FALSE);
	private_neighbors = malloc(sizeof(int) * (g->nodes[u].degree + 1));
	if (!private_neighbors) return (FALSE);

	// "Voisins privés" : sommets couverts UNIQUEMENT par u (covers == 1).
	// Si on retire u, ce sont eux qui deviennent non couverts.
	if (covers[u] == 1) private_neighbors[p_count++] = u;
	j = 0;
	while (j < g->nodes[u].degree)
	{
		neighbor = g->nodes[u].neighbors[j];
		if (covers[neighbor] == 1)
			private_neighbors[p_count++] = neighbor;
		j++;
	}
	// Si aucun voisin privé, u est redondant → on le retire directement (prune déguisé)
	if (p_count == 0)
	{
		free(private_neighbors);
		solutions[u] = FALSE;
		(*len_solutions)--;
		update_covers(g, covers, u, -1);
		return (TRUE);
	}
	// On cherche le candidat v parmi les voisins du 1er voisin privé,
	// car v doit au minimum être adjacent à ce voisin pour le couvrir
	first_priv = &g->nodes[private_neighbors[0]];
	k = 0;
	while (k < first_priv->degree)
	{
		v = first_priv->neighbors[k];
		if (!solutions[v] && tabu_list[v] <= iter)
		{
			can_cover_all = TRUE;
			for (int m = 1; m < p_count; m++)
			{
				covered_by_v = FALSE;
				if (private_neighbors[m] == v)
					covered_by_v = TRUE;
				else {
					for (int z = 0; z < g->nodes[v].degree; z++) {
						if (g->nodes[v].neighbors[z] == private_neighbors[m]) {
							covered_by_v = TRUE;
							break;
						}
					}
				}
				if (!covered_by_v) {
					can_cover_all = FALSE;
					break;
				}
			}
			if (can_cover_all)
			{
				solutions[u] = FALSE;
				update_covers(g, covers, u, -1);
				solutions[v] = TRUE;
				update_covers(g, covers, v, 1);
				// Durée tabou = tenure + aléa → empêche les cycles dans la recherche locale
				tabu_list[u] = iter + TABU_TENURE + (xor_rand() % 10);
				tabu_list[v] = iter + TABU_TENURE + (xor_rand() % 10);
				free(private_neighbors);
				return (TRUE);
			}
		}
		k++;
	}
	free(private_neighbors);
	return (FALSE);
}