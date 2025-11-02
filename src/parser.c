#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void parse_file(char *filename)
{
	int fd = open(filename, O_RDONLY);
	char *buffer = NULL;
	size_t size = 0;

	do {
		getline(&buffer,&size,stdin);
		if (!size)
			break;
		if (buffer[0] == 'c')
			continue;
		if (buffer[0] == 'p') {
			strtok(buffer, " ");
		}
		// TODO parse 
		
	} while (size == 0);
}