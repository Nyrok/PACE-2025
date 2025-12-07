#include "ds_finder.h"

static void	parse_line(t_graph *graph, char *line)
{
	char **strs;

	if (!line)
		return ;
	if (line[0] == 'c')
		return ;
	strs = ft_split(line, ' ');
	if (line[0] == 'p') {
		fill_graph(graph, ft_atoi(strs[2]), ft_atoi(strs[3]));
		free_split(strs, 4);
	}
	else {
		graph->neighbors[ft_atoi(strs[0]) - 1][ft_atoi(strs[1]) - 1] = 1;
		free_split(strs, 2);
	}
}

void	parse_input(t_graph *graph)
{
	char *line;

	do {
		line = get_next_line(STDIN_FILENO);
		parse_line(graph, line);
		free(line);
	} while (line);
}