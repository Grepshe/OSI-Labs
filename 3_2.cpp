#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
int main(int argc, char **argv)
{
    int timer = 15;
    int is_main = 1;
    int init = 5;
    int n = init;
    while(n)
    {
        n--;
        if(!fork())
        {
            is_main = 0;
            timer--;
            init--;
            n = init;
            printf("Posnanskiy Grigoriy Dmitrievich, PID: %ld, PPID: %ld \n", (long)getpid(), (long)getppid());
        }
    }
    
    if(is_main)
    {
        sleep(2);
        system("pstree -p");
    }else
    {
        sleep(timer);
    }
    

    /*n = init;
    while(n)
    {
        n--;
        wait(NULL);
    }*/

    return 0;
}