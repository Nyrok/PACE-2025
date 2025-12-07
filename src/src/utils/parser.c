#include "ds_finder.h"

static void	parse_line(t_graph *graph, char *line)
{
	char **strs;
	t_node	*node;

	if (!line)
		return ;
	if (line[0] == 'c')
		return ;
	strs = ft_split(line, ' ');
	if (line[0] == 'p') {
		fill_graph(graph, ft_atoull(strs[2]), ft_atoull(strs[3]));
		free_split(strs, 4);
	}
	else if (ft_isdigit(line[0]) && graph->nodes) {
		node = &graph->nodes[ft_atoull(strs[0]) - 1];
		node->neighbors = realloc(node->neighbors, (node->degree + 1) * sizeof(t_ull));
		node->neighbors[node->degree] = ft_atoull(strs[1]) - 1;
		node->degree++;
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