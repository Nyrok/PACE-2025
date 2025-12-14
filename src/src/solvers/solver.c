#include "ds_finder.h"

void	solve_graph(t_graph *graph) {
	t_ull	i;

	apply_degree_one_rule(graph);
	printf("%lld\n", graph->v_count);
	i = 0;
	while (i < graph->v_count) {
		printf("%lld\n", i + 1);
		i++;
	}
	free_graph(graph);
	exit(EXIT_SUCCESS);
}
