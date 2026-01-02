#include "ds_finder.h"

static t_node *nodes_ctx;

static int	compare_degrees(const void *a, const void *b)
{
	int		index_a;
	int		index_b;
	double	degree_a;
	double	degree_b;

	index_a = *(int *)a;
	index_b = *(int *)b;
	degree_a = nodes_ctx[index_a].degree;
	degree_b = nodes_ctx[index_b].degree;
	return (degree_a - degree_b); 
}

void	sort_graph(t_graph *graph)
{
	int i;

	debug("Start sorting graph");
	i = 0;
	while (i < graph->v_count)
	{
		graph->v_sorted[i] = i;
		i++;
	}
	nodes_ctx = graph->nodes;
	qsort(graph->v_sorted, graph->v_count, sizeof(int), compare_degrees);
	debug("End sorting graph");
}
