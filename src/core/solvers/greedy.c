#include "ds_finder.h"

extern volatile sig_atomic_t	tle;

static int	find_best_candidate(int v_count, int *first_active, t_bool *actives)
{
	int	i;

	while (*first_active < v_count && !actives[*first_active])
		(*first_active)++;
	i = *first_active;
	while (i < v_count)
	{
		if (actives[i])
			return (i);
		i++;
	}
	return (-1);
}

static void	update_neighbors_active(t_graph *g, int u, t_bool *actives)
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
	t_bool	*solutions;
	t_bool	*actives;
	int		best_node;
	int		first_active;

	fprintf(stderr, "%lld s - Starting Greedy\n", gettime() - *start_time);
	solutions = ft_calloc(graph->v_count, sizeof(t_bool));
	actives = malloc(graph->v_count * sizeof(t_bool));
	if (!solutions || !actives)
		return ;
	ft_memset(actives, TRUE, graph->v_count * sizeof(t_bool));
	first_active = 0;
	while (!tle && gettime() - *start_time < MAX_SOLVE_TIME - TOLERANCE_TIME)
	{
		best_node = find_best_candidate(graph->v_count, &first_active, actives);
		if (best_node == -1)
		{
			graph->finished = TRUE;
			break ;
		}
		actives[best_node] = FALSE;
		solutions[best_node] = TRUE;
		graph->len_solutions++;
		update_neighbors_active(graph, best_node, actives);
	}
	fprintf(stderr, "%lld s - Finished Greedy\n", gettime() - *start_time);
	graph->actives = actives;
	graph->solutions = solutions;
}
