#include "ds_finder.h"

void	solve_graph(t_graph *graph, t_time *start_time) {
	int	i;
	int	solutions_count;

	solve_greedy(graph, start_time);
	solve_optimizer(graph, start_time);
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
	free_graph(graph);
	exit(EXIT_SUCCESS);
}
