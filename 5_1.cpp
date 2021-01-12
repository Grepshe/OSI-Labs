#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

double f(double x)
{
    return (4 / (1 + x * x));
}

double integ(double a, double b, int n)
{
    double s = (f(a) + f(b)) / 2;
    double h = (b - a) / n;

    for (int i = 1; i <= n - 1; i++)
        s += f(a + i * h);

    double I = h * s;
    return I;
}

int main(int argc, char *argv[])
{
    int i;
    pid_t pid;
    int fifo[2];
    int parts, n;
    double curr_pi, pi = 0;
    double k;
    double dx;

    if (argc < 3 || argc == 1)
    {
        printf("Inv arg\n");
        exit(1);
    }

    parts = atoi(argv[1]);
    n = atoi(argv[2]);
    dx = 1.0 / n;

    if (pipe(fifo) == -1)
    {
        perror("");
        exit(1);
    }

    for (i = 0; i < parts; i++)
    {
        pid = fork();
        if (!pid)
        {
            curr_pi = integ(i * 1.0 / parts, (i + 1) * 1.0 / parts, n);
            close(fifo[0]);
            write(fifo[1], &curr_pi, sizeof(curr_pi));
            close(fifo[1]);
            exit(0);
        }
    }
    if (pid)
    {
        double m = 0;
        close(fifo[1]);
        while (read(fifo[0], &m, sizeof(m)))
            pi += m;
        cout << pi << endl;
        close(fifo[0]);
    }
    return 0;
}