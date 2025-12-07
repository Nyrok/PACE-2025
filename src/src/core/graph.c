#include "ds_finder.h"

void	fill_graph(t_graph	*graph, int v, int e)
{
	int		i;

	graph->v_count = v;
	graph->e_count = e;
	graph->neighbors = ft_calloc(v, sizeof(t_node));
	if (!graph->neighbors)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < v)
	{
		graph->neighbors[i].adj = ft_calloc(v, sizeof(t_ull));
		if (!graph->neighbors[i].adj)
		{
			while (--i >= 0)
				free(graph->neighbors[i].adj);
			free(graph->neighbors);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	free_graph(t_graph	*graph)
{
	int		i;

	i = 0;
	while (i < graph->v_count)
	{
		free(graph->neighbors[i].adj);
		i++;
	}
	free(graph->neighbors);
}
