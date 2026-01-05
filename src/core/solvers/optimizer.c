#include "ds_finder.h"

static void	force_kick(t_graph *g, int *solutions_only, int *covers, int *tabu_list, int iter)
{
	static int	idx = 0;
	int			v;

	if (!idx)
		idx = rand() % g->len_solutions;
	else
		idx = (idx + 1) % g->len_solutions;
	v = solutions_only[idx];
	g->solutions[v] = FALSE;
	g->len_solutions--;
	update_covers(g, covers, v, -1);
	tabu_list[v] = iter + 20;
}

static void	add_candidates(t_graph *g, int *covers)
{
	int i;
	int best_v;
	int max_gain;
	int current_gain;
	int j;

	best_v = -1;
	max_gain = 0;
	i = 0;
	while (i < g->v_count)
	{
		if (!g->solutions[i])
		{
			current_gain = 0;
			if (covers[i] == 0)
				current_gain++;
			j = 0;
			while (j < g->nodes[i].degree)
			{
				if (covers[g->nodes[i].neighbors[j]] == 0)
					current_gain++;
				j++;
			}
			if (current_gain > max_gain)
			{
				max_gain = current_gain;
				best_v = i;
			}
		}
		i++;
	}
	if (best_v != -1)
	{
		g->solutions[best_v] = TRUE;
		g->len_solutions++;
		update_covers(g, covers, best_v, 1);
	}
}

void	solve_optimizer(t_graph *g)
{
	int	 	*covers;
	int	 	*solutions_only;
	int	 	*tabu_list;
	t_bool	change;
	int		i;
	int	 	iter;
	int		lock_count;
	int		old_len_solutions;

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
	lock_count = 0;
	old_len_solutions = g->len_solutions;
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
		if (old_len_solutions == g->len_solutions)
			lock_count++;
		else
			lock_count = 0;
		old_len_solutions = g->len_solutions;
		if (!tle && (!change || lock_count >= 2))
		{
			solutions_only = create_solutions_only(g);
			force_kick(g, solutions_only, covers, tabu_list, iter);
			while (!is_covered(g, covers))
				add_candidates(g, covers);
			old_len_solutions = g->len_solutions;
			free(solutions_only);
		}
	}
	free(covers);
	free(tabu_list);
	debug("End Local Search, solutions len %i", g->len_solutions);
}
