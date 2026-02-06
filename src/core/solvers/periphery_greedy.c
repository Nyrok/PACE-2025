#include "ds_finder.h"

// Gain = nombre de sommets actifs que u couvrirait s'il était ajouté (lui-même + voisins actifs)
static int	get_gain(t_graph *g, int u, t_bool *actives)
{
	int	i;
	int	res;

	res = actives[u];
	i = 0;
	while (i < g->nodes[u].degree)
	{
		if (actives[g->nodes[u].neighbors[i]])
			res++;
		i++;
	}
	return (res);
}

static void	update_actives(t_graph *g, int u, t_bool *actives, int *remaining)
{
	int	i;
	int	v;
	
	if (actives[u])
	{
		actives[u] = FALSE;
		(*remaining)--;
	}
	i = 0;
	while (i < g->nodes[u].degree)
	{
		v = g->nodes[u].neighbors[i];
		if (actives[v])
		{
			actives[v] = FALSE;
			(*remaining)--;
		}
		i++;
	}
}

/*
** Structure de bucket sort par listes chaînées implicites (tableaux) :
**   head[d] = premier sommet dans le bucket de gain d (-1 si vide)
**   next[u] = prochain sommet après u dans le même bucket
**   gain[u] = gain estimé du sommet u
** Permet de traiter en priorité les sommets à haut gain sans re-trier.
*/
static void	init_buckets(t_graph *g, int *head, int *next, int *gain)
{
	int	i;
	int	v_gain;

	i = 0;
	while (i < g->v_count)
	{
		v_gain = g->nodes[i].degree + 1;
		gain[i] = v_gain;
		next[i] = head[v_gain];
		head[v_gain] = i;
		i++;
	}
}

static void	core_loop(t_graph *g, int *head, int *next, int *gain)
{
	int	idx;
	int	u;
	int	real_g;
	int	remaining;

	remaining = g->v_count;
	idx = g->v_count;
	while (idx > 0 && remaining > 0)
	{
		if (head[idx] == -1)
		{
			idx--;
			continue ;
		}
		u = head[idx];
		head[idx] = next[u];
		// Lazy evaluation : on recalcule le gain réel au moment de traiter le sommet
		real_g = get_gain(g, u, g->actives);
		if (real_g >= idx)
		{
			g->solutions[u] = TRUE;
			g->len_solutions++;
			update_actives(g, u, g->actives, &remaining);
		}
		else if (real_g > 0)
		{
			// Re-bucketing : gain réel < bucket actuel, on déplace vers le bon bucket
			gain[u] = real_g;
			next[u] = head[real_g];
			head[real_g] = u;
		}
	}
}

void	solve_periphery_greedy(t_graph *g)
{
	int	*head;
	int	*next;
	int	*gain;
	int	i;

	g->actives = malloc(sizeof(t_bool) * (unsigned int)(g->v_count));
	g->solutions = malloc(sizeof(t_bool) * (unsigned int)(g->v_count));
	head = malloc(sizeof(int) * (unsigned int)(g->v_count + 1));
	next = malloc(sizeof(int) * (unsigned int)g->v_count);
	gain = malloc(sizeof(int) * (unsigned int)g->v_count);
	if (!head || !next || !gain || !g->actives || !g->solutions)
		exit(EXIT_FAILURE);
	debug("Start Periphery Greedy");
	i = -1;
	while (++i < g->v_count)
	{
		g->actives[i] = TRUE;
		g->solutions[i] = FALSE;
		head[i] = -1;
	}
	head[g->v_count] = -1;
	init_buckets(g, head, next, gain);
	g->len_solutions = 0;
	core_loop(g, head, next, gain);
	g->finished = TRUE;
	free(head);
	free(next);
	free(gain);
	debug("End Periphery Greedy");
}
