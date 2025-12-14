#include "ds_finder.h"

static long update_neighbors_of_v(t_graph *g, t_ull v, t_ull u, t_ull *stack, long top)
{
	t_ull   i;
	t_ull   w;
	t_node  *node_v;

	node_v = &g->nodes[v];
	i = 0;
	while (i < node_v->degree)
	{
		w = node_v->neighbors[i];
		if (w != u && g->actives[w])
		{
			remove_neighbor(&g->nodes[w], v);
			if (g->nodes[w].degree == 1)
			{
				top++;
				stack[top] = w;
			}
			else if (g->nodes[w].degree == 0)
				g->actives[w] = false;
		}
		i++;
	}
	return (top);
}

static void	remove_first_degree_nodes(t_graph *g, t_ull *stack, t_ll *top)
{
	t_ull   u;
	t_ull   v;

	while (*top >= 0)
	{
		u = stack[(*top)--];
		if (!g->actives[u]) continue ;
		if (g->nodes[u].degree != 1) continue ;
		v = g->nodes[u].neighbors[0];
		if (!g->actives[v]) continue ;
		if (!g->solutions[v])
		{
			g->solutions[v] = true;
			g->len_solutions++;
		}
		g->actives[u] = false;
		g->actives[v] = false;
		*top = update_neighbors_of_v(g, v, u, stack, *top);
	}
}

void apply_degree_one_rule(t_graph *g)
{
	t_ull   *stack;
	t_ll	top;
	t_ull	i;
	
	stack = malloc(sizeof(t_ull) * g->v_count);
	if (!stack || !g->actives || !g->solutions) return ;
	top = -1;
	i = 0;
	while (i < g->v_count)
	{
		g->actives[i] = true;
		if (g->actives[i] && g->nodes[i].degree == 1)
		{
			top++;
			stack[top] = i;
		}
		i++;
	}
	remove_first_degree_nodes(g, stack, &top);
	free(stack);
}
