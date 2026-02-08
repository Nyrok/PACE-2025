#include "ds_finder.h"

__attribute__((hot))
t_bool	try_swap(t_graph *g, t_bool * restrict solutions, int *len_solutions,
		int * restrict covers, int u, int * restrict tabu_list, int iter,
		int *buffer)
{
	int			*private_neighbors;
	int			p_count;
	int			i, j, k;
	int			v, w;
	int			deg;
	const int	*neigh;
	t_bool		can_cover_all;
	t_bool		covered_by_w;

	if (__builtin_expect(tabu_list[u] > iter, 0))
		return (FALSE);
	private_neighbors = buffer;
	p_count = 0;
	// "Voisins privés" : sommets couverts UNIQUEMENT par u (covers == 1).
	// Si on retire u, ce sont eux qui deviennent non couverts.
	if (covers[u] == 1) private_neighbors[p_count++] = u;
	deg = g->nodes[u].degree;
	neigh = g->nodes[u].neighbors;
	i = 0;
	while (i < deg)
	{
		v = neigh[i];
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
	deg = g->nodes[private_neighbors[0]].degree;
	neigh = g->nodes[private_neighbors[0]].neighbors;
	i = 0;
	while (i < deg)
	{
		w = neigh[i];
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
					int deg_w = g->nodes[w].degree;
					const int *neigh_w = g->nodes[w].neighbors;
					k = 0;
					while (k < deg_w)
					{
						if (neigh_w[k] == private_neighbors[j])
						{
							covered_by_w = TRUE;
							break ;
						}
						k++;
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
