#include "ds_finder.h"

void	add_missing_solutions(t_graph *graph, t_bool *actives)
{
	int	i;

	// Sécurité qui n'arrive pas en temps réel ; si l'algorithme principal n'est pas terminé,
	// alors on compte les sommets non couverts dans la solution
	i = 0;
	while (i < graph->v_count)
	{
		if (!graph->solutions[i] && actives[i])
		{
			graph->solutions[i] = TRUE;
			graph->len_solutions++;
		}
		i++;
	}
}

static void	exit_print_solution(t_graph *graph)
{
	int	i;
	int	solutions_count;

	solutions_count = graph->len_solutions;
	printf("%d\n", solutions_count);
	i = 0;
	while (i < graph->v_count) {
		if (graph->solutions[i])
			printf("%d\n", i + 1);
		i++;
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

