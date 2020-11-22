#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int counter(int n)
{
    if (n == 1)
        return 1;
    return n * (counter(n - 1) + 1);
}

int main(int argc, char **argv)
{
    char to_print[500];
    int pos = 0;
    int timer = 15;
    int is_main = 1;
    int init = 5;
    int n = init;
    while (n)
    {
        n--;
        pid_t fork_pid = fork();
        if (!fork_pid)
        {
            pos = 0;
            to_print[0] = 0;
            is_main = 0;
            timer--;
            init--;
            n = init;
        }
        else
        {
            pos += sprintf(to_print + pos, "<%ld>", (long)fork_pid);
        }
    }

    printf("%ld : %s\n", (long)getpid(), to_print);

    if (is_main)
    {
        sleep(2);
        system("pstree -p");
        printf("Posnanskiy Grigoriy Dmitrievich, %d processes\n", counter(init));
        sleep(timer - 2);
    }
    else
    {
        sleep(timer);
    }

    return 0;
}