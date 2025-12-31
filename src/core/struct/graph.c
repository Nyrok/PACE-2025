#include "ds_finder.h"

void	add_neighbor(t_graph *graph, int e1, int e2)
{
	t_node	*node;
	int	i;

	node = &graph->nodes[e1];
	i = 0;
	while (i < node->degree)
	{
		if (node->neighbors[i] == e2)
			return ;
		i++;
	}
	node->neighbors = realloc(node->neighbors, (node->degree + 1) * sizeof(int));
	node->neighbors[node->degree] = e2;
	node->degree++;
}

void	fill_graph(t_graph *graph, int v, int e)
{
	graph->v_count = v;
	graph->e_count = e;
	graph->nodes = ft_calloc(v, sizeof(t_node));
	graph->v_sorted = malloc(graph->v_count * sizeof(int));
	if (!graph->nodes || !graph->v_sorted)
		exit(EXIT_FAILURE);
}

void	free_graph(t_graph	*graph)
{
	int	i;

	i = 0;
	while (i < graph->v_count)
	{
		free(graph->nodes[i].neighbors);
		i++;
	}
	free(graph->nodes);
	free(graph->solutions);
	free(graph->actives);
}
