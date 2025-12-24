#include "ds_finder.h"

t_time	gettime(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec);
}