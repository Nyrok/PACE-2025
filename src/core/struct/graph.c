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

void remove_neighbor(t_node *node, int target)
{
    int   i;

    i = 0;
    while (i < node->degree)
    {
        if (node->neighbors[i] == target)
        {
            node->neighbors[i] = node->neighbors[node->degree - 1];
            node->degree--;
            return ;
        }
        i++;
    }
}

void	fill_graph(t_graph *graph, int v, int e)
{
	graph->v_count = v;
	graph->e_count = e;
	graph->nodes = ft_calloc(v, sizeof(t_node));
    graph->solutions = ft_calloc(v, sizeof(t_bool));
    graph->actives = malloc(v * sizeof(t_bool));
	if (!graph->nodes || !graph->actives || !graph->solutions)
		exit(EXIT_FAILURE);
	ft_memset(graph->actives, TRUE, v);
}

void	free_graph(t_graph	*graph)
{
	int	i;

	i = 0;
	while (i < (int)graph->v_count)
	{
		free(graph->nodes[i].neighbors);
		i++;
	}
	free(graph->nodes);
	free(graph->solutions);
	free(graph->actives);
}
