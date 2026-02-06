#include "ds_finder.h"

/*
** Cherche le sommet actif de plus haut degré dans v_sorted (trié par degré croissant).
** first_active mémorise l'index du premier sommet encore actif pour éviter de
** rescanner depuis le début (les premiers sommets inactifs le restent).
*/
static int	find_best_candidate(int v_count, int *v_sorted, t_bool *actives)
{
	static int	first_active = 0;
	int			i;
	int			node_idx;

	while (first_active < v_count)
	{
		node_idx = v_sorted[first_active];
		if (actives[node_idx])
			break;
		first_active++;
	}
	if (first_active >= v_count)
		return (-1);
	// Parcours depuis first_active : le dernier trouvé = plus haut degré actif
	i = first_active;
	while (i < v_count)
	{
		node_idx = v_sorted[i];
		if (actives[node_idx])
			return (node_idx);
		i++;
	}
	return (v_sorted[first_active]);
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

void	solve_greedy(t_graph *graph)
{
	t_bool	*solutions;
	t_bool	*actives;
	int		best_node;
	int		i;

	debug("Start Greedy");
	solutions = ft_calloc(graph->v_count, sizeof(t_bool));
	actives = malloc((unsigned int)graph->v_count * sizeof(t_bool));
	if (!solutions || !actives)
		return ;
	ft_memset(actives, TRUE, graph->v_count * sizeof(t_bool));
	// Phase feuilles : on ajoute le voisin de la feuille (pas la feuille elle-même),
	// car le voisin couvre la feuille ET potentiellement d'autres sommets
	i = 0;
	while (i < graph->v_count)
	{
		if (graph->nodes[i].degree == 1 && actives[i])
		{
			best_node = graph->nodes[i].neighbors[0];
			if (!solutions[best_node])
			{
				actives[best_node] = FALSE;
				solutions[best_node] = TRUE;
				graph->len_solutions++;
				update_neighbors_active(graph, best_node, actives);
			}
			actives[i] = FALSE;
		}
		i++;
	}
	while (!tle)
	{
		best_node = find_best_candidate(graph->v_count, graph->v_sorted, actives);
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
	graph->actives = actives;
	graph->solutions = solutions;
	debug("End Greedy");
}
