#include "ds_finder.h"

t_graph	*create_graph(void)
{
	t_graph	*graph;

	graph = ft_calloc(1, sizeof(t_graph));
	if (!graph)
		exit(EXIT_FAILURE);
	return (graph);
}

void	fill_graph(t_graph	**graph, int v, int e)
{
	int		i;

	(*graph)->v_count = v;
	(*graph)->e_count = e;
	(*graph)->neighbors = ft_calloc(v, sizeof(int *));
	if (!(*graph)->neighbors)
	{
		free(*graph);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < v)
	{
		(*graph)->neighbors[i] = ft_calloc(v, sizeof(int));
		if (!(*graph)->neighbors[i])
		{
			while (--i >= 0)
				free((*graph)->neighbors[i]);
			free((*graph)->neighbors);
			free(*graph);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}