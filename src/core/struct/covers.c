#include "ds_finder.h"

/*
** covers[i] = nombre de sommets de la solution qui dominent i
** (i lui-même s'il est dans la solution + ses voisins qui y sont).
** Si covers[i] >= 1, le sommet i est couvert.
*/

int	*init_cover_counts(t_graph *g)
{
	int	*covers;
	int	u, v;
	int	i;

	covers = ft_calloc(g->v_count, sizeof(int));
	if (!covers) return (NULL);

	u = 0;
	while (u < g->v_count)
	{
		if (g->solutions[u])
		{
			covers[u]++;
			i = 0;
			while (i < g->nodes[u].degree)
			{
				v = g->nodes[u].neighbors[i];
				covers[v]++;
				i++;
			}
		}
		u++;
	}
	return (covers);
}

// val = +1 quand on ajoute u à la solution, -1 quand on le retire (mise à jour incrémentale)
void	update_covers(t_graph *g, int *covers, int u, int val)
{
	int i, v;

	covers[u] += val;
	i = 0;
	while (i < g->nodes[u].degree)
	{
		v = g->nodes[u].neighbors[i];
		covers[v] += val;
		i++;
	}
}

// Vérifie que tous les sommets soient couverts (covers[i] >= 1 pour tout i appartenant à [0; v_count[ )
t_bool	is_covered(t_graph *g, int *covers)
{
	int	u;

	u = 0;
	while (u < g->v_count)
	{
		if (covers[u] == 0)
			return (FALSE);
		u++;
	}
	return (TRUE);
}
