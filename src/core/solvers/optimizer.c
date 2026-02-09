#include "ds_finder.h"

/*
** Perturbation : retire aléatoirement un sommet de la solution, ce qui crée des "trous",
** puis comble les trous en ajoutant les voisins non couverts.
** Casse les plateaux et permet d'explorer une nouvelle zone de l'espace de recherche.
*/
__attribute__((hot))
static void	add_candidates(t_graph *g, t_bool *solutions, int *len_solutions,
		int *covers, int *tabu_list, int iter)
{
	int	u;
	int	i;
	int	*neighbors;

	do {
		u = xor_rand() % g->v_count;
	} while (!solutions[u] || tabu_list[u] > iter);
	solutions[u] = FALSE;
	(*len_solutions)--;
	tabu_list[u] = iter + 20;
	update_covers(g, covers, u, -1);
	neighbors = g->nodes[u].neighbors;
	i = 0;
	while (i < g->nodes[u].degree)
	{
		if (covers[neighbors[i]] == 0)
		{
			solutions[neighbors[i]] = TRUE;
			(*len_solutions)++;
			update_covers(g, covers, neighbors[i], 1);
		}
		i++;
	}
	// Si après la boucle, u n'est toujours pas couvert (cas où tous ses voisins
	// étaient déjà couverts par d'autres), la solution est invalide.
	// On doit ajouter un voisin pour couvrir u.
	if (covers[u] == 0 && g->nodes[u].degree > 0)
	{
		int v = neighbors[0];
		if (!solutions[v])
		{
			solutions[v] = TRUE;
			(*len_solutions)++;
			update_covers(g, covers, v, 1);
		}
	}
	// Si u est isolé (degree == 0) et non couvert → seule option : se réinsérer
	else if (covers[u] == 0)
	{
		solutions[u] = TRUE;
		(*len_solutions)++;
		update_covers(g, covers, u, 1);
	}
}

/*
** Recherche locale par tabou : tente d'améliorer la solution gloutonne.
** Pour chaque sommet de la solution, on essaie de le supprimer (prune) ou de l'échanger (swap).
** backed_covers et g->solutions sauvegardent la meilleure solution connue.
*/
__attribute__((flatten, hot))
void	solve_optimizer(t_graph *g)
{
	int	 	*covers, *backed_covers, *buffer;
	t_bool	*solutions;
	int		len_solutions, old_len_solutions;
	int	 	*tabu_list;
	t_bool	change;
	int		u;
	int	 	iter;
	int		lock_count; // Itérations sans changement (ni prune ni swap réussi). >= 2 → perturbation
	int		v_count;

	if (tle)
		return ;
	v_count = g->v_count;
	debug("Start Local Search, solutions len %i", g->len_solutions);
	solutions = malloc(v_count * sizeof(t_bool));
	if (!solutions)
		return ;
	ft_memcpy(solutions, g->solutions, v_count * sizeof(t_bool));
	len_solutions = g->len_solutions;
	covers = init_cover_counts(g);
	backed_covers = malloc(v_count * sizeof(int));
	buffer = malloc(v_count * sizeof(int));
	if (!covers || !backed_covers || !buffer)
	{
		free(solutions);
		return ;
	}
	ft_memcpy(backed_covers, covers, v_count * sizeof(int));
	tabu_list = ft_calloc(v_count, sizeof(int));
	if (!tabu_list)
	{
		free(covers);
		free(backed_covers);
		return ;
	}
	iter = 0;
	lock_count = 0;
	old_len_solutions = len_solutions;
	while (!tle)
	{
		iter++;
		change = FALSE;
		u = 0;
		while (!tle && u < v_count)
		{
			// La majorité des sommets ne sont PAS dans D → branch hint unlikely
			if (__builtin_expect(solutions[u], 0))
			{
				if (try_prune(g, solutions, &len_solutions, covers, u))
					change = TRUE;
				else if (try_swap(g, solutions, &len_solutions, covers, u, tabu_list, iter, buffer))
					change = TRUE;
			}
			u++;
		}
		if (old_len_solutions == len_solutions)
			lock_count++;
		else if (len_solutions < g->len_solutions)
		{
			g->len_solutions = len_solutions;
			ft_memcpy(g->solutions, solutions, v_count * sizeof(t_bool));
			ft_memcpy(backed_covers, covers, v_count * sizeof(int));
			lock_count = 0;
		}
		// Si la solution s'est dégradée, on restaure la meilleure connue (sauf core-periphery)
		else if (g->type != GRAPH_CORE_PERIPHERY && len_solutions > g->len_solutions)
		{
			len_solutions = g->len_solutions;
			ft_memcpy(solutions, g->solutions, v_count * sizeof(t_bool));
			ft_memcpy(covers, backed_covers, v_count * sizeof(int));
			lock_count = 0;
		}
		old_len_solutions = len_solutions;
		// Perturbation si : (aucun changement dans l'itération OU 2 itérations bloquées)
		// ET (on est à la meilleure solution OU ce n'est pas un graphe core-periphery)
		if (!tle && ((iter > 0 && !change) || lock_count >= 2) \
			&& (len_solutions == g->len_solutions || g->type != GRAPH_CORE_PERIPHERY))
		{
			add_candidates(g, solutions, &len_solutions, covers, tabu_list, iter);
			old_len_solutions = len_solutions;
			lock_count = 0;
		}
	}
	free(covers);
	free(tabu_list);
	free(solutions);
	free(backed_covers);
	free(buffer);
	debug("End Local Search, solutions len %i", g->len_solutions);
}
