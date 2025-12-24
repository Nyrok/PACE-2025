#include "ds_finder.h"

static int	*init_cover_counts(t_graph *g)
{
	int		*covers;
	t_ull	i, j, neighbor;

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

static void	update_covers(t_graph *g, int *covers, t_ull u, int sign)
{
	t_ull j, neighbor;

	covers[u] += sign;
	j = 0;
	while (j < g->nodes[u].degree)
	{
		neighbor = g->nodes[u].neighbors[j];
		covers[neighbor] += sign;
		j++;
	}
}

static bool	try_prune(t_graph *g, int *covers, t_ull u)
{
	t_ull j, neighbor;

	if (covers[u] < 2)
		return (false);
	j = 0;
	while (j < g->nodes[u].degree)
	{
		neighbor = g->nodes[u].neighbors[j];
		if (covers[neighbor] < 2)
			return (false);
		j++;
	}
	g->solutions[u] = false;
	g->len_solutions--;
	update_covers(g, covers, u, -1);
	return (true);
}

static bool try_swap(t_graph *g, int *covers, t_ull u)
{
	t_ull	*private_neighbors;
	t_ull	p_count = 0;
	t_ull	j, v, k, neighbor;
	bool	can_cover_all;

	private_neighbors = malloc(sizeof(t_ull) * (g->nodes[u].degree + 1));
	if (!private_neighbors) return (false);

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
		g->solutions[u] = false;
		g->len_solutions--;
		update_covers(g, covers, u, -1);
		return (true);
	}
	t_node *first_priv = &g->nodes[private_neighbors[0]];
	k = 0;
	while (k < first_priv->degree)
	{
		v = first_priv->neighbors[k];
		if (!g->solutions[v])
		{
			can_cover_all = true;
			for (t_ull m = 1; m < p_count; m++)
			{
				bool covered_by_v = false;
				if (private_neighbors[m] == v) covered_by_v = true;
				else {
					 for (t_ull z = 0; z < g->nodes[v].degree; z++) {
						if (g->nodes[v].neighbors[z] == private_neighbors[m]) {
							covered_by_v = true;
							break;
						}
					 }
				}
				if (!covered_by_v) {
					can_cover_all = false;
					break;
				}
			}

			if (can_cover_all)
			{
				g->solutions[u] = false;
				update_covers(g, covers, u, -1);
				g->solutions[v] = true;
				update_covers(g, covers, v, 1);
				free(private_neighbors);
				return (true);
			}
		}
		k++;
	}

	free(private_neighbors);
	return (false);
}

void solve_optimizer(t_graph *g, t_time *start_time)
{
	int		*covers;
	bool	change;
	t_ull	i;

	covers = init_cover_counts(g);
	if (!covers) return ;

	while (gettime() - *start_time < MAX_SOLVE_TIME - TOLERANCE_TIME)
	{
		change = false;
		i = 0;
		while (i < g->v_count)
		{
			if (g->solutions[i])
			{
				if (try_prune(g, covers, i))
					change = true;
				else if (try_swap(g, covers, i))
					change = true;
			}
			if ((i % 1000 == 0) || (gettime() - *start_time >= MAX_SOLVE_TIME - TOLERANCE_TIME))
				break ;
			i++;
		}
		if (!change)
			break ;
	}
	free(covers);
	g->finished = true;
}
