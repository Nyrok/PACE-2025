#include "ds_finder.h"

// Variable globale nécessaire car qsort n'accepte pas de contexte supplémentaire
// dans sa fonction de comparaison
static t_node	*nodes_ctx;

static int	compare_degrees(const void *a, const void *b)
{
	int	index_a;
	int	index_b;
	int	degree_a;
	int	degree_b;
	int	diff;

	index_a = *(int *)a;
	index_b = *(int *)b;
	degree_a = nodes_ctx[index_a].degree;
	degree_b = nodes_ctx[index_b].degree;
	diff = degree_a - degree_b;
	if (diff == 0)
		diff = index_a - index_b;
	return (diff);
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
