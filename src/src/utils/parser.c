#include "ds_finder.h"

static void	parse_line(t_graph **graph, char *line)
{
	char **header;

	if (!line)
		return ;
	if (line[0] == 'c')
		return ;
	if (line[0] == 'p') {
		header = ft_split(line, ' ');
		fill_graph(graph, ft_atoi(header[2]), ft_atoi(header[3]));
		free_split(header, 4);
	}
}

void	parse_input(void)
{
	t_graph	*graph = create_graph();
	char *line;

	do {
		line = get_next_line(STDIN_FILENO);
		parse_line(&graph, line);
		if (line)
			printf("%s", line);
		free(line);
	} while (line);
}