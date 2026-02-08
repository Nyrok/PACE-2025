#ifndef COVERS_H
# define COVERS_H

# include "types.h"

int		*init_cover_counts(t_graph *g);
t_bool	is_covered(t_graph *g, int *covers);
void	update_covers(t_graph *g, int * restrict covers, int u, int val);

#endif