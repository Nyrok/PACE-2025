#include "ds_finder.h"

t_graph_type	get_graph_type(t_graph *g)
{
	int					u;
	int					max_d;
	int					leaf_count;
	unsigned long long	avg_d;
	unsigned long long	ratio;

	if (!g || g->v_count <= 0)
		return (GRAPH_UNKNOWN);
	max_d = 0;
	leaf_count = 0;
	u = 0;
	while (u < g->v_count)
	{
		if (g->nodes[u].degree > max_d)
			max_d = g->nodes[u].degree;
		if (g->nodes[u].degree == 1)
			leaf_count++;
		u++;
	}
	// Degré moyen = somme des degrés / nb sommets = 2*arêtes / nb sommets
	avg_d = (unsigned long long)(2 * g->e_count) / g->v_count;
	// Ratio degré max / degré moyen : mesure l'asymétrie de la distribution des degrés
	ratio = (unsigned long long)max_d / avg_d;
	debug("max_d %i avg_d %i", max_d, avg_d);
	// Graphe complet : nb arêtes max d'un graphe non orienté = v*(v-1)/2
	if (g->e_count == (g->v_count * (g->v_count - 1)) / 2)
		return (GRAPH_COMPLETE);
	// Étoile : un sommet connecté à tous les autres et exactement v-1 arêtes
	if (max_d == g->v_count - 1 && g->e_count == g->v_count - 1)
		return (GRAPH_STAR);
	// Seuils empiriques pour classifier la topologie du graphe
	if (ratio > 50)
	{
		if (leaf_count > g->v_count * 0.7)
			return (GRAPH_MULTI_STAR);
		return (GRAPH_CORE_PERIPHERY);
	}
	if (ratio > 5)
		return (GRAPH_SCALE_FREE);
	if (avg_d >= 2 && avg_d <= 6 && max_d <= 10)
	{
		if (g->e_count == g->v_count - 1 && leaf_count > g->v_count * 0.1)
			return (GRAPH_TREE);
		if (g->e_count == g->v_count)
			return (GRAPH_RING);
		return (GRAPH_GRID_2D);
	}
	if (leaf_count == 0 && avg_d > 2)
		return (GRAPH_ERDOS_RENYI);
	return (GRAPH_UNKNOWN);
}

void add_neighbor(t_graph *graph, int u, int v)
{
    t_node	*node;
	int		*tmp, new_cap;

	node = &graph->nodes[u];
    if (node->degree >= node->capacity)
    {
        new_cap = (node->capacity == 0) ? 2 : node->capacity * 2;
        tmp = realloc(node->neighbors, sizeof(int) * new_cap);
        if (!tmp)
			exit(EXIT_FAILURE);
        node->neighbors = tmp;
        node->capacity = new_cap;
    }
    node->neighbors[node->degree] = v;
    node->degree++;
}

void	fill_graph(t_graph *graph, int v, int e)
{
	graph->v_count = v;
	graph->e_count = e;
	graph->nodes = ft_calloc(v, sizeof(t_node));
	if (!graph->nodes)
		exit(EXIT_FAILURE);
}

void	free_graph(t_graph *graph)
{
	int	u;

	u = 0;
	while (u < graph->v_count)
	{
		free(graph->nodes[u].neighbors);
		u++;
	}
	free(graph->nodes);
	free(graph->solutions);
}
