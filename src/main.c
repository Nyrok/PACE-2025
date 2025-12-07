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

	//read the graph from stdin
	char *str;
	do {
		str = get_next_line(STDIN_FILENO);
		if (str)
			printf("%s", str);
		free(str);
	} while (str);
	printf("\n");
	while (!tle);
	fprintf(stderr, "interrompu\n");
	return 0;
}
