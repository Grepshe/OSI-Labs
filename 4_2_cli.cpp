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
#include <sys/mman.h>

using namespace std;

#define MAX_CLIENTS 10

struct ClientData
{
    double lhs;
    double rhs;
    double res;
    char op;
};

struct ServerData
{
    int clients_quanity;
    ClientData clients[MAX_CLIENTS];
};

struct Client
{
    Client()
    {
        shm_fd = shm_open("/shm_calc", O_RDWR, S_IRUSR | S_IWUSR);

        data = reinterpret_cast<ServerData *>(mmap(NULL, sizeof(ServerData), PROT_WRITE, MAP_SHARED, shm_fd, 0));

        semaphore = sem_open("/sem_calc", O_RDWR);
        sem_wait(semaphore);
        mypos = data->clients_quanity++;
        sem_post(semaphore);
    }

    void run()
    {
        cout << "Runned" << endl;
        while (true)
        {
            double lhs, rhs;
            char op;
            cin >> lhs >> op >> rhs;
            sem_wait(semaphore);
            data->clients[mypos].lhs = lhs;
            data->clients[mypos].rhs = rhs;
            data->clients[mypos].op = op;
            sem_post(semaphore);
            usleep(10000);
            sem_wait(semaphore);
            cout << data->clients[mypos].res << endl;
            sem_post(semaphore);
        }
    }

    int shm_fd;
    int mypos;
    sem_t *semaphore;
    ServerData *data;
};

int main(int argc, char **argv)
{
    Client cli;
    cli.run();

    return 0;
}