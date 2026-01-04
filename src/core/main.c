#include "ds_finder.h"

//https://www.optil.io/optilion/help/signals#c
volatile sig_atomic_t	tle = 0;
t_time					start_time;

void term(int signum)
{
	(void)signum;
	if (tle == 0)
		debug("Received SIGTERM, exiting...");
	tle = 1;
}

int main(int argc, char *argv[])
{
	start_time = gettime();
	t_graph graph = {
		.v_count = 0,
		.e_count = 0,
		.type = GRAPH_UNKNOWN,
		.nodes = NULL,
		.solutions = NULL,
		.actives = NULL,
		.v_sorted = NULL,
		.len_solutions = 0,
		.finished = FALSE
	};
	struct sigaction action;

	(void)argc;
	(void)argv;
	srand(42); // Déterministe
	ft_memset(&action, 0, sizeof(struct sigaction));
	action.sa_handler = term;
	sigaction(SIGTERM, &action, NULL);
	parse_input(&graph);
	graph.type = get_graph_type(&graph);
	debug("Graph type %d", graph.type);
	sort_graph(&graph);
	solve_graph(&graph);
	return (EXIT_SUCCESS);
}
