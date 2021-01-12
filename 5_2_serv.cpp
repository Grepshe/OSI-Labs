#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>
#include <sys/ipc.h>
#include <sys/msg.h>

using namespace std;

#ifndef MSGMAX
#define MSGMAX 1024
#endif

typedef struct
{
    double first;
    double second;
} Elem;

typedef struct mbuf
{
    long mtype;
    int childpid;
    int ratio[4];
    Elem ans[3];
} mbuf;

double croot(double x)
{
    if (x < 0)
        return -pow(-x, 1.0 / 3.0);
    return pow(x, 1.0 / 3.0);
}

int Kardano(double A, double B, double C, double D, Elem *x)
{
    if (A == 0)
    {
        printf("X is any\n");
        return -1;
    }

    double p = (3.0 * A * C - B * B) / (3.0 * A * A);
    double q = (2.0 * B * B * B - 9.0 * A * B * C + 27.0 * A * A * D) / (27.0 * A * A * A);
    double S = (q * q / 4.0) + (p * p * p / 27.0);

    double F;
    if (q == 0)
        F = M_PI / 2.0;
    if (q < 0)
        F = atan(-2.0 * sqrt(-S) / q);
    if (q > 0)
        F = atan(-2.0 * sqrt(-S) / q) + M_PI;

    int i;
    for (i = 0; i < 3; i++)
        x[i].first = x[i].second = 0;
    if (S < 0)
    {
        x[0].first = 2.0 * sqrt(-p / 3.0) * cos(F / 3.0) - B / (3.0 * A);
        x[1].first = 2.0 * sqrt(-p / 3.0) * cos((F / 3.0) + 2.0 * M_PI / 3.0) - B / (3.0 * A);
        x[2].first = 2.0 * sqrt(-p / 3.0) * cos((F / 3.0) + 4.0 * M_PI / 3.0) - B / (3.0 * A);
    }
    if (S == 0)
    {
        x[0].first = 2.0 * croot(-q / 2.0) - B / (3.0 * A);
        x[1].first = -croot(-q / 2.0) - B / (3.0 * A);
        x[2].first = -croot(-q / 2.0) - B / (3.0 * A);
    }

    if (S > 0)
    {
        double temp1 = croot((-q / 2.0) + sqrt(S)) + croot((-q / 2.0) - sqrt(S));
        double temp2 = croot((-q / 2.0) + sqrt(S)) - croot((-q / 2.0) - sqrt(S));
        x[0].first = temp1 - B / (3.0 * A);
        x[1].first = -temp1 / 2.0 - B / (3.0 * A);
        x[1].second = sqrt(3) * temp2 / 2.0;
        x[2].first = -temp1 / 2.0 - B / (3.0 * A);
        x[2].second = -sqrt(3) * temp2 / 2.0;
    }
    return 0;
}

int main()
{
    mbuf mobj;
    Elem x[3];
    int pid = getpid();
    cout << "Srv pid: " << pid << endl;

    int fd = msgget(100, IPC_CREAT | IPC_EXCL | 0642);

    while (1)
    {
        if (msgrcv(fd, &mobj, MSGMAX, 15, IPC_NOWAIT | MSG_NOERROR) > 0)
        {
            if (Kardano(mobj.ratio[0], mobj.ratio[1], mobj.ratio[2], mobj.ratio[3], x) == -1)
                perror("Invalid A");
            mobj.ans[0] = x[0];
            mobj.ans[1] = x[1];
            mobj.ans[2] = x[2];

            mobj.mtype = mobj.childpid;
            msgsnd(fd, &mobj, sizeof(mobj.ans) * 2, IPC_NOWAIT);
        }
    }

    msgctl(fd, IPC_RMID, 0);
    return 0;
}