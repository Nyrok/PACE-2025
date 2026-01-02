#include "ds_finder.h"

void	debug(char *message, ...)
{
	va_list	args;

	if (DEBUG)
	{
		va_start(args, message);
		fprintf(stderr, "%lld s - ", gettime() - start_time);
		vfprintf(stderr, message, args);
		fprintf(stderr, "\n");
		va_end(args);
	}
}
