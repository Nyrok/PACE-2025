#include "ds_finder.h"

void	exit_print_solution(t_graph *graph)
{
	int	i;
	int	solutions_count;

	solutions_count = graph->len_solutions;
	if (!graph->finished)
	{
		i = 0;
		while (i < graph->v_count)
		{
			if (!graph->solutions[i] && graph->actives[i])
				solutions_count++;
			i++;
		}
	}
	printf("%d\n", solutions_count);
	i = 0;
	while (i < graph->v_count) {
		if (graph->solutions[i] || (!graph->finished && graph->actives[i]))
			printf("%d\n", i + 1);
		i++;
	}
	fflush(stdout);
	free_graph(graph);
	exit(EXIT_SUCCESS);
}

void	solve_graph(t_graph *graph) {
	if (get_graph_type(graph) == GRAPH_CORE_PERIPHERY)
		solve_periphery_greedy(graph);
	else
		solve_greedy(graph);
	solve_optimizer(graph);
	exit_print_solution(graph);
}

