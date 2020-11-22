#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
int main(int argc, char **argv)
{
    if(argc != 2)
    {
        printf("No arg");
        return 1;
    }
    int n;
    sscanf(argv[1],"%d",&n);
    while(n)
    {
        n--;
        if(!fork())
        {
            printf("Posnanskiy Grigoriy Dmitrievich, PID: %ld, PPID: %ld \n", (long)getpid(), (long)getppid());
            break;
        }
    }

    return 0;
}