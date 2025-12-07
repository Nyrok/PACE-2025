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
		fill_graph(graph, ft_atoll(strs[2]), ft_atoll(strs[3]));
		free_split(strs, 4);
	}
	else {
		graph->neighbors[ft_atoll(strs[0]) - 1].adj[ft_atoll(strs[1]) - 1] = 1;
		graph->neighbors[ft_atoll(strs[0]) - 1].degree++;
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