#include <stdio.h>
#include <stdlib.h>

char **split(const char *str, const char *delim, int *count) {
    char *s = strdup(str);
    char *token;
    char **result = NULL;
    int tokens = 0;

    token = strtok(s, delim);
    while (token != NULL) {
        result = realloc(result, sizeof(char*) * (tokens + 1));
        result[tokens++] = strdup(token);
        token = strtok(NULL, delim);
    }
    *count = tokens;
    free(s);
    return result;
}