#include "ds_finder.h"

//https://www.optil.io/optilion/help/signals#c
volatile sig_atomic_t tle = 0;

void term(int signum)
{
	(void)signum;
	tle = 1;
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	struct sigaction action;
	memset(&action, 0, sizeof(struct sigaction));
	action.sa_handler = term;
	sigaction(SIGTERM, &action, NULL);
	parse_input();
	while (!tle);
	fprintf(stderr, "interrompu\n");
	return 0;
}
