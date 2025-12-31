#include "ds_finder.h"

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
