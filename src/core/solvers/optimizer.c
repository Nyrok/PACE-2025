#include "ds_finder.h"

void solve_optimizer(t_graph *g)
{
	int	 	*covers;
	int	 	*tabu_list;
	t_bool	change;
	int		i;
	int	 	iter;

	if (tle)
		return ;
	debug("Start Local Search, solutions len %i", g->len_solutions);
	covers = init_cover_counts(g);
	if (!covers)
		return ;
	tabu_list = ft_calloc(g->v_count, sizeof(int));
	if (!tabu_list)
	{
		free(covers);
		return ;
	}
	iter = 0;
	while (!tle)
	{
		iter++;
		change = FALSE;
		i = 0;
		while (!tle && i < g->v_count)
		{
			if (g->solutions[i])
			{
				if (try_prune(g, covers, i))
					change = TRUE;
				else if (try_swap(g, covers, i, tabu_list, iter))
					change = TRUE;
			}
			i++;
		}
		if (!change)
			break ;
	}
	free(covers);
	free(tabu_list);
	debug("End Local Search, solutions len %i", g->len_solutions);
}
