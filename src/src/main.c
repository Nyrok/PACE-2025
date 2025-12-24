#include "ds_finder.h"

//https://www.optil.io/optilion/help/signals#c
volatile sig_atomic_t	tle = 0;
t_time					start_time;

void term(int signum)
{
	(void)signum;
	tle = 1;
}

int main(int argc, char *argv[])
{
	start_time = gettime();
	t_graph graph = {
		0, // v_count
		0, // e_count
		NULL, // nodes
		NULL, // solutions
		NULL, // actives
		0, // len_solutions
		false // finished
	};
	struct sigaction action;

	(void)argc;
	(void)argv;
	ft_memset(&action, 0, sizeof(struct sigaction));
	action.sa_handler = term;
	sigaction(SIGTERM, &action, NULL);
	parse_input(&graph);
	while (!tle)
		solve_graph(&graph, &start_time);
	free_graph(&graph);
	ft_putendl_fd("Received SIGTERM, exiting...", STDERR_FILENO);
	return 0;
}
