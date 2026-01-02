#include "ds_finder.h"

void	parse_input(t_graph *graph)
{
	char	*line = NULL;
	size_t	len = 0;
	ssize_t	read;
	int		v1, v2;
	int		nb_nodes, nb_edges;
	char	buf_type[3];

	debug("Start parsing");
	while ((read = getline(&line, &len, stdin)) != -1)
	{
		if (line[0] == 'c' || line[0] == '\n')
			continue;
		if (line[0] == 'p' && graph->v_count == 0)
		{
			if (sscanf(line, "p %2s %d %d", buf_type, &nb_nodes, &nb_edges) == 3)
				fill_graph(graph, nb_nodes, nb_edges);
		}
		else if (line[0] >= '0' && line[0] <= '9')
		{
			if (sscanf(line, "%d %d", &v1, &v2) == 2)
			{
				add_neighbor(graph, v1 - 1, v2 - 1);
				add_neighbor(graph, v2 - 1, v1 - 1);
			}
		}
	}
	free(line);
	debug("End parsing");
}
