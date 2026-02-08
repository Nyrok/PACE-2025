#include "ds_finder.h"

/*
** Sélection gloutonne du meilleur candidat à ajouter à D parmi N[u].
** Critère : score(v) = nombre de sommets non couverts (covers[] == 0) que v
** dominerait s'il rejoignait D (v lui-même s'il est non couvert + ses voisins
** non couverts). Retourne le candidat de score maximal, ou -1 si aucun valide.
** include_self = TRUE  → u est candidat (réparation d'un voisin non couvert)
** include_self = FALSE → seuls N(u) sont candidats (couvrir u sans le réinsérer)
*/
static int	greedy_pick(t_graph *g, int *covers, t_bool *solutions,
		int u, t_bool include_self)
{
	int	best, best_score, i, j, v, score;

	best = -1;
	best_score = -1; // -1 pour accepter tout candidat avec score >= 0
	// Passe 1 : évaluation de u lui-même (si autorisé et pas déjà dans D)
	// score(u) = |{w ∈ N(u) : covers[w] == 0}| (nb voisins non couverts)
	if (include_self && !solutions[u])
	{
		best = u;
		best_score = 0;
		i = 0;
		while (i < g->nodes[u].degree)
		{
			if (covers[g->nodes[u].neighbors[i]] == 0)
				best_score++;
			i++;
		}
	}
	// Passe 2 : évaluation de chaque voisin v ∈ N(u) non présent dans D
	i = 0;
	while (!tle && i < g->nodes[u].degree)
	{
		v = g->nodes[u].neighbors[i];
		if (!solutions[v])
		{
			// score(v) = 1{covers[v]==0} + |{w ∈ N(v) : covers[w] == 0}|
			// v lui-même compte s'il est non couvert (il se dominerait en rejoignant D)
			score = (covers[v] == 0) ? 1 : 0;
			j = 0;
			while (j < g->nodes[v].degree)
			{
				if (covers[g->nodes[v].neighbors[j]] == 0)
					score++;
				j++;
			}
			if (score > best_score)
			{
				best = v;
				best_score = score;
			}
		}
		i++;
	}
	return (best);
}

/*
** Perturbation : éjecte un sommet aléatoire u de D pour créer des "trous",
** puis répare la solution via greedy_pick en deux phases :
**   Phase 1 : pour chaque voisin de u devenu non couvert (covers == 0),
**             greedy_pick(v_i, TRUE) sélectionne le meilleur candidat dans N[v_i].
**   Phase 2 : si u lui-même reste non couvert, greedy_pick(u, FALSE) sélectionne
**             le meilleur voisin de u (sans u, car tabou) pour le couvrir.
** La mise à jour de covers[] après chaque ajout est dynamique : les scores
** des candidats suivants tiennent compte des ajouts précédents.
*/
void	add_candidates(t_graph *g, t_bool *solutions, int *len_solutions,
		int *covers, int *tabu_list, int iter)
{
	int	u;
	int	i;
	int	*neighbors;

	// Éjection : sommet aléatoire dans D, non protégé par le tabou
	do {
		if (tle)
			return ;
		u = xor_rand() % g->v_count;
	} while (!solutions[u] || tabu_list[u] > iter);
	solutions[u] = FALSE;
	(*len_solutions)--;
	tabu_list[u] = iter + 20; // Tabou long (20) pour empêcher la réinsertion immédiate
	update_covers(g, covers, u, -1);
	// Phase 1 : réparation des voisins devenus non couverts après l'éjection de u
	neighbors = g->nodes[u].neighbors;
	i = 0;
	while (!tle && i < g->nodes[u].degree)
	{
		if (covers[neighbors[i]] == 0)
		{
			// TRUE : le voisin non couvert est lui-même candidat à rejoindre D
			int w = greedy_pick(g, covers, solutions, neighbors[i], TRUE);
			if (w >= 0 && !solutions[w])
			{
				solutions[w] = TRUE;
				(*len_solutions)++;
				// Mise à jour dynamique : modifie les scores des candidats suivants
				update_covers(g, covers, w, 1);
			}
		}
		i++;
	}
	// Phase 2 : si u reste non couvert et a des voisins, chercher un candidat
	if (covers[u] == 0 && g->nodes[u].degree > 0)
	{
		// FALSE : u ne peut pas se réinsérer (tabou), seuls ses voisins sont candidats
		int v = greedy_pick(g, covers, solutions, u, FALSE);
		if (v >= 0 && !solutions[v])
		{
			solutions[v] = TRUE;
			(*len_solutions)++;
			update_covers(g, covers, v, 1);
		}
	}
	// Cas extrême : u est isolé (degree == 0) et non couvert → seule option : se réinsérer
	else if (covers[u] == 0)
	{
		solutions[u] = TRUE;
		(*len_solutions)++;
		update_covers(g, covers, u, 1);
	}
}
