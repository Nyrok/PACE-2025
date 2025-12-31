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

static double	get_score(int node_index)
{
	double		score, sub_score;
	int		i, j;
	t_node	*node, *neighbor_node;
	int		neighbor_idx, neighbor_neighbor_idx;

	i = 0;
	node = &nodes_ctx[node_index];
	score = 0.0;
	qsort(node->neighbors, node->degree, sizeof(int), compare_degrees);
	while (i < node->degree)
	{
		neighbor_idx = node->neighbors[i]; 
		j = 0;
		neighbor_node = &nodes_ctx[neighbor_idx];
		sub_score = 0.0;
		while (j < neighbor_node->degree)
		{
			neighbor_neighbor_idx = neighbor_node->neighbors[j];
			if (neighbor_neighbor_idx != neighbor_idx && neighbor_neighbor_idx != node_index)
				sub_score += nodes_ctx[neighbor_neighbor_idx].degree;
			j++;
		}
		i++;
		score += 1.0 / ((i / nodes_ctx[neighbor_idx].degree) - (1 / (sub_score * i)));
	}
	return (score);
}

static int	compare(const void *a, const void *b)
{
	int		index_a;
	int		index_b;
	double	weight_a;
	double	weight_b;

	index_a = *(int *)a;
	index_b = *(int *)b;
	weight_a = get_score(index_a);
	weight_b = get_score(index_b);
	if (weight_a - weight_b == 0.0)
		return (nodes_ctx[index_a].degree - nodes_ctx[index_b].degree);
	return (weight_b - weight_a); 
}

void	sort_graph(t_graph *graph)
{
	int i;

	debug("Start sorting");
	i = 0;
	while (i < graph->v_count)
	{
		graph->v_sorted[i] = i;
		i++;
	}
	nodes_ctx = graph->nodes;
	qsort(graph->v_sorted, graph->v_count, sizeof(int), compare);
	debug("End sorting");
}
