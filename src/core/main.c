#include "ds_finder.h"

/*
** Pipeline principal : parse → classification du graphe → tri par degré → résolution gloutonne → optimisation locale.
** Le juge optil.io envoie SIGTERM quand le temps est écoulé : on intercepte ce signal
** pour lever le flag `tle` et afficher la meilleure solution trouvée jusque-là.
*/

volatile sig_atomic_t	tle = 0;
t_time					start_time;

void term(int signum)
{
	(void)signum;
	if (tle == 0)
		debug("Received SIGTERM, exiting...");
	tle = 1;
}

int main(void)
{
	start_time = gettime();
	t_graph graph = {
		.v_count = 0,
		.e_count = 0,
		.type = GRAPH_UNKNOWN,
		.nodes = NULL,
		.solutions = NULL,
		.actives = NULL,
		.len_solutions = 0,
		.finished = FALSE
	};
	struct sigaction action;

	ft_memset(&action, 0, sizeof(struct sigaction));
	action.sa_handler = term;
	sigaction(SIGTERM, &action, NULL);
	parse_input(&graph);
	graph.type = get_graph_type(&graph);
	debug("Graph type %d", graph.type);
	solve_graph(&graph);
	return (EXIT_SUCCESS);
}
