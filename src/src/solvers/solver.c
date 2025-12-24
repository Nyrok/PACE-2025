#include "ds_finder.h"

void	solve_graph(t_graph *graph, t_time *start_time) {
	t_ull	i;
	t_ull	solutions_count;

	apply_degree_one_rule(graph);
	solve_greedy(graph, start_time);
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
	printf("%lld\n", solutions_count);
	i = 0;
	while (i < graph->v_count) {
		if (graph->solutions[i])
			printf("%lld\n", i + 1);
		else if (!graph->finished && graph->actives[i]) {
			printf("%lld\n", i + 1);
		}
		i++;
	}
	free_graph(graph);
	exit(EXIT_SUCCESS);
}
