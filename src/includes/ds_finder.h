#ifndef DS_FINDER_H
# define DS_FINDER_H

# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <math.h>

# include "get_next_line.h"
# include "libft.h"

typedef struct s_graph
{
    int         v_count;
    int         e_count;
    int  		**neighbors;
}   t_graph;

void	parse_input(void);
t_graph	*create_graph(void);
void	fill_graph(t_graph	**graph, int v, int e);

#endif