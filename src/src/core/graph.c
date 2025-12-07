#include "ds_finder.h"

void	add_neighbor(t_graph *graph, t_ull e1, t_ull e2)
{
	t_node	*node;
	t_ull	i;

	node = &graph->nodes[e1];
	i = 0;
	while (i < node->degree)
	{
		if (node->neighbors[i] == e2)
			return ;
		i++;
	}
	node->neighbors = realloc(node->neighbors, (node->degree + 1) * sizeof(t_ull));
	node->neighbors[node->degree] = e2;
	node->degree++;
}

void	fill_graph(t_graph *graph, t_ull v, t_ull e)
{
	t_ll	i;

	graph->v_count = v;
	graph->e_count = e;
	graph->nodes = ft_calloc(v, sizeof(t_node));
	if (!graph->nodes)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < (t_ll)v)
	{
		graph->nodes[i].neighbors = ft_calloc(0, sizeof(t_ull));
		graph->nodes[i].capacity = 10;
		if (!graph->nodes[i].neighbors)
		{
			while (--i >= 0)
				free(graph->nodes[i].neighbors);
			free(graph->nodes);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	free_graph(t_graph	*graph)
{
	t_ll	i;

	i = 0;
	while (i < (t_ll)graph->v_count)
	{
		free(graph->nodes[i].neighbors);
		i++;
	}
	free(graph->nodes);
}
