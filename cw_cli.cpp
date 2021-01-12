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

#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

using namespace std;

#define MAX_CLIENTS 10

struct Message
{
    int status_code;
    int from; // 2 - старорусская, 3 - британская, 4 - СИ
    int to;   // 2 - старорусская, 3 - британская, 4 - СИ
    int type; // 2 - расстояние, 3 - масса, 4 - площадь
    double value;
};

struct Client
{
    Client()
    {
        my_socket = socket(AF_INET, SOCK_STREAM, NULL);

        inet_aton("127.0.0.1", &local.sin_addr);
        local.sin_port = htons(1234);
        local.sin_family = AF_INET;

        connect(my_socket, (struct sockaddr *)&local, sizeof(local));
        cout << "Connected" << endl;
    }

    void run()
    {
        Message msg;
        while (1)
        {
            cout << "Enter from, to (2-Starorus, 3-Brit, 4-Ci), type (2-lenght, 3-mass, 4-square), value. [from to type value], from = -1 to exit:" << endl;
            cin >> msg.from >> msg.to >> msg.type >> msg.value;
            if (msg.from == -1)
            {
                msg.status_code = -1;
                break;
            }
            else
                msg.status_code = 0;
            write(my_socket, &msg, sizeof(Message));
            read(my_socket, &msg, sizeof(Message));
            cout << "Result: " << msg.value << endl;
        }
        close(my_socket);
        cout << "Shutting down" << endl;
    }

    struct sockaddr_in local;
    int my_socket;
};

int main(int argc, char **argv)
{
    Client cli;
    cli.run();

    return 0;
}