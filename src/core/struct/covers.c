#include "ds_finder.h"

/*
** covers[i] = nombre de sommets de la solution qui dominent i
** (i lui-même s'il est dans la solution + ses voisins qui y sont).
** Si covers[i] >= 1, le sommet i est couvert.
*/

int	*init_cover_counts(t_graph *g)
{
	int		*covers;
	int	i, j, neighbor;

	covers = ft_calloc(g->v_count, sizeof(int));
	if (!covers) return (NULL);

	i = 0;
	while (i < g->v_count)
	{
		if (g->solutions[i])
		{
			covers[i]++;
			j = 0;
			while (j < g->nodes[i].degree)
			{
				neighbor = g->nodes[i].neighbors[j];
				covers[neighbor]++;
				j++;
			}
		}
		i++;
	}
	return (covers);
}

// val = +1 quand on ajoute u à la solution, -1 quand on le retire (mise à jour incrémentale)
void	update_covers(t_graph *g, int *covers, int u, int val)
{
	int j, neighbor;

	covers[u] += val;
	j = 0;
	while (j < g->nodes[u].degree)
	{
		neighbor = g->nodes[u].neighbors[j];
		covers[neighbor] += val;
		j++;
	}
}

t_bool	is_covered(t_graph *g, int *covers)
{
	int	i;

	i = 0;
	while (i < g->v_count)
	{
		if (covers[i] == 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
