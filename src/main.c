#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
 
//https://www.optil.io/optilion/help/signals#c
volatile sig_atomic_t tle = 0;
int n, i;
float worker;
 
void term(int signum)
{
    tle = 1;
}
 
int main(int argc, char *argv[])
{
    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = term;
    sigaction(SIGTERM, &action, NULL);
 
    //read the graph from stdin
    int c;
    c = fgetc(stdin);
    while(c != -1) {
        printf("%c", c);
        c = fgetc(stdin);
    }
    printf("\n");
    
    /*
    demo of capturing SIGTERM
    to see how it works, run:
    gcc -Wall main.c
    timeout 2s ./a.out < instance.gr
    tle is True after 2 second (in the benchmark, it will be after 5 minutes)
    */

    while(!tle) {
        ;   //rien
    }
    fprintf(stderr, "interrompu\n");
 
    return 0;
}