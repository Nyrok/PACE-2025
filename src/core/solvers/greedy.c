#include "ds_finder.h"

static double	get_score(t_graph *g, int node_idx, int *curr_degrees)
{
	int		i;
	double	score;
	t_node	*u;

	u = &g->nodes[node_idx];
	i = 0;
	score = 0.0;
	while (i < u->degree)
	{
		int v = u->neighbors[i];
		if (g->actives[v] && curr_degrees[v] > 0)
			score += 1.0 / ((double)curr_degrees[v] || 1);
		i++;
	}
	return score;
}

static int	find_best_candidate(t_graph *g, int *curr_degrees)
{
	int		best_node;
	double	best_score;
	double	current_score;
	int	i;

	best_node = -1;
	best_score = -1.0;
	i = 0;
	while (i < g->v_count)
	{
		if (g->actives[i] && (curr_degrees[i] == 0 || curr_degrees[i] == 1))
			return (i);
		if (g->actives[i])
		{
			current_score = get_score(g, i, curr_degrees);
			if (current_score > best_score)
			{
				best_score = current_score;
				best_node = i;
			}
		}
		i++;
	}
	return (best_node);
}

static int	*init_degrees(t_graph *g)
{
	int	*arr;
	int	i;

	arr = malloc(sizeof(int) * g->v_count);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < g->v_count)
	{
		if (g->actives[i])
			arr[i] = g->nodes[i].degree;
		else
			arr[i] = 0;
		i++;
	}
	return (arr);
}

static void	update_neighbors_score(t_graph *g, int u, int *curr_degrees, t_bool original)
{
	int		i;
	int		v;
	t_node	*node_u;

	node_u = &g->nodes[u];
	i = 0;
	while (i < node_u->degree)
	{
		v = node_u->neighbors[i];
		if (!g->actives[v]) 
		{
			i++;
			continue ;
		}
		if (original)
		{
			g->actives[v] = FALSE;
			curr_degrees[v] = 0;
			update_neighbors_score(g, v, curr_degrees, FALSE);
		}
		else if (curr_degrees[v] > 0)
				curr_degrees[v]--;
		i++;
	}
}

void	solve_greedy(t_graph *graph, t_time *start_time)
{
	int	*curr_degrees;
	int	best_node;

	curr_degrees = init_degrees(graph);
	if (!curr_degrees)
		return ;
	while (gettime() - *start_time < MAX_SOLVE_TIME - TOLERANCE_TIME)
	{
		best_node = find_best_candidate(graph, curr_degrees);
		if (best_node == -1)
			break ;
		graph->solutions[best_node] = TRUE;
		graph->len_solutions++;
		update_neighbors_score(graph, best_node, curr_degrees, TRUE);
		graph->actives[best_node] = FALSE;
		curr_degrees[best_node] = 0;
	}
	free(curr_degrees);
}
