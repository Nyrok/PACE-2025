#include "ds_finder.h"

extern volatile sig_atomic_t	tle;

static int	get_score(t_graph *g, int node_idx, t_bool *actives)
{
	int		i;
	int	score;
	t_node	*u;

	u = &g->nodes[node_idx];
	if (u->degree == 0)
		return (-1);
	i = 0;
	score = 0;
	while (i < u->degree)
	{
		int v = u->neighbors[i];
		if (actives[v] && g->nodes[v].degree > 0)
			score += g->nodes[v].degree;
		i++;
	}
	return (score);
}

static int	*init_scores(t_graph *g, t_bool *actives)
{
	int	*arr;
	int	i;

	arr = malloc(sizeof(int) * g->v_count);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < g->v_count)
	{
		arr[i] = get_score(g, i, actives);
		i++;
	}
	return (arr);
}

static int	find_best_candidate(t_graph *g, int *scores, int *first_active, t_bool *actives)
{
	static int		best_node;
	static int		best_score;
	int	i;

	best_node = -1;
	best_score = g->v_count;
	while (*first_active < g->v_count && !actives[*first_active])
		(*first_active)++;
	i = *first_active;
	while (i < g->v_count)
	{
		if (actives[i] && scores[i] < best_score)
		{
			best_score = scores[i];
			best_node = i;
		}
		if (best_node >= 0 && best_score <= 0)
			return (best_node);
		else if (best_score == 1)
			return (g->nodes[best_node].neighbors[0]);
		i++;
	}
	return (best_node);
}

static void	update_neighbors_score(t_graph *g, int u, t_bool *actives)
{
	int		i;
	int		v;
	t_node	*node_u;

	node_u = &g->nodes[u];
	i = 0;
	while (i < node_u->degree)
	{
		v = node_u->neighbors[i];
		if (actives[v]) 
			actives[v] = FALSE;
		i++;
	}
}

void	solve_greedy(t_graph *graph, t_time *start_time)
{
	int		*scores;
	t_bool	*solutions;
	t_bool	*actives;
	int		best_node;
	int		first_active;

	solutions = ft_calloc(graph->v_count, sizeof(t_bool));
	actives = malloc(graph->v_count * sizeof(t_bool));
	scores = init_scores(graph, actives);
	if (!scores)
		return ;
	ft_memset(actives, TRUE, graph->v_count * sizeof(t_bool));
	first_active = 0;
	while (!tle && gettime() - *start_time < MAX_SOLVE_TIME - TOLERANCE_TIME)
	{
		best_node = find_best_candidate(graph, scores, &first_active, actives);
		if (best_node == -1)
		{
			graph->finished = TRUE;
			break ;
		}
		actives[best_node] = FALSE;
		solutions[best_node] = TRUE;
		graph->len_solutions++;
		update_neighbors_score(graph, best_node, actives);
	}
	free(scores);
	fprintf(stderr, "Finished greedy on %lld/%lld s\n", gettime() - *start_time, MAX_SOLVE_TIME - TOLERANCE_TIME);
	graph->actives = actives;
	graph->solutions = solutions;
}
