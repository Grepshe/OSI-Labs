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

void convert_to_C(Message &msg)
{
    if (msg.from == 2 && msg.type == 2)
    {
        msg.value *= 0.7112; //аршин -> м
    }
    if (msg.from == 2 && msg.type == 3)
    {
        msg.value *= 16.3804964; //Пуд -> кг
    }
    if (msg.from == 2 && msg.type == 4)
    {
        msg.value *= 0.505805; //кв.аршин -> м2
    }
    if (msg.from == 3 && msg.type == 2)
    {
        msg.value *= 0.3048; //фут -> метр
    }
    if (msg.from == 3 && msg.type == 3)
    {
        msg.value *= 0.453592; //фунт -> кг
    }
    if (msg.from == 3 && msg.type == 4)
    {
        msg.value *= 0.9144; //ярд -> м2
    }
    msg.from = 4;
}

void convert_from_C(Message &msg)
{
    if (msg.to == 2 && msg.type == 2)
    {
        msg.value /= 0.7112; //аршин -> м
    }
    if (msg.to == 2 && msg.type == 3)
    {
        msg.value /= 16.3804964; //Пуд -> кг
    }
    if (msg.to == 2 && msg.type == 4)
    {
        msg.value /= 0.505805; //кв.аршин -> м2
    }
    if (msg.to == 3 && msg.type == 2)
    {
        msg.value /= 0.3048; //фут -> метр
    }
    if (msg.to == 3 && msg.type == 3)
    {
        msg.value /= 0.453592; //фунт -> кг
    }
    if (msg.to == 3 && msg.type == 4)
    {
        msg.value /= 0.9144; //ярд -> м2
    }
    msg.from = msg.to;
}

void make_convertation(Message &msg)
{
    convert_to_C(msg);
    convert_from_C(msg);
}

struct Server
{
    Server()
    {
        server_socket = socket(AF_INET, SOCK_STREAM, NULL);

        inet_aton("127.0.0.1", &local.sin_addr);
        local.sin_port = htons(1234);
        local.sin_family = AF_INET;

        bind(server_socket, (struct sockaddr *)&local, sizeof(local));
        listen(server_socket, 5);

        client_socket = accept(server_socket, NULL, NULL);
    }

    void run()
    {
        Message msg;
        while (read(client_socket, &msg, sizeof(Message)))
        {
            if (msg.status_code == -1)
                break;
            make_convertation(msg);
            write(client_socket, &msg, sizeof(Message));
        }
        close(client_socket);
        cout << "Shutting down" << endl;
    }

    struct sockaddr_in local;

    int server_socket, client_socket;
};

int main(int argc, char **argv)
{
    Server srv;
    srv.run();

    return 0;
}