#include "ds_finder.h"

static void	parse_line(t_graph *graph, char *line)
{
	char **strs;
	int	e1, e2;

	if (!line)
		return ;
	if (line[0] == 'c')
		return ;
	strs = ft_split(line, ' ');
	if (graph->v_count == 0 && line[0] == 'p') {
		fill_graph(graph, ft_atoi(strs[2]), ft_atoi(strs[3]));
		free_split(strs, 4);
	}
	else if (graph->v_count > 0 && ft_isdigit(line[0])) {
		e1 = ft_atoi(strs[0]) - 1;
		e2 = ft_atoi(strs[1]) - 1;
		add_neighbor(graph, e1, e2);
		add_neighbor(graph, e2, e1);
		free_split(strs, 2);
	}
}

void	parse_input(t_graph *graph, t_time *start_time)
{
	char *line;

	fprintf(stderr, "%lld s - Starting parsing\n", gettime() - *start_time);
	do {
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		parse_line(graph, line);
		free(line);
	} while (line);
	fprintf(stderr, "%lld s - Finished parsing\n", gettime() - *start_time);
}