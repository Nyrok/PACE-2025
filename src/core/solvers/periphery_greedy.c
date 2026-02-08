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

static void	init_buckets(t_graph *g, int *head, int *next, int *gain)
{
	int	u;
	int	v_gain; // Gain initial = degree + 1 (surestimation, car tous actifs au départ)

	u = 0;
	while (u < g->v_count)
	{
		v_gain = g->nodes[u].degree + 1;
		gain[u] = v_gain;
		next[u] = head[v_gain];
		head[v_gain] = u;
		u++;
	}
}

static void	core_loop(t_graph *g, t_bool *solutions, t_bool *actives, int *head, int *next, int *gain)
{
	int	idx;
	int	u;
	int	real_g;
	int	remaining;

	remaining = g->v_count;
	idx = g->v_count;
	while (!tle && idx > 0 && remaining > 0)
	{
		if (head[idx] == -1)
		{
			idx--;
			continue ;
		}
		u = head[idx];
		head[idx] = next[u];
		// Lazy evaluation : on recalcule le gain réel au moment de traiter le sommet
		real_g = get_gain(g, u, actives);
		// Gain réel >= bucket → candidat valide (gain stable ou sous-estimé), on l'ajoute
		if (real_g >= idx)
		{
			solutions[u] = TRUE;
			g->len_solutions++;
			update_actives(g, u, actives, &remaining);
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

/*
** Structure de bucket sort par listes chaînées implicites (tableaux) :
**   actives[u] = TRUE si le sommet u n'est pas encore couvert
**   head[d] = premier sommet dans le bucket de gain d (-1 si vide)
**   next[u] = prochain sommet après u dans le même bucket
**   gain[u] = gain estimé du sommet u
** Permet de traiter en priorité les sommets à haut gain sans re-trier.
*/
void	solve_periphery_greedy(t_graph *graph)
{
	t_bool	*solutions;
	t_bool	*actives;
	int		*head;
	int		*next;
	int		*gain;
	int		u;

	solutions = malloc(sizeof(t_bool) * (unsigned int)(graph->v_count));
	actives = malloc(sizeof(t_bool) * (unsigned int)(graph->v_count));
	head = malloc(sizeof(int) * (unsigned int)(graph->v_count + 1));
	next = malloc(sizeof(int) * (unsigned int)graph->v_count);
	gain = malloc(sizeof(int) * (unsigned int)graph->v_count);
	if (!head || !next || !gain || !actives || !solutions)
		exit(EXIT_FAILURE);
	debug("Start Periphery Greedy");
	u = -1;
	while (++u < graph->v_count)
	{
		actives[u] = TRUE;
		solutions[u] = FALSE;
		head[u] = -1;
	}
	head[graph->v_count] = -1;
	init_buckets(graph, head, next, gain);
	graph->len_solutions = 0;
	core_loop(graph, solutions, actives, head, next, gain);
	graph->solutions = solutions;
	if (tle)
		add_missing_solutions(graph, actives);
	free(actives);
	free(head);
	free(next);
	free(gain);
	debug("End Periphery Greedy");
}
