#include "ds_finder.h"

void	add_missing_solutions(t_graph *graph, t_bool *actives)
{
	int	u;

	// Fallback si SIGTERM interrompt l'algorithme avant qu'il ne termine :
	// ajoute tous les sommets encore actifs (non couverts) pour garantir une solution valide
	u = 0;
	while (u < graph->v_count)
	{
		if (!graph->solutions[u] && actives[u])
		{
			graph->solutions[u] = TRUE;
			graph->len_solutions++;
		}
		u++;
	}
}

static void	exit_print_solution(t_graph *graph)
{
	int	u;
	int	solutions_count;

	solutions_count = graph->len_solutions;
	printf("%d\n", solutions_count);
	u = 0;
	while (u < graph->v_count) {
		if (graph->solutions[u])
			printf("%d\n", u + 1);
		u++;
	}
	fflush(stdout);
	free_graph(graph);
	exit(EXIT_SUCCESS);
}

void	solve_graph(t_graph *graph) {
	if (graph->type == GRAPH_CORE_PERIPHERY || graph->type == GRAPH_GRID_2D)
		solve_periphery_greedy(graph);
	else
		solve_greedy(graph);
	solve_optimizer(graph);
	exit_print_solution(graph);
}

