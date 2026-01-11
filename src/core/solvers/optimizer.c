#include "ds_finder.h"

static void	add_candidates(t_graph *g, t_bool *solutions, int *len_solutions, int *covers, int *tabu_list, int iter)
{
	int	v;
	int	i;

	do {
		v = rand() % g->v_count;
	} while (solutions[v]);
	i = 0;
	while (i < g->nodes[v].degree)
	{
		if (!solutions[g->nodes[v].neighbors[i]])
		{
			solutions[g->nodes[v].neighbors[i]] = TRUE;
			(*len_solutions)++;
			update_covers(g, covers, g->nodes[v].neighbors[i], 1);
		}
		i++;
	}
	solutions[v] = TRUE;
	(*len_solutions)++;
	update_covers(g, covers, v, 1);
	tabu_list[v] = iter + 20;
}

void	solve_optimizer(t_graph *g)
{
	int	 	*covers, *backed_covers;
	t_bool	*solutions;
	int		len_solutions, old_len_solutions;
	int	 	*tabu_list;
	t_bool	change;
	int		i;
	int	 	iter;
	int		lock_count;

	if (tle)
		return ;
	debug("Start Local Search, solutions len %i", g->len_solutions);
	solutions = malloc(g->v_count * sizeof(t_bool));
	ft_memcpy(solutions, g->solutions, g->v_count * sizeof(t_bool));
	len_solutions = g->len_solutions;
	covers = init_cover_counts(g);
	backed_covers = malloc(g->v_count * sizeof(int));
	if (!covers || !backed_covers)
		return ;
	ft_memcpy(backed_covers, covers, g->v_count * sizeof(int));
	tabu_list = ft_calloc(g->v_count, sizeof(int));
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
		i = 0;
		while (!tle && i < g->v_count)
		{
			if (solutions[i])
			{
				if (try_prune(g, solutions, &len_solutions, covers, i))
					change = TRUE;
				else if (try_swap(g, solutions, &len_solutions, covers, i, tabu_list, iter))
					change = TRUE;
			}
			i++;
		}
		if (old_len_solutions == len_solutions)
			lock_count++;
		else if (len_solutions < g->len_solutions)
		{
			g->len_solutions = len_solutions;
			ft_memcpy(g->solutions, solutions, g->v_count * sizeof(t_bool));
			ft_memcpy(backed_covers, covers, g->v_count * sizeof(int));
			lock_count = 0;
		}
		else if (g->type != GRAPH_CORE_PERIPHERY && len_solutions > g->len_solutions)
		{
			len_solutions = g->len_solutions;
			ft_memcpy(solutions, g->solutions, g->v_count * sizeof(t_bool));
			ft_memcpy(covers, backed_covers, g->v_count * sizeof(int));
			lock_count = 0;
		}
		old_len_solutions = len_solutions;
		if (!tle && ((iter > 0 && !change) || lock_count >= 2))
		{
			add_candidates(g, solutions, &len_solutions, covers, tabu_list, iter);
			old_len_solutions = len_solutions;
		}
	}
	free(covers);
	free(tabu_list);
	free(solutions);
	free(backed_covers);
	debug("End Local Search, solutions len %i", g->len_solutions);
}
