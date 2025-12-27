#include "ds_finder.h"

void	solve_graph(t_graph *graph, t_time *start_time) {
	t_ull	i;
	t_ull	solutions_count;

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
	ft_putnbr_fd(solutions_count, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	i = 0;
	while (i < graph->v_count) {
		if (graph->solutions[i] || (!graph->finished && graph->actives[i]))
		{
			ft_putnbr_fd(i + 1, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		i++;
	}
	free_graph(graph);
	exit(EXIT_SUCCESS);
}
