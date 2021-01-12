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
#include <new>

using namespace std;

#define MAX_CLIENTS 10

double make_op(double lhs, double rhs, char op)
{
    switch (op)
    {
    case '+':
        return lhs + rhs;
    case '-':
        return lhs - rhs;
    case '*':
        return lhs * rhs;
    case '/':
        return lhs / rhs;
    default:
        return -1;
    }
}

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

struct Server
{
    Server()
    {
        shm_fd = shm_open("/shm_calc", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
        ftruncate(shm_fd, sizeof(ServerData));
        void *addr = mmap(NULL, sizeof(ServerData), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, NULL);
        data = new (reinterpret_cast<ServerData *>(addr)) ServerData;

        semaphore = sem_open("/sem_calc", O_CREAT, O_RDWR, 0);
        if (semaphore == SEM_FAILED)
        {
            perror(":( ");
            exit(1);
        }
        data->clients_quanity = 0;
        sem_post(semaphore);
    }

    void run()
    {
        cout << "Runned" << endl;
        while (true)
        {
            usleep(1000);
            sem_wait(semaphore);

            for (int i = 0; i < data->clients_quanity; ++i)
                data->clients[i].res = make_op(data->clients[i].lhs, data->clients[i].rhs, data->clients[i].op);

            sem_post(semaphore);
        }
        sem_close(semaphore);
        shm_unlink("/shm_calc");
    }

    int shm_fd;
    sem_t *semaphore;
    ServerData *data;
};

int main(int argc, char **argv)
{
    Server srv;
    srv.run();

    return 0;
}