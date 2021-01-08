#include <pthread.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <semaphore.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

const int TIME_TO_END = 30;
const char filename[] = "in.txt";

using namespace std;

sem_t *semaphore;
time_t start_time;

int writer()
{
    ofstream file(filename, ios_base::app);
    int counter = 0;
    while (time(0) - start_time < TIME_TO_END)
    {
        sem_wait(semaphore);

        file << rand() % 1000 << endl;
        file.flush();
        ++counter;

        sem_post(semaphore);
        usleep(10000 + rand() % 10000);
    }
    return counter;
}

int reader(int digit)
{
    FILE *file = fopen(filename, "r"); //dunno how to fix stream after reaching eof
    int counter = 0;
    char buf;
    while (time(0) - start_time < TIME_TO_END)
    {
        sem_wait(semaphore);

        if (getc(file) == digit + '0')
            ++counter;
        clearerr(file);

        sem_post(semaphore);
        usleep(10000 + rand() % 10000);
    }
    fclose(file);
    return counter;
}

int main(int argc, char **argv)
{
    //sem_init(&semaphore, 1, 1); needs to be putted to shm :(
    semaphore = sem_open("semaphore", O_CREAT, O_RDWR, 1);
    start_time = time(0);
    pid_t main = getpid();
    int id = 0;
    while (id < 20)
    {
        if (fork())
        {
            ++id;
        }
        else
        {
            break;
        }
    }
    if (getpid() == main)
    {
        while (time(0) - start_time < TIME_TO_END + 1)
        {
        }
        sem_unlink("semaphore");
    }
    else
    {
        if (id < 10)
            cout << getpid() << " I'm reader " << id << " Counted:" << reader(id) << endl;
        else
            cout << getpid() << " I'm writer " << id << " Writed:" << writer() << endl;
    }

    return 0;
}