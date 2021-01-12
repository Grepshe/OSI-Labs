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
    int ratio[4] = {0, 0, 0, 0};
    Elem ans[3];
} mbuf;

int main()
{
    int a, b, c, d, i;
    int mypid = getpid();
    mbuf mobj;
    int len;
    int choise;

    cout << "Cli pid: " << mypid << endl;

    while (1)
    {
        cout << "Enter cubic coef a, b, c, d" << endl;
        cin >> a >> b >> c >> d;
        mobj.ratio[0] = a;
        mobj.ratio[1] = b;
        mobj.ratio[2] = c;
        mobj.ratio[3] = d;

        mobj.childpid = mypid;
        mobj.mtype = 15;

        len = sizeof(mobj.ans);

        if (msgsnd(0, &mobj, MSGMAX, IPC_NOWAIT))
            perror("rttessage - client");
        sleep(1);

        if (msgrcv(0, &mobj, MSGMAX, mypid, IPC_NOWAIT | MSG_NOERROR) > 0)
        {
            for (i = 0; i < 3; i++)
            {
                if (mobj.ans[i].second == 0.0)
                    printf("x%d = %.15lf\n", i, mobj.ans[i].first);
                else
                {
                    printf("x%d = %.15lf + i * %.15lf\n",
                           i, mobj.ans[i].first, mobj.ans[i].second);
                }
            }
        }

        break;
    }

    return 0;
}