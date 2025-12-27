#include "ds_finder.h"

static int	*init_cover_counts(t_graph *g)
{
	int		*covers;
	int	i, j, neighbor;

	covers = ft_calloc(g->v_count, sizeof(int));
	if (!covers) return (NULL);

	i = 0;
	while (i < g->v_count)
	{
		if (g->solutions[i])
		{
			covers[i]++;
			j = 0;
			while (j < g->nodes[i].degree)
			{
				neighbor = g->nodes[i].neighbors[j];
				covers[neighbor]++;
				j++;
			}
		}
		i++;
	}
	return (covers);
}

static void	update_covers(t_graph *g, int *covers, int u, int sign)
{
	int j, neighbor;

	covers[u] += sign;
	j = 0;
	while (j < g->nodes[u].degree)
	{
		neighbor = g->nodes[u].neighbors[j];
		covers[neighbor] += sign;
		j++;
	}
}

static t_bool	try_prune(t_graph *g, int *covers, int u)
{
	int j, neighbor;

	if (covers[u] < 2)
		return (FALSE);
	j = 0;
	while (j < g->nodes[u].degree)
	{
		neighbor = g->nodes[u].neighbors[j];
		if (covers[neighbor] < 2)
			return (FALSE);
		j++;
	}
	g->solutions[u] = FALSE;
	g->len_solutions--;
	update_covers(g, covers, u, -1);
	return (TRUE);
}

static t_bool	try_swap(t_graph *g, int *covers, int u, int *tabu_list, int iter)
{
	t_node	*first_priv;
	int	*private_neighbors;
	int	p_count = 0;
	int	j, v, k, neighbor;
	t_bool	can_cover_all;
	t_bool	covered_by_v;

	if (tabu_list[u] > iter)
		return (FALSE);
	private_neighbors = malloc(sizeof(int) * (g->nodes[u].degree + 1));
	if (!private_neighbors) return (FALSE);

	if (covers[u] == 1) private_neighbors[p_count++] = u;
	j = 0;
	while (j < g->nodes[u].degree)
	{
		neighbor = g->nodes[u].neighbors[j];
		if (covers[neighbor] == 1)
			private_neighbors[p_count++] = neighbor;
		j++;
	}
	if (p_count == 0) 
	{
		free(private_neighbors);
		g->solutions[u] = FALSE;
		g->len_solutions--;
		update_covers(g, covers, u, -1);
		return (TRUE);
	}
	first_priv = &g->nodes[private_neighbors[0]];
	k = 0;
	while (k < first_priv->degree)
	{
		v = first_priv->neighbors[k];
		if (!g->solutions[v] && tabu_list[v] <= iter)
		{
			can_cover_all = TRUE;
			for (int m = 1; m < p_count; m++)
			{
				covered_by_v = FALSE;
				if (private_neighbors[m] == v) covered_by_v = TRUE;
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
				g->solutions[u] = FALSE;
				update_covers(g, covers, u, -1);
				g->solutions[v] = TRUE;
				update_covers(g, covers, v, 1);
				tabu_list[u] = iter + TABU_TENURE;
				tabu_list[v] = iter + TABU_TENURE;
				free(private_neighbors);
				return (TRUE);
			}
		}
		k++;
	}
	free(private_neighbors);
	return (FALSE);
}

void solve_optimizer(t_graph *g, t_time *start_time)
{
	int	 	*covers;
	int	 	*tabu_list;
	t_bool	change;
	int	i;
	int	 	iter;

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
	while (gettime() - *start_time < MAX_SOLVE_TIME - TOLERANCE_TIME)
	{
		iter++;
		change = FALSE;
		i = 0;
		while (i < g->v_count)
		{
			if (g->solutions[i])
			{
				if (try_prune(g, covers, i))
					change = TRUE;
				else if (try_swap(g, covers, i, tabu_list, iter))
					change = TRUE;
			}
			if ((i % 1000 == 0) && (gettime() - *start_time >= MAX_SOLVE_TIME - TOLERANCE_TIME))
				break ;
			i++;
		}
		if (!change)
		{
			g->finished = TRUE;
			break ;
		}
	}
	free(covers);
	free(tabu_list);
}
