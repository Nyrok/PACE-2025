#include "ds_finder.h"

/*
** Recherche locale par tabou : tente d'améliorer la solution gloutonne.
** Pour chaque sommet de la solution, on essaie de le supprimer (prune) ou de l'échanger (swap).
** backed_covers et g->solutions sauvegardent la meilleure solution connue.
*/
void	solve_optimizer(t_graph *g)
{
	int	 	*covers, *backed_covers, *buffer;
	t_bool	*solutions;
	int		len_solutions, old_len_solutions;
	int	 	*tabu_list;
	t_bool	change;
	int		u;
	int	 	iter;
	int		lock_count, degrade_count, stale_count;

	if (tle)
		return ;
	debug("Start Local Search, solutions len %i", g->len_solutions);
	solutions = malloc(g->v_count * sizeof(t_bool));
	if (!solutions)
		return ;
	ft_memcpy(solutions, g->solutions, g->v_count * sizeof(t_bool));
	len_solutions = g->len_solutions;
	covers = init_cover_counts(g);
	backed_covers = malloc(g->v_count * sizeof(int));
	buffer = malloc(g->v_count * sizeof(int));
	if (!covers || !backed_covers || !buffer)
	{
		free(solutions);
		return ;
	}
	ft_memcpy(backed_covers, covers, g->v_count * sizeof(int));
	tabu_list = ft_calloc(g->v_count, sizeof(int));
	if (!tabu_list)
	{
		free(covers);
		free(backed_covers);
		return ;
	}
	iter = 0;
	lock_count = 0; // Itérations sans changement (ni prune ni swap réussi). >= 2 → perturbation
	degrade_count = 0; // Itérations où len_solutions > meilleure connue. >= 2 → restauration
	stale_count = 0; // Perturbations sans que la meilleure solution ne s'améliore. >= 20 → triple perturbation
	old_len_solutions = len_solutions;
	while (!tle)
	{
		iter++;
		change = FALSE;
		u = 0;
		while (!tle && u < g->v_count)
		{
			if (solutions[u])
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
			debug("New best solution found at iter %i, len %i", iter, len_solutions);
			g->len_solutions = len_solutions;
			ft_memcpy(g->solutions, solutions, g->v_count * sizeof(t_bool));
			ft_memcpy(backed_covers, covers, g->v_count * sizeof(int));
			lock_count = 0;
			degrade_count = 0;
			stale_count = 0;
		}
		// Dégradation : len_solutions > meilleure connue (g->len_solutions).
		// Tolérer 2 itérations pour traverser un col avant de restaurer.
		else if (g->type != GRAPH_CORE_PERIPHERY && len_solutions > g->len_solutions)
		{
			degrade_count++;
			if (degrade_count >= 2)
			{
				len_solutions = g->len_solutions;
				ft_memcpy(solutions, g->solutions, g->v_count * sizeof(t_bool));
				ft_memcpy(covers, backed_covers, g->v_count * sizeof(int));
				lock_count = 0;
				degrade_count = 0;
			}
		}
		old_len_solutions = len_solutions;
		// Perturbation si : (aucun changement dans l'itération OU 2 itérations bloquées)
		// ET (on est à la meilleure solution OU ce n'est pas un graphe core-periphery)
		if (!tle && ((iter > 0 && !change) || lock_count >= 2) \
			&& (len_solutions == g->len_solutions || g->type != GRAPH_CORE_PERIPHERY))
		{
			add_candidates(g, solutions, &len_solutions, covers, tabu_list, iter);
			stale_count++;
			if (stale_count >= 20)
			{
				add_candidates(g, solutions, &len_solutions, covers, tabu_list, iter);
				add_candidates(g, solutions, &len_solutions, covers, tabu_list, iter);
				stale_count = 0;
			}
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
