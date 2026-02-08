#include "ds_finder.h"

t_bool	try_swap(t_graph *g, t_bool *solutions, int *len_solutions, int *covers, int u, int *tabu_list, int iter,
 	int *buffer)
{
	int		*private_neighbors;
	t_node	*node_v0; // Premier voisin privé de u
	int		p_count;
	int		i, j, k; // Itérateurs
	int		v, w; // v voisin de u, w candidat de remplacement pour u
	t_bool	can_cover_all;
	t_bool	covered_by_w;

	if (tabu_list[u] > iter)
		return (FALSE);
	private_neighbors = buffer;
	p_count = 0;
	// "Voisins privés" : sommets couverts UNIQUEMENT par u (covers == 1).
	// Si on retire u, ce sont eux qui deviennent non couverts.
	if (covers[u] == 1) private_neighbors[p_count++] = u;
	i = 0;
	while (i < g->nodes[u].degree)
	{
		v = g->nodes[u].neighbors[i];
		if (covers[v] == 1)
		{
			private_neighbors[p_count++] = v;
			if (p_count > 15)
				return (FALSE);
		}
		i++;
	}
	// Si aucun voisin privé, u est redondant → on le retire directement (prune déguisé)
	if (p_count == 0)
	{
		solutions[u] = FALSE;
		(*len_solutions)--;
		update_covers(g, covers, u, -1);
		return (TRUE);
	}
	// On cherche le candidat w parmi les voisins du 1er voisin privé,
	// car w doit au minimum être adjacent à ce voisin pour le couvrir
	node_v0 = &g->nodes[private_neighbors[0]];
	i = 0;
	while (i < node_v0->degree)
	{
		w = node_v0->neighbors[i];
		if (!solutions[w] && tabu_list[w] <= iter)
		{
			can_cover_all = TRUE;
			j = 1;
			while (j < p_count)
			{
				covered_by_w = FALSE;
				// w se domine lui-même : si w EST le voisin privé, il le couvre
				if (private_neighbors[j] == w)
					covered_by_w = TRUE;
				else {
					k = 0;
					while (k < g->nodes[w].degree)
					{
						if (g->nodes[w].neighbors[k] == private_neighbors[j])
						{
							covered_by_w = TRUE;
							break ;
						}
					}
				}
				if (!covered_by_w) {
					can_cover_all = FALSE;
					break ;
				}
				j++;
			}
			if (can_cover_all)
			{
				solutions[u] = FALSE;
				update_covers(g, covers, u, -1);
				solutions[w] = TRUE;
				update_covers(g, covers, w, 1);
				// Durée tabou = tenure + aléa → empêche les cycles dans la recherche locale
				tabu_list[u] = iter + TABU_TENURE + (xor_rand() % 10);
				tabu_list[w] = iter + TABU_TENURE + (xor_rand() % 10);
				return (TRUE);
			}
		}
		i++;
	}
	return (FALSE);
}
